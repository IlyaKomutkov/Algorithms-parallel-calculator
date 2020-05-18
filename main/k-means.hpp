#pragma once
#include <cmath>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <random>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "matrix.hpp"
#include "linalg.hpp"

void testK();

class Point {

private:
    size_t pointID, clusterID;
    size_t dim;
    std::vector<double> values;

public:
    Point(size_t id, std::string line) {
        dim = 0;
        pointID = id;
        std::stringstream is(line);
        double val;
        while (is >> val) {
            values.push_back(val);
            dim++;
        }
        clusterID = 0; //Initially not assigned to any cluster
    }

    size_t getDimensions() {
        return dim;
    }

    size_t getCluster() {
        return clusterID;
    }

    size_t getID() {
        return pointID;
    }

    void setCluster(int val) {
        clusterID = val;
    }

    double getVal(int pos) {
        return values[pos];
    }
};

class Cluster {

private:
    size_t clusterID;
    std::vector<double> centroid;
    std::vector<Point> points;

public:
    Cluster(size_t clusterId, Point centroid) {
        this->clusterID = clusterId;
        for (size_t i{ 0 }; i < centroid.getDimensions(); ++i) {
            this->centroid.push_back(centroid.getVal(i));
        }
        this->addPoint(centroid);
    }

    void addPoint(Point p) {
        p.setCluster(this->clusterID);
        points.push_back(p);
    }

    bool removePoint(int pointId) {
        size_t size = points.size();

        for (size_t i{ 0 }; i < size; ++i)
        {
            if (points[i].getID() == pointId)
            {
                points.erase(points.begin() + i);
                return true;
            }
        }
        return false;
    }

    size_t getId() {
        return clusterID;
    }

    Point getPoint(int pos) {
        return points[pos];
    }

    size_t getSize() {
        return points.size();
    }

    double getCentroidByPos(int pos) {
        return centroid[pos];
    }

    void setCentroidByPos(int pos, double val) {
        this->centroid[pos] = val;
    }
};

class KMeans {
private:
    int K, iters, dim, total_points;
    std::vector<Cluster> clusters;

    size_t getNearestClusterId(Point point) {
        double sum = 0.0, min_dist;
        size_t NearestClusterId;

        for (size_t i{ 0 }; i < dim; ++i)
        {
            sum += pow(clusters[0].getCentroidByPos(i) - point.getVal(i), 2.0);
        }

        min_dist = sqrt(sum);
        NearestClusterId = clusters[0].getId();

        for (size_t i{ 1 }; i < K; ++i)
        {
            double dist;
            sum = 0.0;

            for (size_t j{ 0 }; j < dim; ++j)
            {
                sum += pow(clusters[i].getCentroidByPos(j) - point.getVal(j), 2.0);
            }

            dist = sqrt(sum);

            if (dist < min_dist)
            {
                min_dist = dist;
                NearestClusterId = clusters[i].getId();
            }
        }

        return NearestClusterId;
    }

public:
    KMeans(int K, int iterations)
    {
        this->K = K;
        this->iters = iterations;
    }

    void run(std::vector<Point>& all_points, size_t files) {

        total_points = all_points.size();
        dim = all_points[0].getDimensions();


        //Initializing Clusters
        std::vector<int> used_pointIds;

        for (size_t i{ 1 }; i <= K; i++)
        {
            while (true)
            {
                int index = rand() % total_points;

                if (find(used_pointIds.begin(), used_pointIds.end(), index) == used_pointIds.end())
                {
                    used_pointIds.push_back(index);
                    all_points[index].setCluster(i);
                    Cluster cluster(i, all_points[index]);
                    clusters.push_back(cluster);
                    break;
                }
            }
        }
        std::cout << "Clusters initialized = " << clusters.size() << std::endl << std::endl;


        std::cout << "Running K-Means Clustering.." << std::endl;

        size_t iter = 1;
        while (true)
        {
            std::cout << "Iter - " << iter << "/" << iters << std::endl;
            bool done = true;

            // Add all points to their nearest cluster
            for (size_t i{ 0 }; i < total_points; i++)
            {
                size_t currentClusterId = all_points[i].getCluster();
                size_t nearestClusterId = getNearestClusterId(all_points[i]);

                if (currentClusterId != nearestClusterId)
                {
                    if (currentClusterId != 0) {
                        for (size_t j{ 0 }; j < K; j++) {
                            if (clusters[j].getId() == currentClusterId) {
                                clusters[j].removePoint(all_points[i].getID());
                            }
                        }
                    }

                    for (size_t j{ 0 }; j < K; j++) {
                        if (clusters[j].getId() == nearestClusterId) {
                            clusters[j].addPoint(all_points[i]);
                        }
                    }
                    all_points[i].setCluster(nearestClusterId);
                    done = false;
                }
            }

            // Recalculating the center of each cluster
            for (size_t i{ 0 }; i < K; i++)
            {
                size_t ClusterSize = clusters[i].getSize();

                for (size_t j{ 0 }; j < dim; j++)
                {
                    double sum = 0.0;
                    if (ClusterSize > 0)
                    {
                        for (size_t p{ 0 }; p < ClusterSize; p++)
                            sum += clusters[i].getPoint(p).getVal(j);
                        clusters[i].setCentroidByPos(j, sum / ClusterSize);
                    }
                }
            }

            if (done || iter >= iters)
            {
                std::cout << "Clustering completed in iteration : " << iter << std::endl << std::endl;
                break;
            }
            iter++;
        }

        std::string temp1 = "cluster";
        std::string temp2 = ".csv";
        std::string temp3 = "centroids";

        for (size_t i{ 0 }; i < K; i++)
        {
            //to change file names
            std::ofstream outfile;
            std::stringstream ss;
            //name files "clusterN_k, N - number of files, k=0...K
            ss << temp1 << files << "_" << i << temp2;
            std::string name;
            ss >> name;
            outfile.open(name);
            if (outfile.is_open())
            {
                for (size_t j{ 0 }; j < clusters[i].getSize(); j++)
                {
                    outfile << clusters[i].getPoint(j).getID() << "," << clusters[i].getPoint(j).getVal(0);
               
                    //running along a multidimensional array
                    for (size_t n{ 1 }; n < clusters[i].getPoint(j).getDimensions(); ++n)
                        outfile << "," << clusters[i].getPoint(j).getVal(n);
                    outfile << std::endl;
                }
                outfile << std::endl;
            }
        }


        //Write cluster centers to file

        std::ofstream outcenter;
        std::stringstream ss;
        ss << temp3 << files << temp2;
        std::string name;
        ss >> name;
        outcenter.open(name);
        if (outcenter.is_open()) {
            for (size_t i{ 0 }; i < K; i++) {
                outcenter << clusters[i].getId() << "," << clusters[i].getCentroidByPos(0);
                for (size_t j{ 1 }; j < dim; j++) {
                    outcenter << "," << clusters[i].getCentroidByPos(j) ;  //Output to file
                }
                outcenter << std::endl;
            }
            outcenter.close();
        }
        else {
            exit(-1);
        }

    }
};

void testK()
{
    size_t K = 10;
    size_t pointId = 1;
    int iters = 100; //max iterations
    //Open file for fetching points
    std::vector<std::string> pam = { "dim10.txt", "dim11.txt", "dim12.txt", "dim13.txt", "dim14.txt", "dim15.txt" };
    for (size_t i{ 0 }; i < pam.size(); ++i)
    {
        std::ifstream infile(pam[i].c_str());
        if (!infile.is_open()) {
            std::cout << "Error: Failed to open file." << std::endl;
        }
        std::vector<Point> all_points;
        std::string line;
        while (getline(infile, line)) {
            Point point(pointId, line);
            all_points.push_back(point);
            pointId++;
        }
        infile.close();
        if (all_points.size() < K) {
            std::cout << "Error: Number of clusters greater than number of points." << std::endl;
        }
        KMeans kmeans(K, iters);
        kmeans.run(all_points, i);
        K++;
    }


    std::cout << "\nData fetched successfully!" << std::endl << std::endl;
}

cmake_minimum_required(VERSION 3.14)
project(ode_solver)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(BoostTest main.cpp)
target_link_libraries(BoostTest ${Boost_LIBRARIES})

add_executable(ode_solver
        linalg.hpp
        LVOde.hpp
        main.cpp
        matrix.hpp
        matrix.inl
        matrix_methods.inl
        ODE.cpp
        ODE.hpp
        read_csv.cpp
        read_csv.hpp
        RK.hpp
        RKIntegrator.cpp
        RKIntegrator.hpp
        RKIntegrator.inl
        RKMethod.hpp
        testing.cpp
        testing.hpp
        vector.hpp)

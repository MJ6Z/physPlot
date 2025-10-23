cmake_minimum_required(VERSION 3.15)
project(complexPlotProject LANGUAGES CXX)

find_package(pybind11 REQUIRED)
find_package(OpenCV REQUIRED)

pybind11_add_module(physPlot plot.cpp)
target_link_libraries(physPlot PRIVATE ${OpenCV_LIBS})
set_target_properties(physPlot PROPERTIES CXX_STANDARD 17)

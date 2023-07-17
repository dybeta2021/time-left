cmake_minimum_required(VERSION 3.25)
project(pytimeleft)

set(CMAKE_CXX_STANDARD 20)
set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/bin/python3)

include_directories(deps/pybind11-2.10.4/include)
add_subdirectory(deps/pybind11-2.10.4)

aux_source_directory(. SOURCE)
pybind11_add_module(${PROJECT_NAME} ${SOURCE})

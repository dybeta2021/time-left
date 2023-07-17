cmake_minimum_required(VERSION 3.25)
project(time_left)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(deps/json-3.11.2/include)

add_executable(${PROJECT_NAME} main.cpp)

file(COPY access/future_day_transaction_calendar_2019.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_day_transaction_calendar_2020.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_day_transaction_calendar_2021.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_day_transaction_calendar_2022.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_day_transaction_calendar_2023.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_day_transaction_calendar_2024.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_day_transaction_calendar_2025.json DESTINATION ${CMAKE_BINARY_DIR}/)

file(COPY access/future_night_transaction_calendar_2019.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_night_transaction_calendar_2020.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_night_transaction_calendar_2021.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_night_transaction_calendar_2022.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_night_transaction_calendar_2023.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_night_transaction_calendar_2024.json DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY access/future_night_transaction_calendar_2025.json DESTINATION ${CMAKE_BINARY_DIR}/)


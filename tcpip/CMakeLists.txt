cmake_minimum_required(VERSION 2.8)

project(AllinOne1.2)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Threads)

# OpenCV
find_package( OpenCV REQUIRED )

# Pylon 
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
find_package(Pylon)
include_directories(${Pylon_INCLUDE_DIRS})

include_directories(Sources)
include_directories(Headers)
include_directories(TCPIP)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_USE_QTSQL TRUE)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCES Sources/*.cpp Headers/*.h)
file(GLOB TCPIP TCPIP/*)

set (project_sources
    main.cpp
    mainwindow.cpp
    tcpserver.cpp)

add_executable(AllinOne1.2 main.cpp mainwindow.cpp dbconnector.cpp toss.cpp mainwindow.ui ${SOURCES} ${TCPIP})

qt5_wrap_ui (mainwindow mainwindow.ui)

target_link_libraries(AllinOne1.2 Qt5::Widgets)
target_link_libraries(AllinOne1.2 Qt5::Core)
target_link_libraries(AllinOne1.2 Qt5::Sql)
target_link_libraries(AllinOne1.2 ${OpenCV_LIBS})
target_link_libraries(AllinOne1.2 ${OpenCV_LIBS} ${Pylon_LIBRARIES})

target_link_libraries(AllinOne1.2 ${OpenCV_LIBS} ${Pylon_LIBRARIES})
target_link_libraries(AllinOne1.2 Threads::Threads)
target_link_libraries(AllinOne1.2 Qt5::Network)

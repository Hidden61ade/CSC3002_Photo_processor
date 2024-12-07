cmake_minimum_required(VERSION 3.5)

project(CSC3002_Photo_processor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Gui Widgets Concurrent REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
set(OpenCV_DIR C:/Users/Lenovo/Downloads/opencv/opencv-build)
#set(OpenCV_DIR C:/opencv/opencv-build)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})



if(ANDROID)
  add_library(CSC3002_Photo_processor SHARED
      main.cpp
      mainwindow.cpp
      mainwindow.h
      mainwindow.ui
      ImageProcessor.h
      ImageProcessor.cpp
      pipeline.cpp
      pipeline.h
      nodebase.cpp
      nodebase.h
      port.cpp
      port.h
      imageprocessorwindow.cpp
      imageprocessorwindow.h
      imageprocessorwindow.ui
      lasso.cpp
      lasso.h
      grabcut.cpp
      grabcut.h
      grabcut2.h
      grabcut2.cpp
      grabcutwindow.cpp
      grabcutwindow.h
      grabcutwindow.ui

      simplecut.h
      simplecut.cpp
      simplerotate.h
      simplerotate.cpp
      mirror.h
      mirror.cpp
      watermark.h
      watermark.cpp

      lassowindow.cpp
      lassowindow.h
      lassowindow.ui
  )
else()
  add_executable(CSC3002_Photo_processor
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ImageProcessor.h
    ImageProcessor.cpp
    imageprocessorwindow.cpp
    imageprocessorwindow.h
    imageprocessorwindow.ui

    pipeline.cpp
    pipeline.h
    nodebase.cpp
    nodebase.h
    port.cpp
    port.h
    Nodes.cpp
    Nodes.h

    nodeconnection.cpp
    nodeconnection.h

    lasso.cpp
    lasso.h

    grabcut.h
    grabcut2.h
    grabcut.cpp
    grabcut2.cpp

    grabcutwindow.cpp
    grabcutwindow.h
    grabcutwindow.ui

    simplecut.h
    simplecut.cpp
    simplerotate.h
    simplerotate.cpp
    mirror.h
    mirror.cpp
    watermark.h
    watermark.cpp

    testwindow.cpp
    testwindow.h
    testwindow.ui

    agvview.cpp
    agvview.h

    lassowindow.cpp
    lassowindow.h
    lassowindow.ui
  )
endif()

target_link_libraries(CSC3002_Photo_processor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt5::Core Qt5::Gui Qt5::Concurrent ${OpenCV_LIBS} )


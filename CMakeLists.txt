# =================================================== *
# ====         Copyright (c) 2024 icampsi        ==== *
# ==== SPDX-License-Identifier: GPL-3.0-or-later ==== *
# =================================================== */

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ruleta VERSION 1.0.0 LANGUAGES CXX)

# Warning level
if (MSVC)
    add_compile_options(/W4 /WX)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Wall
        -Wextra
        -pedantic
        -Werror
        -Wno-nonportable-include-path
        -Wno-microsoft-include
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        -Wall
        -Wextra
        -pedantic
        -Werror
    )
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

# Find QT Widgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)
if(Qt${QT_VERSION_MAJOR}_FOUND)
    message("Found Qt library")
else()
    message(FATAL_ERROR "Qt Widgets not found")
endif()

set(MAIN_FILES
    # SRC
    main.cpp
    # MAIN_WIDGETS
    main_widgets/wheel.h       main_widgets/wheel.cpp     main_widgets/wheel.ui
    main_widgets/marcLbl.h      main_widgets/marcLbl.cpp    main_widgets/marcLbl.ui
    main_widgets/marcador.h     main_widgets/marcador.cpp   main_widgets/marcador.ui
    main_widgets/timer.h       main_widgets/timer.cpp     main_widgets/timer.ui

    # UI
    ui/mainwindow.h ui/mainwindow.cpp ui/mainwindow.ui
    ui/dialog.h ui/dialog.cpp ui/dialog.ui
    ui/timerdialog.h ui/timerdialog.cpp ui/timerdialog.ui
    ui/propertiesdialog.h ui/propertiesdialog.cpp ui/propertiesdialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${MAIN_FILES}
        resources/resources.qrc
    )
else()
    add_executable(${PROJECT_NAME}
        ${MAIN_FILES}
        resources/resources.qrc
    )
endif()

# Set the output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add current source dir as a include path
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# LINK LIBRARIES
# QT
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.icampsil.ruleta)
endif()

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
    )
endif()

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()

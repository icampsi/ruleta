cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ruleta VERSION 0.1.0 LANGUAGES CXX)

# Warning level
if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-nonportable-include-path -Wno-microsoft-include)
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
    message("Found Poppler library: ${POPPLER_CPP_LIB}")
else()
    message(FATAL_ERROR "Qt Widgets not found")
endif()

set(MAIN_FILES
    # SRC
    main.cpp
    WWheel.h    WWheel.cpp  WWheel.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ruleta
        MANUAL_FINALIZATION
        ${MAIN_FILES}
        MainWindow.h MainWindow.cpp MainWindow.ui
        MarcLbl.h MarcLbl.cpp MarcLbl.ui
        Marcador.h Marcador.cpp Marcador.ui
        dialog.h dialog.cpp dialog.ui


    )

else()
    if(ANDROID)
        add_library(ruleta SHARED
        )
    else()
        add_executable(ruleta
            ${MAIN_FILES}
        )
    endif()
endif()

# Set the output directory for the executable
set_target_properties(ruleta PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Add current source dir as a include path
target_include_directories(ruleta PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# LINK LIBRARIES
# QT
target_link_libraries(ruleta PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.FindWhat)
endif()

set_target_properties(ruleta PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

include(GNUInstallDirs)
install(TARGETS ruleta
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ruleta)
endif()

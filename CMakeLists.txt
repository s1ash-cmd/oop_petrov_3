cmake_minimum_required(VERSION 3.16)

project(oop_petrov_3 VERSION 0.1 LANGUAGES CXX)

if(POLICY CMP0167)
    cmake_policy(SET CMP0167 NEW)
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Boost REQUIRED COMPONENTS serialization)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
endif()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
)

set(ADDITIONAL_SOURCES
    petrov_header.h
    petrov_item.h
    petrov_used_item.h
    petrov_widget.cpp
    petrov_widget.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(oop_petrov_3
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${ADDITIONAL_SOURCES}
    )
else()
    add_executable(oop_petrov_3
        ${PROJECT_SOURCES}
        ${ADDITIONAL_SOURCES}
        petrov_item.cpp
        petrov_used_item.cpp

        petrov_dialog.h petrov_dialog.cpp petrov_dialog.ui
    )
endif()

target_link_libraries(oop_petrov_3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Boost::serialization)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.oop_petrov_3)
endif()

set_target_properties(oop_petrov_3 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS oop_petrov_3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(oop_petrov_3)
endif()

cmake_minimum_required(VERSION 3.5)

project(GIBDD VERSION 0.1 LANGUAGES CXX)

set(QT_DIR "C:\\Qt\\6.4.2\\msvc2019_64")


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.4.2\\msvc2019_64")
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Sql)


set(PROJECT_SOURCES
      main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        cars.cpp
        cars.h
        cars.ui
        registration.cpp
        registration.h
        registration.ui
        newto.h
        newto.cpp
        newto.ui
        admincars.cpp
        admincars.h
        admincars.ui
        carinfo.cpp
        carinfo.h
        carinfo.ui
        newcar.cpp
        newcar.h
        newcar.ui
      )


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(GIBDD
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(GIBDD
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(GIBDD PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(GIBDD  PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

install(TARGETS
            GIBDD
        DESTINATION
            .
)

get_property(QT_CORE_INCLUDE_DIRS TARGET Qt${QT_VERSION_MAJOR}::Core PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
list(GET QT_CORE_INCLUDE_DIRS 0 QT_CORE_MAIN_INCLUDE_DIR)
get_filename_component(QT_MAIN_DIR ${QT_CORE_MAIN_INCLUDE_DIR}/../.. ABSOLUTE)

install(FILES $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Core>
              $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Gui>
              $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Widgets>
              $<TARGET_FILE:Qt${QT_VERSION_MAJOR}::Sql>
              DESTINATION .)

install(DIRECTORY ${QT_MAIN_DIR}/plugins/platforms/
                  DESTINATION ./platforms USE_SOURCE_PERMISSIONS)

install(DIRECTORY
    ${QT_MAIN_DIR}/plugins/sqldrivers/
        DESTINATION ./sqldrivers USE_SOURCE_PERMISSIONS)

if(QT_VERSION_MAJOR EQUAL 5)
    qt_finalize_executable(GIBDD )
endif()

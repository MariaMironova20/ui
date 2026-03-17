cmake_minimum_required(VERSION 3.16)

project(ui1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Подключаем OpenGL в зависимости от версии Qt
if(${QT_VERSION_MAJOR} EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
    set(OPENGL_COMPONENT Qt6::OpenGLWidgets)
else()
    find_package(Qt5 REQUIRED COMPONENTS OpenGL)
    set(OPENGL_COMPONENT Qt5::OpenGL)
endif()

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ui1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ui1 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ui1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линкуем нужные модули
target_link_libraries(ui1 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    ${OPENGL_COMPONENT}
)

# Остальная часть (установка, свойства iOS и т.д.) остаётся без изменений
include(GNUInstallDirs)
install(TARGETS ui1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ui1)
endif()

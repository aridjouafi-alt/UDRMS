cmake_minimum_required(VERSION 3.16)
project(udrms VERSION 0.1 LANGUAGES CXX)

# ─────────────────────────────
# C++ + Qt Settings
# ─────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR})

# ─────────────────────────────
# Qt Packages
# ─────────────────────────────
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ─────────────────────────────
# Project Sources (Qt + UI)
# ─────────────────────────────
set(PROJECT_SOURCES
    # Core app
    main.cpp
    udrms.cpp
    udrms.h

    # Other windows/pages
    welcome.cpp
    welcome.h


    # Resources
    resources.qrc

    # Student module (Qt UI + logic)
    studentwidget.cpp
    studentwidget.h
)

# ─────────────────────────────
# External C++ logic (your backend classes)
# ─────────────────────────────
set(BACKEND_SOURCES
    src/core/university.h
    src/core/university.cpp

    src/core/student.h
    src/core/student.cpp

    src/core/room.h
    src/core/room.cpp

    src/core/dormitory.h
    src/core/dormitory.cpp

    src/core/restaurant.h
    src/core/restaurant.cpp

    src/core/menu.h
    src/core/menu.cpp

    src/core/filemanager.h
    src/core/filemanager.cpp
)

# ─────────────────────────────
# Build Target
# ─────────────────────────────
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(udrms
        MANUAL_FINALIZATION

        ${PROJECT_SOURCES}
        ${BACKEND_SOURCES}

        udrms.ui
        welcome.ui
        studentwidget.ui
        dormitorywidget.ui
        restaurantwidget.ui
        dormitorywidget.h dormitorywidget.cpp dormitorywidget.ui
        restaurantwidget.h restaurantwidget.cpp restaurantwidget.ui
    )
else()
    if(ANDROID)
        add_library(udrms SHARED
            ${PROJECT_SOURCES}
            ${BACKEND_SOURCES}
        )
    else()
        add_executable(udrms
            ${PROJECT_SOURCES}
            ${BACKEND_SOURCES}
        )
    endif()
endif()

# ─────────────────────────────
# Link Qt
# ─────────────────────────────
target_link_libraries(udrms PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# ─────────────────────────────
# Include backend folder
# ─────────────────────────────
target_include_directories(udrms PRIVATE src/core)

# ─────────────────────────────
# App Properties
# ─────────────────────────────
set_target_properties(udrms PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# ─────────────────────────────
# Install
# ─────────────────────────────
include(GNUInstallDirs)

install(TARGETS udrms
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# ─────────────────────────────
# Qt6 Finalization
# ─────────────────────────────
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(udrms)
endif()
cmake_minimum_required(VERSION 3.14)

project(stock_exchange_console VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.85.0 COMPONENTS filesystem regex)

if(Boost_FOUND)
    add_executable(progname file1.cxx file2.cxx)
    target_link_libraries(progname Boost::filesystem Boost::regex)
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

find_library(MYSQLCPPCONN_LIBRARY NAMES mysqlcppconn)
find_path(MYSQLCPPCONN_INCLUDE_DIR NAMES mysql_driver.h)
if(MYSQLCPPCONN_LIBRARY AND MYSQLCPPCONN_INCLUDE_DIR)
    include_directories(${MYSQLCPPCONN_INCLUDE_DIR})
    link_directories(/usr/lib/x86_64-linux-gnu)
else()
    message(FATAL_ERROR "Could not find MySQL Connector/C++")
endif()

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(stock_exchange_console
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        user.h user.cpp
        order.h order.cpp
        ordertype.h ordertype.cpp
        wallet.h wallet.cpp
        asset.h asset.cpp
        exchange.h exchange.cpp
        marketstatistics.h marketstatistics.cpp
        transaction.h transaction.cpp
        exchangedata.h exchangedata.cpp
        assettype.h assettype.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET stock_exchange_console APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(stock_exchange_console SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(stock_exchange_console
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(stock_exchange_console
    PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${MySQLConnectorCPP_LIBRARIES}
    ${MySQLConnectorCPP_LIBRARIES}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.stock_exchange_console)
endif()
set_target_properties(stock_exchange_console PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS stock_exchange_console
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(stock_exchange_console)
    qt_finalize_executable(stock_exchange_console)
endif()

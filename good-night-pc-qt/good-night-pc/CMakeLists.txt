cmake_minimum_required(VERSION 3.16)

project(good-night-pc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebView HttpServer WebChannel)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appgood-night-pc
    main.cpp
)

qt_add_qml_module(appgood-night-pc
    URI good-night-pc
    VERSION 1.0

    QML_FILES
    Main.qml

    SOURCES
    backend/backend.h
    backend/backend.cpp
    SOURCES frontend/frontend.h
    SOURCES frontend/frontend.cpp
    SOURCES frontend/websockettransport.h
    SOURCES frontend/websockettransport.cpp
    SOURCES frontend/websocketclientwrapper.h
    SOURCES frontend/websocketclientwrapper.cpp

    #     RESOURCES android/AndroidManifest.xml android/build.gradle android/res/values/libs.xml android/res/xml/qtprovider_paths.xml android/gradle/wrapper/gradle-wrapper.jar android/gradle/wrapper/gradle-wrapper.properties android/gradle.properties android/gradlew android/gradlew.bat
)

qt_add_resources(appgood-night-pc "appgood-night-pc"
    PREFIX "/"
    FILES
    assets/www/index.html
    assets/www/styles.css
    assets/www/qwebchannel.js
)

set_property(TARGET appgood-night-pc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appgood-night-pc PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgood-night-pc
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgood-night-pc
    PRIVATE Qt6::Quick
    PRIVATE Qt6::WebView
    PRIVATE Qt6::HttpServer
    PRIVATE Qt6::WebChannel
)

include(GNUInstallDirs)
install(TARGETS appgood-night-pc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

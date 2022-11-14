cmake_minimum_required(VERSION 3.5)

project(ProdApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)




set(PROJECT_SOURCES
        main.cpp
        login.cpp
        login.h
        login.ui
        homeScreen.cpp
        homeScreen.h
        homeScreen.ui
        addtask.h
        addtask.cpp
        addtask.ui
        tasks.h
        viewtask.cpp
        viewtask.h
        viewtask.ui
        account.h
        account.cpp
        account.ui
        completedtasks.h
        completedtasks.cpp
        completedtasks.ui
        notes.cpp
        notes.h
        notes.ui
        img.qrc
        addevent.cpp
        addevent.h
        addevent.ui
        events.h
        viewevent.cpp
        viewevent.h
        viewevent.ui
        studentlist.h
        studentlist.cpp
        studentlist.ui
        calenderview.h
        calenderview.cpp
        calenderview.ui
        adminpage.h
        adminpage.cpp
        adminpage.ui
        adminpin.h
        adminpin.cpp
        adminpin.ui
        sendmessage.h
        sendmessage.cpp
        sendmessage.ui
        viewmessage.h
        viewmessage.cpp
        viewmessage.ui
        replymessage.h
        replymessage.cpp
        replymessage.ui
        eventreminder.h
        eventreminder.cpp
        eventreminder.ui

)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(UNIson
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_ICON_RESOURCE_WINDOWS}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ProdApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(UNIson SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(UNIson
            ${PROJECT_SOURCES}
        )
    endif()
endif()
target_link_libraries(UNIson PRIVATE Qt6::Sql)
target_link_libraries(UNIson PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(UNIson PRIVATE Qt6::Multimedia)


set_target_properties(UNIson PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
add_custom_command(TARGET UNIson PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/db/ $<TARGET_FILE_DIR:UNIson>)
install(TARGETS UNIson
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UNIson)

endif()

cmake_minimum_required(VERSION 3.16)

project(noteapp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appnoteapp
    main.cpp
)

qt_add_qml_module(appnoteapp
    URI noteapp
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES note.h note.cpp
        SOURCES markdownnote.h markdownnote.cpp
        QML_FILES
        QML_FILES MarkdownNote.qml
        QML_FILES FileView.qml
        SOURCES notemanager.h notemanager.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appnoteapp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appnoteapp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appnoteapp
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appnoteapp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

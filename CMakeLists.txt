cmake_minimum_required(VERSION 3.16)

project(babnote VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 COMPONENTS Quick Sql REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(BabnoteApp
    main.cpp
)

set(QML_FILES
    main.qml
    NoteExplorer.qml
    NoteEditor.qml
    NoteExplorerBar.qml
)

qt_add_qml_module(BabnoteApp
    URI babnote
    VERSION 1.0
    RESOURCE_PREFIX /babatg
    QML_FILES
        ${QML_SINGLETONS}
        ${QML_FILES}
    SOURCES
        types.h
        INoteController.h
        DBNoteController.h DBNoteController.cpp
)

set_target_properties(BabnoteApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER babnote
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(BabnoteApp
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(BabnoteApp
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Sql
)

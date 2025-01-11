cmake_minimum_required(VERSION 3.16)

project(babnote VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 COMPONENTS Quick Sql REQUIRED)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(babnote
    main.cpp
)

qt_add_qml_module(babnote
    URI babnote
    VERSION 1.0
    RESOURCE_PREFIX /babatg
    QML_FILES
        main.qml
        NoteExplorer.qml
        NoteEditor.qml
        NoteExplorerBar.qml
    SOURCES
        types.h
        INoteController.h
        DBNoteController.h DBNoteController.cpp
)

set_target_properties(babnote PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(babnote
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(babnote
    PRIVATE Qt6::Quick Qt6::Sql)

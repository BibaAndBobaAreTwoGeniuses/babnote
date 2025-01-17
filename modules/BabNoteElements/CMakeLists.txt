find_package(Qt6 6.5 COMPONENTS Quick Sql REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)


include_directories(src)
qt_add_qml_module(BabNoteElements
    URI BabNote.Elements
    VERSION 1.0
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/BabNote/Elements"
    SOURCES
        src/INoteController.h
        src/DBNoteController.h
        src/DBNoteController.cpp
        src/Note.h
        src/Note.cpp
        src/SqlNoteModel.h
        src/SqlNoteModel.cpp




)
target_link_libraries(BabNoteElements
    PUBLIC
        Qt6::Quick
        Qt6::Sql
)

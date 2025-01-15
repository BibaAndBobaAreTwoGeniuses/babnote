set(PROJ_QML_SINGLETON_FILES
    qml/singletons/AppSettings.qml
)
set(PROJ_QML_FILES
    ${PROJ_QML_SINGLETON_FILES}
    qml/Main.qml
    qml/FileViewBar.qml
    qml/FileViewMenu.qml
    qml/FileView.qml
    qml/TextNote.qml
)

set_source_files_properties(${PROJ_QML_SINGLETON_FILES}
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(BabNote
    URI BabNote
    VERSION 1.0
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/BabNote"
    QML_FILES
        ${PROJ_QML_FILES}
)
target_link_libraries(BabNote
    PUBLIC
        BabNoteElements
)
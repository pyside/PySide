#
# Try to find QtMultimedia
# TODO: Remove this hack when cmake support QtMultimedia module
if (NOT QT_QTMULTIMEDIA_FOUND AND ${QTVERSION} VERSION_GREATER 4.5.9)
    find_path(QT_QTMULTIMEDIA_INCLUDE_DIR QtMultimedia
            PATHS ${QT_HEADERS_DIR}/QtMultimedia
                ${QT_LIBRARY_DIR}/QtMultimedia.framework/Headers
            NO_DEFAULT_PATH)
    find_library(QT_QTMULTIMEDIA_LIBRARY QtMultimedia PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
    if (QT_QTMULTIMEDIA_INCLUDE_DIR AND QT_QTMULTIMEDIA_LIBRARY)
        set(QT_QTMULTIMEDIA_FOUND ON)
    else()
        #Replace this on documentation
        set(if_QtMultimedia "<!--")
        set(end_QtMultimedia "-->")
    endif()
endif ()

# Try to find QtMaemo5 - it has to be done before QtGui to enable some QtMaemo5 flags
# TODO: Remove this hack when cmake support QtMaemo5 module
if (NOT QT_QTMAEMO5_FOUND AND ${QTVERSION} VERSION_GREATER 4.5.9)
    find_path(QT_QTMAEMO5_INCLUDE_DIR QtMaemo5
            PATHS ${QT_HEADERS_DIR}/QtMaemo5
                ${QT_LIBRARY_DIR}/QtMaemo5.framework/Headers
            NO_DEFAULT_PATH)
    find_library(QT_QTMAEMO5_LIBRARY QtMaemo5 PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
    if (QT_QTMAEMO5_INCLUDE_DIR AND QT_QTMAEMO5_LIBRARY)
        set(QT_QTMAEMO5_FOUND ON)
        set(Q_WS_MAEMO_5 ON)
    else()
        #Replace this on documentation
        set(if_Maemo5 "<!--")
        set(end_Maemo5 "-->")
    endif()
endif ()

# Try to find QtDeclarative
# TODO: Remove this hack when cmake support QtDeclarative module
if (NOT QT_QTDECLARATIVE_FOUND AND ${QTVERSION} VERSION_GREATER 4.6.0)
    find_path(QT_QTDECLARATIVE_INCLUDE_DIR QtDeclarative
            PATHS ${QT_HEADERS_DIR}/QtDeclarative
                ${QT_LIBRARY_DIR}/QtDeclarative.framework/Headers
            NO_DEFAULT_PATH)
    find_library(QT_QTDECLARATIVE_LIBRARY QtDeclarative PATHS ${QT_LIBRARY_DIR} NO_DEFAULT_PATH)
    if (QT_QTDECLARATIVE_INCLUDE_DIR AND QT_QTDECLARATIVE_LIBRARY)
        set(QT_QTDECLARATIVE_FOUND ON)
    else()
        #Replace this on documentation
        set(if_QtDeclarative "<!--")
        set(end_QtDeclarative "-->")
    endif()
endif ()



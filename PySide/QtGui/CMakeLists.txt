project(QtGui)

# Check QtGui support
macro(CHECK_QT_GUI_MACRO macro_display_name qt_macro module_sources global_sources)
    if (DEFINED PYSIDE_${qt_macro})
        if (PYSIDE_${qt_macro})
            list(APPEND ${global_sources} ${${module_sources}})
        endif()
    else()
        set(SRC_FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/test${qt_macro}.cxx)
        file(WRITE ${SRC_FILE}
        "#include <QtGui>\n"
        "int main() { \n"
        "#ifdef ${qt_macro}\n"
        "#error not supported.\n"
        "#endif\n"
        "}\n")

        try_compile(Q_WORKS ${CMAKE_BINARY_DIR}
                    ${SRC_FILE}
                    CMAKE_FLAGS
                    -DINCLUDE_DIRECTORIES:STRING=${QT_QTGUI_INCLUDE_DIR}\;${QT_INCLUDE_DIR}
                    -DLINK_LIBRARIES:PATH=${QT_QTGUI_LIBRARY_RELEASE}
                    OUTPUT_VARIABLE OUTPUT)

        set("PYSIDE_${qt_macro}" ${Q_WORKS} CACHE STRING "Has this Qt module been found by pyside?")
        if(Q_WORKS)
            message(STATUS "Testing support to ${macro_display_name} -- enabled")
            list(APPEND ${global_sources} ${${module_sources}})
        else()
            message(STATUS "Testing support to ${macro_display_name} -- disabled")
        endif()
    endif()
endmacro(CHECK_QT_GUI_MACRO)


if(Q_WS_X11)
    set(MODULE_NAME gui_x11)
    set(SPECIFIC_OS_FILES
        ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qx11info_wrapper.cpp
       )

elseif(Q_WS_MAC)
    set(MODULE_NAME gui_mac)
    set(SPECIFIC_OS_FILES
       )
else()
    message(FATAL_ERROR "OS not supported")
endif(Q_WS_X11)

if (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)
    set (QtGui_46_SRC )
else()
    set(QtGui_46_SRC
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix2x2_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix2x3_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix2x4_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix3x2_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix3x3_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix3x4_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix4x2_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix4x3_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix4x4_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgesture_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgesturerecognizer_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsanchor_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsanchorlayout_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsblureffect_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicscolorizeeffect_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsdropshadoweffect_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicseffect_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsobject_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsopacityeffect_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsrotation_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscale_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicstransform_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qkeyeventtransition_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmouseeventtransition_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpangesture_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpinchgesture_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qquaternion_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qswipegesture_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtilerules_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtouchevent_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtouchevent_touchpoint_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qvector2d_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qvector3d_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qvector4d_wrapper.cpp
    )
endif (${QT_VERSION_MAJOR} EQUAL 4 AND ${QT_VERSION_MINOR} LESS 6)

set(QtGui_SRC
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractbutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractgraphicsshapeitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractitemdelegate_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractitemview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractproxymodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractscrollarea_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractslider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractspinbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstracttextdocumentlayout_paintcontext_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstracttextdocumentlayout_selection_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstracttextdocumentlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qactionevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qactiongroup_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qaction_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qapplication_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qbitmap_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qboxlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qbrush_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qbuttongroup_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcalendarwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcdestyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcheckbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcleanlooksstyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qclipboard_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcloseevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcolordialog_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcolor_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcolumnview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcombobox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcommandlinkbutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcommonstyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcompleter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qconicalgradient_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcontextmenuevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qcursor_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdatawidgetmapper_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdateedit_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdatetimeedit_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdesktopservices_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdesktopwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdialogbuttonbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdialog_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdial_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdirmodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdockwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdoublespinbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdoublevalidator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdragenterevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdragleaveevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdragmoveevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdrag_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qdropevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qerrormessage_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfiledialog_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfileiconprovider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfileopenevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfilesystemmodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfocusevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfocusframe_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfontcombobox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfontdatabase_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfontdialog_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfontinfo_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfontmetricsf_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfontmetrics_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qfont_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qformlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qframe_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgradient_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsellipseitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsgridlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsitemanimation_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsitemgroup_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicslayoutitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicslayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicslinearlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicslineitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicspathitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicspixmapitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicspolygonitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsproxywidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsrectitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenecontextmenuevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenedragdropevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicssceneevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenehelpevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenehoverevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenemouseevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenemoveevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicssceneresizeevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscenewheelevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsscene_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicssimpletextitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicstextitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicsview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgraphicswidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgridlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgroupbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qhboxlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qheaderview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qhelpevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qhideevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qhoverevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qicondragevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qiconenginev2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qiconengine_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qicon_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qimageiohandler_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qimagereader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qimage_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qimagewriter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qinputcontextfactory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qinputcontext_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qinputdialog_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qinputevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qinputmethodevent_attribute_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qinputmethodevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qintvalidator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qitemdelegate_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qitemeditorcreatorbase_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qitemeditorfactory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qitemselectionmodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qitemselectionrange_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qitemselection_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qkeyevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qkeysequence_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlabel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlayoutitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlcdnumber_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlineargradient_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlineedit_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlistview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlistwidgetitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qlistwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmainwindow_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmatrix_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmdiarea_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmdisubwindow_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmenubar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmenu_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmessagebox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmotifstyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmouseevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmoveevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qmovie_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpaintdevice_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpaintenginestate_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpaintengine_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpainterpath_element_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpainterpathstroker_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpainterpath_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpainter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpaintevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpalette_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpen_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpictureio_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpicture_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpixmapcache_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpixmap_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qplaintextdocumentlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qplaintextedit_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qplastiquestyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpolygonf_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpolygon_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprogressbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprogressdialog_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qproxymodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpushbutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qradialgradient_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qradiobutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qregexpvalidator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qregion_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qresizeevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qrubberband_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qscrollarea_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qscrollbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsessionmanager_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qshortcutevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qshortcut_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qshowevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsizepolicy_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qslider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsortfilterproxymodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsound_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qspaceritem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qspinbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsplashscreen_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsplitterhandle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsplitter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstackedlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstackedwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstandarditemmodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstandarditem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstatusbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstatustipevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstringlistmodel_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleditemdelegate_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstylefactory_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstylehintreturnmask_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstylehintreturnvariant_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstylehintreturn_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionbutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptioncombobox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptioncomplex_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiondockwidgetv2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiondockwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionfocusrect_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionframev2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionframe_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiongraphicsitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiongroupbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionheader_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionmenuitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionprogressbarv2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionprogressbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionrubberband_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionsizegrip_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionslider_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionspinbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontabbarbase_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontabv2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontabwidgetframe_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontab_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontitlebar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontoolbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontoolboxv2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontoolbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptiontoolbutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionviewitemv2_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionviewitemv3_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionviewitemv4_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoptionviewitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyleoption_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstylepainter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qstyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsyntaxhighlighter_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtabbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtabletevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtableview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtablewidgetitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtablewidgetselectionrange_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtablewidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtabwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextblockformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextblockgroup_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextblock_iterator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextblockuserdata_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextblock_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextbrowser_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextcharformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextcursor_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextdocumentfragment_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextdocument_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextedit_extraselection_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextedit_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextfragment_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextframeformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextframe_iterator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextframe_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextimageformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextinlineobject_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextlayout_formatrange_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextlength_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextline_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextlistformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextlist_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextobjectinterface_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextobject_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextoption_tab_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtextoption_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtexttablecellformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtexttablecell_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtexttableformat_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtexttable_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtgui_module_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtimeedit_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtoolbar_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtoolbox_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtoolbutton_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtooltip_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtransform_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtreeview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtreewidgetitemiterator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtreewidgetitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qtreewidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qundocommand_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qundogroup_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qundostack_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qundoview_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qvalidator_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qvboxlayout_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwhatsthisclickedevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwhatsthis_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwheelevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwidgetaction_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwidgetitem_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwidget_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwindowsstyle_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwindowstatechangeevent_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwizardpage_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qwizard_wrapper.cpp
${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qworkspace_wrapper.cpp

${SPECIFIC_OS_FILES}
${QtGui_46_SRC}
)

#Check GtkStyle
set(QT_GTKSTYLE_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qgtkstyle_wrapper.cpp
)
CHECK_QT_GUI_MACRO("GtkStyle" QT_NO_STYLE_GTK QT_GTKSTYLE_SRCS QtGui_SRC)

#Check SystemTray
set(QT_SYSTEMTRAY_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsystemtrayicon_wrapper.cpp
)
CHECK_QT_GUI_MACRO("SystemTray" QT_NO_SYSTEMTRAYICON QT_SYSTEMTRAY_SRCS QtGui_SRC)

#Check QT_PRINTDIALOG support
set(QT_PRINTDIALOG_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractpagesetupdialog_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qabstractprintdialog_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qpagesetupdialog_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprintdialog_wrapper.cpp
)
CHECK_QT_GUI_MACRO("PrintDialog Support" QT_NO_PRINTDIALOG QT_PRINTDIALOG_SRCS QtGui_SRC)

#Check QT_PRITPREVIEW support
set(QT_PRINTPREVIEW_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprintpreviewwidget_wrapper.cpp
)
CHECK_QT_GUI_MACRO("PrintPreview Support" QT_NO_PRINTPREVIEWWIDGET QT_PRINTPREVIEW_SRCS QtGui_SRC)

#Check QT_PRINTPREVIEWDIALOG support
set(QT_PRINTPREVIEWDIALOG_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprintpreviewdialog_wrapper.cpp
)
CHECK_QT_GUI_MACRO("PrintPreviewDialog Support" QT_NO_PRINTPREVIEWDIALOG QT_PRINTPREVIEWDIALOG_SRCS QtGui_SRC)

#Check QT_PRINTER
set(QT_PRINTER_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprinter_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprinterinfo_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qprintengine_wrapper.cpp
)
CHECK_QT_GUI_MACRO("Printer Support" QT_NO_PRINTER QT_PRINTER_SRCS QtGui_SRC)

#Check QT_SIZEGRIP support
set(QT_SIZEGRIP_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/qsizegrip_wrapper.cpp
)
CHECK_QT_GUI_MACRO("SizeGrip Support" QT_NO_SIZEGRIP QT_SIZEGRIP_SRCS QtGui_SRC)

configure_file(typesystem_gui.xml.in
               "${CMAKE_CURRENT_BINARY_DIR}/typesystem_gui.xml" @ONLY)

execute_generator(gui QtGui_SRC "${CMAKE_CURRENT_BINARY_DIR}:${QtCore_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/PySide/QtGui/
                    ${QT_INCLUDE_DIR}
                    ${SHIBOKEN_INCLUDE_DIR}
                    ${libpyside_SOURCE_DIR}
                    ${PYTHON_INCLUDE_PATH}
                    ${QtCore_BINARY_DIR}/PySide/QtCore/
                    )
add_library(QtGui SHARED ${QtGui_SRC})
set_property(TARGET QtGui PROPERTY PREFIX "")
target_link_libraries(QtGui
                      pyside
                      QtCore
                      ${PYTHON_LIBRARIES}
                      ${SHIBOKEN_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
                      )

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QtGui.so DESTINATION "${SITE_PACKAGE}/PySide")

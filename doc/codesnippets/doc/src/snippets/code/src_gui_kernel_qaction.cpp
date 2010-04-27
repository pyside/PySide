//! [0]
app = QApplication(argv)
app.setAttribute(Qt.AA_DontShowIconsInMenus)  # Icons are *no longer shown* in menus
// ...
myAction = QAction()
// ...
myAction.setIcon(SomeIcon)
myAction.setIconVisibleInMenu(True)   # Icon *will* be shown in menus for *this* action.
//! [0]

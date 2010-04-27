//! [0]
def nextId(self):
    id = self.currentId()
    if id == Page_Intro:
        if field("intro.evaluate").toBool():
            return Page_Evaluate
        else:
            return Page_Register
    elif id == Page_Evaluate:
        return Page_Conclusion
    elif id == Page_Register:
        if field("register.upgradeKey").toString().isEmpty():
            return Page_Details
        else:
            return Page_Conclusion
    elif id == Page_Details:
        return Page_Conclusion
    else:
        return -1
//! [0]


//! [1]
class MyWizard(QWizard):
    def __init__(self, parent):
        QWizard.__ini__(self, parent)
        ...
        layout = [QWizard.Stretch, QWizard.BackButton, QWizard.CancelButton, QWizard.NextButton, QWizard.FinishButton]
        setButtonLayout(layout);
        ...
//! [1]

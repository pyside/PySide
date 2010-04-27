//! [0]
def wheelEvent(self, event):
    numDegrees = event.delta() / 8
    numSteps = numDegrees / 15

    if event->orientation() == Qt.Horizontal:
        scrollHorizontally(numSteps)
    else:
        scrollVertically(numSteps)
    event.accept()
//! [0]

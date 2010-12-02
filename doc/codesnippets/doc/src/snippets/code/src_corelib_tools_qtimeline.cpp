//! [0]
...
progressBar = QProgressBar(self)
progressBar.setRange(0, 100)

# Construct a 1-second timeline with a frame range of 0 - 100
timeLine = QTimeLine(1000, self)
timeLine.setFrameRange(0, 100)
timeLine.frameChanged[int].connect(progressBar.setValue)

# Clicking the push button will start the progress bar animation
pushButton = QPushButton(QObject.tr("Start animation"), self)
pushButton.clicked.connect(timeLine.start)
...
//! [0]

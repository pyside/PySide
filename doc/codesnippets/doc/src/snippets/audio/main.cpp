
class Window2 (QWidget):
//![0]
    @Slot(QAudio.State)
    def stateChanged(self, newState):
        if newState == QAudio.StopState:
            if self.input.error() != QAudio.NoError:
                # Error handling
//![0]

class Window (QWidget):
    def __init__(self):
        QWidget.__init__(self)
        self.output = QAudioOutput()
        self.output.stateChanged[QAudio.State].connect(self.stateChanged)

    def setupFormat(self):
//![1]
        format = QAudioFormat()
        format.setFrequency(44100)
//![1]
        format.setChannels(2)
        format.setSampleSize(16)
        format.setCodec("audio/pcm")
        format.setByteOrder(QAudioFormat.LittleEndian)
//![2]
        format.setSampleType(QAudioFormat.SignedInt)

        info = QAudioDeviceInfo(QAudioDeviceInfo.defaultOutputDevice())

        if not info.isFormatSupported(format):
            format = info.nearestFormat(format)
//![2]

//![3]
    @Slot(QAudio.State)
    def stateChanged(self, newState):
        if newState == QAudio.StopState:
            if self.output.error() != QAudio.NoError:
                # Perform error handling
            else:
                # Normal stop
//![3]

        # Handle
        elif newState == QAudio.ActiveState:
            # Handle active state...

app = QApplication(sys.argv)

window = Window()
window.show()
sys.exit(app.exec_())



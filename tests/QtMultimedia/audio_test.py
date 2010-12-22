
'''Test cases for QHttp'''

import unittest

from PySide.QtCore import *
from PySide.QtMultimedia import *

class testAudioDevices(unittest.TestCase):

    def testListDevices(self):
        valid = False
        devices = QAudioDeviceInfo.availableDevices(QAudio.AudioOutput)
        if not len(devices):
            return

        valid = True
        for devInfo in devices:
            if devInfo.deviceName() == 'null':
                # skip the test if the only device found is a invalid device
                if len(devices) == 1:
                    return
                else:
                    continue
            fmt = QAudioFormat()
            for codec in devInfo.supportedCodecs():
                fmt.setCodec(codec)
                for frequency in devInfo.supportedFrequencies():
                    fmt.setFrequency(frequency)
                    for channels in devInfo.supportedChannels():
                        fmt.setChannels(channels)
                        for sampleType in devInfo.supportedSampleTypes():
                            fmt.setSampleType(sampleType)
                            for sampleSize in devInfo.supportedSampleSizes():
                                fmt.setSampleSize(sampleSize)
                                for endian in devInfo.supportedByteOrders():
                                    fmt.setByteOrder(endian)
                                    if devInfo.isFormatSupported(fmt):
                                        return
        self.assert_(False)


if __name__ == '__main__':
    unittest.main()

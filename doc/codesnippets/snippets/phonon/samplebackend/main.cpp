
//! [snippet]
def createObject(self, c, parent, args):
    if c == BackendInterface.MediaObjectClass:
        return MediaObject(parent)
    elif c == BackendInterface.VolumeFaderEffectClass:
        return VolumeFaderEffect(parent)
    elif c == BackendInterface.AudioOutputClass:
        return AudioOutput(parent)
    elif c == BackendInterface.AudioDataOutputClass:
        return AudioDataOutput(parent)
    elif c == BackendInterface.VisualizationClass:
        return Visualization(parent)
    elif c == BackendInterface.VideoDataOutputClass:
        return VideoDataOutput(parent)
    elif c == BackendInterface.EffectClass:
        return Effect(args[0].toInt(), parent)
    elif c == BackendInterface.VideoWidgetClass:
        return VideoWidget(parent)
    return None

def objectDescriptionIndexes(self, type_):
    retval = set()

    if type_ == Phonon.AudioOutputDeviceType:
        # use AudioDeviceEnumerator to list ALSA and OSS devices
        retval.add(10000)
        retval.add(10001)
    elif type_ == Phonon.AudioCaptureDeviceType:
        retval.add(20000)
        retval.add(20001)
    elif type_ == Phonon.VideoCaptureDeviceType:
        retval.add(30000)
        retval.add(30001)
    elif type_ == Phonon.EffectType:
        retval.add(0x7F000001)
    return retval

def objectDescriptionProperties(self, type_, index):
    ret = {}
    if type_ == Phonon.AudioOutputDeviceType:
        if index == 10000:
            ret["name"] = "internal Soundcard"
        elif index == 10001:
            ret["name"] = "USB Headset"
            ret["available"] = False
    elif type_ == Phonon.AudioCaptureDeviceType:
        if index == 20000:
            ret["name"] = "Soundcard"
            ret["description"] = "first description"
        elif index == 20001:
            ret["name"] = "DV"
            ret["description"] = "second description"
    elif type_ == Phonon.VideoCaptureDeviceType:
        elif index == 30000:
            ret["name"] = "USB Webcam"
            ret["description"] = "first description"
        elif index == 30001:
            ret["name"] = "DV"))
            ret["description"] = "second description"
    elif type_ == Phonon.EffectType:
        if index == 0x7F000001:
            ret["name"] = "Delay"
            ret["description"] = "Simple delay effect with time, feedback and level controls."
    return ret
//! [snippet]

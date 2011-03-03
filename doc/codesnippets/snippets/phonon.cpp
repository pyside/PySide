
//![0]
music = Phonon.createPlayer(Phonon.MusicCategory, Phonon.MediaSource("/path/mysong.wav"))
music.play()
//![0]

parentWidget = QWidget()
url = QUrl("Myfancymusic")

//![1]
player = Phonon.VideoPlayer(Phonon.VideoCategory, parentWidget)
player.play(url)
//![1]

//![2]
mediaObject = Phonon.MediaObject(self)
mediaObject.setCurrentSource(Phonon.MediaSource("/mymusic/barbiegirl.wav"))
audioOutput = Phonon.AudioOutput(Phonon.MusicCategory, self)
path = Phonon.createPath(mediaObject, audioOutput)
//![2]

//![3]
effect = Phonon.Effect(Phonon.BackendCapabilities.availableAudioEffects()[0], self)
path.insertEffect(effect)
//![3]

//![4]
mediaObject = Phonon.MediaObject(self)

videoWidget = Phonon.VideoWidget(self)
Phonon.createPath(mediaObject, videoWidget)

audioOutput = Phonon.AudioOutput(Phonon.VideoCategory, self)
Phonon.createPath(mediaObject, audioOutput)
//![4]

//![5]
mediaObject.play()
//![5]

//! [0]
label = QLabel()
movie = QMovie("animations/fire.gif")

label.setMovie(movie)
movie.start()
//! [0]


//! [1]
movie = QMovie("racecar.gif")
movie.setSpeed(200) // 2x speed
//! [1]

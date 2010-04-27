//! [0]
while True:
    mutex.lock()
    keyPressed.wait(mutex)
    do_something()
    mutex.unlock()
//! [0]


//! [1]
while True:
    getchar()
    keyPressed.wakeAll()

//! [1]


//! [2]
while True:
    mutex.lock()
    keyPressed.wait(&mutex)
    count += 1
    mutex.unlock()

    do_something()

    mutex.lock()
    count -= 1
    mutex.unlock()
//! [2]


//! [3]
while True:
    getchar()

    mutex.lock()
    # Sleep until there are no busy worker threads
    while count > 0:
        mutex.unlock()
        sleep(1)
        mutex.lock()
    keyPressed.wakeAll()
    mutex.unlock()
//! [3]

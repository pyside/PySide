//! [0]
number = 6

def method1():
    number *= 5
    number /= 4

def method2():
    number *= 3
    number /= 2
//! [0]


//! [1]
# method1()
number *= 5        # number is now 30
number /= 4        # number is now 7

# method2()
number *= 3        # number is now 21
number /= 2        # number is now 10
//! [1]


//! [2]
# Thread 1 calls method1()
number *= 5        # number is now 30

# Thread 2 calls method2().
#
# Most likely Thread 1 has been put to sleep by the operating
# system to allow Thread 2 to run.
number *= 3        # number is now 90
number /= 2        # number is now 45

# Thread 1 finishes executing.
number /= 4        # number is now 11, instead of 10
//! [2]


//! [3]
mutex = QMutex()
number = 6

def method1():
    mutex.lock()
    number *= 5
    number /= 4
    mutex.unlock()

def method2():
    mutex.lock()
    number *= 3
    number /= 2
    mutex.unlock()
//! [3]


//! [4]
def complexFunction(flag):
    mutex.lock()

    retVal = 0

    if flag == 0 or flag == 1:
        mutex.unlock()
        return moreComplexFunction(flag)
    elif flag == 2:
        status = anotherFunction()
        if status < 0:
            mutex.unlock()
            return -2
        retVal = status + flag
    else:
        if flag > 10:
            mutex.unlock()
            return -1

    mutex.unlock()
    return retVal
//! [4]


//! [5]
def complexFunction(flag):
    locker = QMutexLocker(mutex)

    retVal = 0

    if flag == 0 or flag == 1:
        return moreComplexFunction(flag)
    elif flag == 2:
            status = anotherFunction()
            if status < 0:
                return -2
            retVal = status + flag
    else:
        if flag > 10:
            return -1

    return retVal
//! [5]


//! [6]
class SignalWaiter:
    def __init__(mutex):
        self.locker = mutex

    def waitForSignal():
        # ...
        while not signalled:
            waitCondition.wait(self.locker.mutex())
        # ...
//! [6]

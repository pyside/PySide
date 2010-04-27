//! [0]
class Number:
    def __init__(n):
        self.num = n
//! [0]


//! [1]
def calcSquare(number):
    locker = QMutexLocker(mutexpool.get(number))
    number.num = number.num * number.num
//! [1]

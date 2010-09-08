import atexit
from QtCore import __moduleShutdown

atexit.register(__moduleShutdown)

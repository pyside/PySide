#!/usr/bin/env python

import time,os

class TimeoutException(Exception):
   def __init__(self, msg):
      self.msg = msg

   def __str__(self):
      return repr(self.msg)

class ProcessTimer(object):
   '''Timeout function for controlling a subprocess.Popen instance.

   Naive implementation using busy loop, see later other means
   of doing this.
   '''

   def __init__(self, proc, timeout):
      self.proc = proc
      self.timeout = timeout

   def waitfor(self):
      time_passed = 0
      while(self.proc.poll() is None and time_passed < self.timeout):
         time_passed = time_passed + 1
         time.sleep(1)

      if time_passed >= self.timeout:
         raise TimeoutException("Timeout expired, possible deadlock")

if __name__ == "__main__":
   #simple example

   from subprocess import Popen

   proc = Popen(['sleep','10'])
   t = ProcessTimer(proc,5)
   try:
      t.waitfor()
   except TimeoutException:
      print "timeout - PID: %d" % (t.proc.pid)
      #TODO: detect SO and kill accordingly
      #Linux
      os.kill(t.proc.pid, 9)
      #Windows (not tested)
      #subprocess.Popen("taskkill /F /T /PID %i"%handle.pid , shell=True)
   print "exit code: %d" % (t.proc.poll())


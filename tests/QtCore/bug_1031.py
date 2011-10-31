from PySide.QtCore import QStateMachine, QState

mach = QStateMachine()
state = QState(mach)
print(state.machine())

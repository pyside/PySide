//! [0]
    engine = QScriptEngine()
    debugger = QScriptEngineDebugger()
    debugger.attachTo(engine)
//! [0]

//! [1]
    engine.evaluate("debugger")
//! [1]

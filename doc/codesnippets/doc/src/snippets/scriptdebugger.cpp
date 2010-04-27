
#include <QtGui>
#include <QtScript>
#include <QtScriptTools>

// Perhaps shpw entire example for getting debugger up with script
int main(int argv, char **args)
{
    QApplication app(argv, args);

     QString fileName("helloscript.qs");
     QFile scriptFile(fileName);
     scriptFile.open(QIODevice::ReadOnly);
     QTextStream stream(&scriptFile);
     QString contents = stream.readAll();
     scriptFile.close();

    QScriptEngine *engine = new QScriptEngine();

    QScriptEngineDebugger *debugger = new QScriptEngineDebugger();
    debugger->attachTo(engine);

    // Set up configuration with only stack and code
    QWidget *widget = new QWidget;
//![0]
    codeWindow = debugger.widget(QScriptEngineDebugger.CodeWidget)
    stackWidget = debugger.widget(QScriptEngineDebugger.StackWidget)

    layout = QHBoxLayout()
    layout.addWidget(codeWindow)
    layout.addWidget(stackWidget)
//![0]

//![1]
    continueAction = debugger.action(QScriptEngineDebugger.ContinueAction)
    stepOverAction = debugger.action(QScriptEngineDebugger.StepOverAction)
    stepIntoAction = debugger.action(QScriptEngineDebugger.StepIntoAction)

    toolBar = QToolBar()
    toolBar.addAction(continueAction)
//![1]
    toolBar->addAction(stepOverAction);
    toolBar->addAction(stepIntoAction);

    layout->addWidget(toolBar);
    continueAction->setIcon(QIcon("copy.png"));

    debugger->setAutoShowStandardWindow(false);

    widget->setLayout(layout);
    widget->show();

     QPushButton button;
     QScriptValue scriptButton = engine->newQObject(&button);
     engine->globalObject().setProperty("button", scriptButton);

//![2]
     debugger.action(QScriptEngineDebugger.InterruptAction).trigger()
     engine.evaluate(contents, fileName)
//![2]

    return app.exec();
}


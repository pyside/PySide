/* There is a Qt BUG for versions >= 4.7.2 and < 4.8.0. What's happening is that
 * a timer is unregistered twice, once by first by ~QObject and then by
 * ~QTreeWidget or ~QTreeView.
 *
 * So the proposed workaround was to register a new message handler for omiting
 * Qt's warning messages related to timer unregister.
 *
 * Note: if the incoming message is a non-timer-related one, it will be
 * normally printed on the screen, otherwise it won't.
 *
 * You read more about this bug at:
 * https://bugreports.qt.nokia.com/browse/QTBUG-16175
 */
#if QT_VERSION >= 0x040702 && QT_VERSION < 0x040800

/* This function will omit Qt's warning messages by working it around with
 * another message handler which only breaks out when it's an incoming warning
 * message.
 */
static inline void messageHandler(QtMsgType type, const char* s)
{
    switch (type) {
    case QtDebugMsg:
    case QtCriticalMsg:
        std::cerr << s << std::endl;
        break;
    case QtFatalMsg:
        std::cerr << s << std::endl;
        abort();
    case QtWarningMsg:
        QRegExp rx("^.*[\\s]+unregister timer.*Fix application.*$");

        rx.setMinimal(true);

        if (!rx.exactMatch(s))
            std::cerr << s << std::endl;

        break;
    }
}

static inline void omitTimerWarningMessages(void)
{
    qInstallMsgHandler(messageHandler);
}

#else

static inline void omitTimerWarningMessages(void)
{
}

#endif

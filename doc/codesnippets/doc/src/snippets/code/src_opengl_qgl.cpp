//! [0]
fmt = QGLFormat()
fmt.setAlpha(True)
fmt.setStereo(True)
QGLFormat.setDefaultFormat(fmt)
//! [0]


//! [1]
fmt = QGLFormat()
fmt.setDoubleBuffer(False)                 # single buffer
fmt.setDirectRendering(False)              # software rendering
myWidget = MyGLWidget(fmt, ...)
//! [1]


//! [2]
fmt = QGLFormat()
fmt.setOverlay(True)
fmt.setStereo(True)
myWidget = MyGLWidget(fmt, ...)
if !myWidget.format().stereo():
    # ok, goggles off
    if !myWidget.format().hasOverlay():
        print "Cool hardware required"
//! [2]


//! [3]
# The rendering in MyGLWidget depends on using
# stencil buffer and alpha channel

class MyGLWidget(QGLWidget):
    def __init__(self, parent):
        QGLWidget.__init__(self, QGLFormat(QGL.StencilBuffer | QGL.AlphaChannel), parent)

        if !format().stencil():
            print "Could not get stencil buffer results will be suboptimal"
        if !format().alpha():
            print "Could not get alpha channel results will be suboptimal"
    ...
//! [3]


//! [4]
a = QApplication([])
f = QGLFormat()
f.setDoubleBuffer(False)
QGLFormat.setDefaultFormat(f)
//! [4]


//! [5]
f = QGLFormat.defaultOverlayFormat()
f.setDoubleBuffer(True)
QGLFormat.setDefaultOverlayFormat(f)
//! [5]


//! [6]
# ...continued from above
myWidget = MyGLWidget(QGLFormat(QGL.HasOverlay), ...)
if myWidget.format().hasOverlay():
    # Yes, we got an overlay, let's check _its_ format:
    olContext = myWidget.overlayContext()
    if olContext.format().doubleBuffer():
         # yes, we got a double buffered overlay
    else:
         # no, only single buffered overlays are available
//! [6]


//! [7]
cx = QGLContext()
#  ...
f = QGLFormat()
f.setStereo(True)
cx.setFormat(f)
if !cx.create():
    exit() # no OpenGL support, or cannot render on the specified paintdevice
if !cx.format().stereo():
    exit() # could not create stereo context
//! [7]


//! [8]
class MyGLDrawer(QGLWidget):

    def __init__(self, parent):
        QGLWidget.__init__(self, parent)
        pass

    def initializeGL(self):
        # Set up the rendering context, define display lists etc.:
        ...
        glClearColor(0.0, 0.0, 0.0, 0.0)
        glEnable(GL_DEPTH_TEST)
        ...
    
    def resizeGL(self, w, h):
        # setup viewport, projection etc.:
        glViewport(0, 0, w, h)
        ...
        glFrustum(...)
        ...

    def paintGL(self):
        # draw the scene:
        ...
        glRotatef(...)
        glMaterialfv(...)
        glBegin(GL_QUADS)
        glVertex3f(...)
        glVertex3f(...)
        ...
        glEnd()
        ...
//! [8]

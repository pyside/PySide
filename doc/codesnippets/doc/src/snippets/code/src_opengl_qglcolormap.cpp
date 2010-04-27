//! [0]
import sys

from PySide.QtGui import QApplication, qRgb
from PySide.QtOpenGL import QGLColormap

def main(argv):
    app = QApplication(argv)

    widget = MySuperGLWidget()     # a QGLWidget in color-index mode
    colormap = QGLColormap()

    # This will fill the colormap with colors ranging from
    # black to white.
    for i in range(0, colormap.size()):
        colormap.setEntry(i, qRgb(i, i, i))

    widget.setColormap(colormap)
    widget.show()
    return app.exec_()

if __name__ == "__main__":
    main(sys.argv)
//! [0]

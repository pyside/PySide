//! [0]
shader = QGLShader(QGLShader.Vertex)
shader.compileSourceCode(code)

program = QGLShaderProgram(context)
program.addShader(shader)
program.link()

program.bind()
//! [0]

//! [1]
program.addShaderFromSourceCode(QGLShader.Vertex,
    "attribute highp vec4 vertex\n" \
    "attribute mediump mat4 matrix\n" \
    "void main(void)\n" \
    "{\n" \
    "   gl_Position = matrix * vertex\n" \
    "}")
program.addShaderFromSourceCode(QGLShader.Fragment,
    "uniform mediump vec4 color\n" \
    "void main(void)\n" \
    "{\n" \
    "   gl_FragColor = color\n" \
    "}")
program.link()
program.bind()

vertexLocation = program.attributeLocation("vertex")
matrixLocation = program.attributeLocation("matrix")
colorLocation = program.uniformLocation("color")
//! [1]

//! [2]
triangleVertices = (
    60.0f,  10.0f,  0.0f,
    110.0f, 110.0f, 0.0f,
    10.0f,  110.0f, 0.0f)

color = QColor(0, 255, 0, 255)

pmvMatrix = QMatrix4x4()
pmvMatrix.ortho(self.rect())

program.enableAttributeArray(vertexLocation)
program.setAttributeArray(vertexLocation, triangleVertices, 3)
program.setUniformValue(matrixLocation, pmvMatrix)
program.setUniformValue(colorLocation, color)

glDrawArrays(GL_TRIANGLES, 0, 3)

program.disableAttributeArray(vertexLocation)
//! [2]

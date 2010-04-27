//! [0]
pbuffer QGLPixelBuffer(...)
...
pbuffer.makeCurrent()
dynamicTexture = pbuffer.generateDynamicTexture()
pbuffer.bindToDynamicTexture(dynamicTexture)
...
pbuffer.releaseFromDynamicTexture()
//! [0]


//! [1]
pbuffer QGLPixelBuffer(...)
...
pbuffer.makeCurrent()
dynamicTexture = pbuffer.generateDynamicTexture()
...
pbuffer.updateDynamicTexture(dynamicTexture)
//! [1]


//! [adding a corner anchor in two steps]
layout.addAnchor(a, Qt.AnchorTop, layout, Qt.AnchorTop)
layout.addAnchor(a, Qt.AnchorLeft, layout, Qt.AnchorLeft)
//! [adding a corner anchor in two steps]

//! [adding a corner anchor]
layout.addCornerAnchors(a, Qt.TopLeftCorner, layout, Qt.TopLeftCorner)
//! [adding a corner anchor]

//! [adding anchors]
layout.addAnchor(b, Qt.AnchorLeft, a, Qt.AnchorRight)
layout.addAnchor(b, Qt.AnchorTop, a, Qt.AnchorBottom)
//! [adding anchors]

//! [adding anchors to match sizes in two steps]
layout.addAnchor(b, Qt.AnchorLeft, c, Qt.AnchorLeft)
layout.addAnchor(b, Qt.AnchorRight, c, Qt.AnchorRight)
//! [adding anchors to match sizes in two steps]

//! [adding anchors to match sizes]
layout.addAnchors(b, c, Qt.Horizontal)
//! [adding anchors to match sizes]

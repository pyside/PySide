import Qt 4.7

Text {
    text: owner.name + " " + owner.phone 
    Component.onCompleted: { owner.newName = owner.name }
}

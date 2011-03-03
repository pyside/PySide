import QtQuick 1.0
import "ImageProviderCore" // import the plugin that registers the color image provider

//![0]
Column {
    Image { source: "image://colors/yellow" }
    Image { source: "image://colors/red" }
}
//![0]

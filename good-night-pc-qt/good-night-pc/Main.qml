import QtQuick
import QtWebView
import QtQuick.Controls

Window {
    width: 480
    height: 720
    visible: true
    title: qsTr("Hello World")

    flags: Qt.Window |
           Qt.WindowTitleHint |
           Qt.WindowSystemMenuHint |
           Qt.WindowMaximizeButtonHint |
           Qt.WindowMinimizeButtonHint

    WebView{
        id: webview
        anchors.fill: parent

        url: "http://127.0.0.1:8080/index.html"

        Button{
            text: "Click me!"
        }
    }
}

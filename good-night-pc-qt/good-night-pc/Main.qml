import QtQuick
import QtWebView
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    WebView{
        id: webview
        anchors.fill: parent

        // anchors {
        //     top:    parent.top
        //     left:   parent.left
        //     right:  parent.right
        // }
        // height: parent.height / 2

        url: "http://127.0.0.1:8080/index.html"
        //url: "http://127.0.0.1:8080/api/hello"
        //url: "https://www.wp.pl"

        Button{
            text: "Click me!"
        }

    }

    // Rectangle{
    //     anchors {
    //         top:    webview.bottom
    //         left:   parent.left
    //         right:  parent.right
    //         bottom: parent.bottom
    //     }
    //     color: "red"

    //     Button{
    //         text: "Click me!"
    //     }
    // }


}

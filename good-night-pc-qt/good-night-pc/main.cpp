#include <QGuiApplication>
#include <QHttpServer>
#include <QMimeDatabase>
#include <QQmlApplicationEngine>
#include <QTcpServer>
#include <QWebChannel>
#include <QWebSocketServer>
#include <QtWebView>

#include "./backend/backend.h"
#include "./frontend/websocketclientwrapper.h"
#include "./frontend/websockettransport.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtWebView::initialize();

    //-----BACKEND--------

    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
                            QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::LocalHost, 12345)) {
        qFatal("Failed to open web socket server.");
        return 1;
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    QWebChannel channel;
    QObject::connect(&clientWrapper,
                     &WebSocketClientWrapper::clientConnected,
                     &channel,
                     &QWebChannel::connectTo);

    Backend backend(&app);
    channel.registerObject(QStringLiteral("backend"), &backend);

    //-------------------

    //http server for host app gui
    QHttpServer httpServer;

    // Używamy ".*", co oznacza: wyłap absolutnie każde zapytanie URL
    httpServer.route(".*", [](const QHttpServerRequest &request) {
        QString path = request.url().path();

        // Jeśli ktoś wchodzi na sam adres "127.0.0.1:8080/", dajmy mu domyślnie index.html
        if (path == "/" || path == "") {
            path = "/index.html";
        }

        // Budujemy poprawną ścieżkę do pliku w systemie zasobów Qt (QRC)
        // Wynik np.: ":/assets/www/index.html"
        QString qrcPath = ":/assets/www" + path;
        QFile file(qrcPath);

        if (file.open(QIODevice::ReadOnly)) {
            // Automatyczne rozpoznawanie MIME
            QMimeDatabase mimeDb;
            QString mimeType = mimeDb.mimeTypeForFile(qrcPath).name();

            return QHttpServerResponse(mimeType.toUtf8(), file.readAll());
        }

        // Jeśli pliku nie ma w Qt Resources (np. zapytanie o favicone)
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NotFound);
    });

    httpServer.route("/api/hello", []() {
        QString textFromCpp = "Hello World form C++ backend!";
        return QHttpServerResponse("text/plain", textFromCpp.toUtf8());
    });

    auto tcpserver = new QTcpServer();
    if (!tcpserver->listen(QHostAddress::LocalHost, 8080) || !httpServer.bind(tcpserver)) {
        delete tcpserver;
        return -1;
    }
    //----------------------------

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("good-night-pc", "Main");

    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSslSocket>
#include <QtWebView>
#include <QQuickStyle>

#include "application.h"

int main(int argc, char *argv[])
{
    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QtWebView::initialize();
    QQuickStyle::setStyle("Material");

    app.setOrganizationName("KNU University");
    app.setApplicationDisplayName("Ukraine Guide");
    app.setApplicationName("Ukraine Guide");
    Application ukraineGuideApp;

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    // register types in qml
    LocalityType::declareQML();
    LocalityListModel::declareQML();
    LocalityModel::declareQML();
    EstablishmentsListModel::declareQML();
    RoutesListModel::declareQML();

    // make needed objects be in QML context as a context properties
    QQmlContext *context = engine.rootContext();
    context->setContextProperty(QStringLiteral("application"), &ukraineGuideApp);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

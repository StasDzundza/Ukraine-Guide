#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSslSocket>

#include "application.h"
#include "locality_type.h"
#include "locality_list_model.h"
#include "locality_model.h"

int main(int argc, char *argv[])
{
    qDebug() << "Device supports OpenSSL: " << QSslSocket::supportsSsl();
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setObjectName("KNU University");
    app.setApplicationDisplayName("Ukraine Guide");
    app.setApplicationName("Ukraine Guide");
    Application ukraineGuideApp;

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);

    // register types in qml
    LocalityType::declareQML();
    LocalityListModel::declareQML();
    LocalityModel::declareQML();

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

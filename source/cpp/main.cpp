#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "application.h"
#include "locality_type.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setObjectName("KNU University");
    app.setApplicationDisplayName("Ukraine Guide");
    app.setApplicationName("Ukraine Guide");
    Application ukraineGuideApp;

    QQmlApplicationEngine engine;

    // register types in qml
    LocalityType::declareQML();

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

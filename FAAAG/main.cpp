#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "filterimage.h"


int main(int argc, char *argv[])
{
    qDebug() << "hi";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    FilterImage filters;
    engine.rootContext()->setContextProperty("Filters",&filters);
    engine.addImageProvider("live",&filters);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>



int main(int argc, char *argv[])
{
    qDebug() << "hi";
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

/*
   cv::Mat image = cv::imread("../1.png", 1);
   if(! image.data )                              // Check for invalid input
   {
       qDebug() <<  "Could not open or find the image";
       return -1;
   }
   cv::namedWindow("My Image");
   cv::imshow("My Image", image);
   cv::waitKey(0);

*/
    engine.load(url);
    return app.exec();
}

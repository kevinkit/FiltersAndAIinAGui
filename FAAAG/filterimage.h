#ifndef FILTERIMAGE_H
#define FILTERIMAGE_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QWidget>
#include <qqml.h>
#include <QQuickPaintedItem>
#include <QQuickItem>
#include <QPainter>
#include <QImage>
#include <QImageReader>
#include <QDebug>
#include <QBuffer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QTimer>


/*!
    @brief Filter class for adapint the filters and loading the images
*/
class FilterImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString currentFilter READ currentFilter WRITE setFilter NOTIFY filterChanged)
    Q_PROPERTY(QString representationName READ representationName WRITE setRepresentationName NOTIFY representationNameChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int index READ currentIndex WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int representation READ currentRepresentation WRITE setRepresentation NOTIFY representationChanged)
    Q_PROPERTY(bool liveview  READ liveview WRITE setliveview NOTIFY liveviewChanged)


public:
    explicit FilterImage(QQuickItem *parent = nullptr);
    ~FilterImage();
    //TODO: should maybe put into slots? not sure atm
    Q_INVOKABLE void setImage(const QImage &image);
    Q_INVOKABLE void paint(QPainter *painter) override;
    Q_INVOKABLE void setRepresentation(int idx);

    cv::VideoCapture cam;

    QImage image() const;
    QString currentFilter();
    QString representationName() const;
    int currentIndex();

    int currentRepresentation();

    Q_INVOKABLE QImage executeFiltering();

    QTimer *timer;


    bool liveview() const
    {
        return m_liveview;
    }

public slots:
    void setFilter(const QString &currentFilter);
    void setIndex(int idx);
    void updateImage(const QString filename);
        
    void setRepresentationName(QString representationName);

    void setliveview(bool liveview);

    void frameGrabber();


signals:
    void filterChanged(QString currentFilter);
    void imageChanged();
    void indexChanged();
    void representationChanged();
    void representationNameChanged(QString representationName);

    void liveviewChanged(bool liveview);


private:

    int m_currentFilterIndx;
    int m_currentRepresentation;

    QString filename;
    QString m_currentFilter;

    QImage current_image;
    QImage current_image_gray;
    QImage current_image_fft;
    QImage orig_image;

    cv::Mat current_cv_image;
    cv::Mat current_cv_image_gray;
    cv::Mat current_cv_Image_fft;
    cv::Mat orig_image_cv;
    QString m_representationName;

    bool m_liveview;

};

#endif // FILTERIMAGE_H

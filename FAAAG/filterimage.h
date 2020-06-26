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

/*!
    @brief Filter class for adapint the filters and loading the images
*/
class FilterImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString currentFilter READ currentFilter WRITE setFilter NOTIFY filterChanged)
    Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)
    Q_PROPERTY(int index READ currentIndex WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int representation READ currentRepresentation WRITE setRepresentation NOTIFY representationChanged)

public:
    explicit FilterImage(QQuickItem *parent = nullptr);

    //TODO: should maybe put into slots? not sure atm
    Q_INVOKABLE void setImage(const QImage &image);
    Q_INVOKABLE void paint(QPainter *painter) override;
    Q_INVOKABLE void setRepresentation(int idx);
    
    QImage image() const;
    QString currentFilter();

    int currentIndex();
    int currentRepresentation();

    Q_INVOKABLE void executeFiltering();
    Q_INVOKABLE void executeRepresentationSwitch();

public slots:
    void setFilter(const QString &currentFilter);
    void setIndex(int idx);
    void updateImage(const QString filename);
    
    
signals:
    void filterChanged();
    void imageChanged();
    void indexChanged();
    void representationChanged();
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


};

#endif // FILTERIMAGE_H

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

public:
    explicit FilterImage(QQuickItem *parent = nullptr);

    Q_INVOKABLE void setImage(const QImage &image);
    Q_INVOKABLE void paint(QPainter *painter) override;

    QImage image() const;
    QString currentFilter();

    int currentIndex();
    Q_INVOKABLE void executeFiltering();

public slots:
    void setFilter(const QString &currentFilter);
    void setIndex(int idx);

signals:
    void filterChanged();
    void imageChanged();
    void indexChanged();
private:



    QImage no_image;
    QImage orig_image;
    QString m_currentFilter;
    int m_currentFilterIndx;
    QImage current_image;
    cv::Mat current_cv_image;
    cv::Mat current_cv_image_gray;
};

#endif // FILTERIMAGE_H

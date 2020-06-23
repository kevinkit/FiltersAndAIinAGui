#ifndef FILTERIMAGE_H
#define FILTERIMAGE_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QWidget>
#include <qqml.h>
#include <QImage>
#include <QQuickImageProvider>

/*!
    @brief Filter class for adapint the filters and loading the images
*/
class FilterImage : public QObject, public QQuickImageProvider
{
    Q_OBJECT
    Q_PROPERTY(QString currentFilter READ currentFilter WRITE setFilter NOTIFY filterChanged)
    Q_PROPERTY(int index READ currentIndex WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(QImage image READ getImage WRITE updateImage NOTIFY imageChanged)
    QML_ELEMENT
public:
    FilterImage();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    QString currentFilter();
    QImage getImage();
    int currentIndex();

public slots:
    void setFilter(const QString &currentFilter);
    void setIndex(int idx);
    void updateImage(const QImage &image);
signals:
    void filterChanged();
    void imageChanged(QString parameter);
    void indexChanged();
private:

    void executeFiltering();

    QImage image;
    QImage no_image;
    QImage orig_image;
    QString m_currentFilter;
    int m_currentFilterIndx;

};

#endif // FILTERIMAGE_H

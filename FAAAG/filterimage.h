#ifndef FILTERIMAGE_H
#define FILTERIMAGE_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QWidget>
#include <qqml.h>
#include <QImage>
#include <QQuickImageProvider>



class FilterImage : public QObject, public QQuickImageProvider
{
    Q_OBJECT
    Q_PROPERTY(QString currentFilter READ currentFilter WRITE setFilter NOTIFY filterChanged)
    QML_ELEMENT
public:
    FilterImage();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    QString currentFilter();
    QString m_currentFilter;
    QImage m_qimage;

public slots:
    void setFilter(const QString &currentFilter);
    void updateImage(const QImage &image);
signals:
    void filterChanged();
    void imageChanged();
private:
    QImage image;
    QImage no_image;


};

#endif // FILTERIMAGE_H

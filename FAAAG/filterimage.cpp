#include <QDebug>
#include <QFileDialog>
#include "filterimage.h"
#include <QBuffer>

FilterImage::FilterImage() : QQuickImageProvider(QQuickImageProvider::Image)
{
    m_currentFilter = "No filter";
    m_qimage = QImage("file:/../../1.png");
    this->no_image = QImage("file:/../../1.png");
    this->blockSignals(false);
}

QString FilterImage::currentFilter()
{
    return this->m_currentFilter;
}

void FilterImage::setFilter(const QString &currentFilter)
{
    if(currentFilter == this->m_currentFilter)
        return;

    qDebug() << "filter changed" << currentFilter;

    this->m_currentFilter = currentFilter;
    emit filterChanged();
}

QImage FilterImage::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    QImage result = this->image;

    if(result.isNull()) {
        result = this->no_image;
    }

    if(size) {
        *size = result.size();
    }

    if(requestedSize.width() > 0 && requestedSize.height() > 0) {
        result = result.scaled(requestedSize.width(), requestedSize.height(), Qt::KeepAspectRatio);
    }

    return result;
}

void FilterImage::updateImage(const QImage &image)
{
    if(this->image != image) {
        this->image = image;
        emit imageChanged();
    }
}

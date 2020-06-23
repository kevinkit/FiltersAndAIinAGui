#include <QDebug>
#include <QFileDialog>
#include "filterimage.h"
#include <QBuffer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

FilterImage::FilterImage() : QQuickImageProvider(QQuickImageProvider::Image)
{
    m_currentFilter = "No filter";
    this->no_image = QImage("file:/../../1.png");
    this->orig_image = QImage("file:/../../1.png");
    this->image =  QImage("file:/../../1.png");
    this->blockSignals(false);
}

QString FilterImage::currentFilter()
{
    return this->m_currentFilter;
}

QImage FilterImage::getImage()
{
    return this->image;
}

int FilterImage::currentIndex()
{
    return this->m_currentFilterIndx;
}

void FilterImage::setIndex(int idx)
{
    if(m_currentFilterIndx == idx)
        return;

    qDebug() << "Index changed!" << idx;
    this->m_currentFilterIndx = idx;
    executeFiltering();
    emit indexChanged();
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
        qDebug() << "Changed image!";
        emit imageChanged("image://live/image");
    }else{
        qDebug() << "Still the same";
    }
}

/*!
    @brief Function for executiing the used filter on it
*/
void FilterImage::executeFiltering(){

    cv::Mat src_gray,dst,abs_dst,temp;
    //Create cv mat
    cv::Mat mat(this->image.height(),
                this->image.width(),
                CV_8UC3,
                this->image.bits(),
                this->image.bytesPerLine());


    cv::cvtColor(mat,src_gray,cv::COLOR_RGB2GRAY);
    switch(this->m_currentFilterIndx){
        case 0: this->updateImage(this->orig_image); break;
        case 1: {
                    cv::Laplacian(src_gray,dst,CV_8U,1,0,cv::BORDER_DEFAULT);
                    cv::convertScaleAbs(dst,abs_dst);
                    cvtColor(src_gray, temp,cv::COLOR_GRAY2RGB);
                    //convert back to qimage
                    qDebug() << "here";
                    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                    this->updateImage(dest);
                    namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
                    cv::imshow( "Display window", dst );                   // Show our image inside it.

                    cv::waitKey(0);
                    break;
                }

        case 2: break;
        case 3: break;
    }
}

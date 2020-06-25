#include "filterimage.h"
#include <QFileInfo>

FilterImage::FilterImage(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->current_image = QImage("file:/../../1.png");
    this->current_cv_image = cv::imread("./../1.png");

    this->orig_image = QImage("file:/../../1.png");
    this->orig_image_cv = cv::imread("./../1.png");
    cv::cvtColor(cv::imread("./../1.png"),this->current_cv_image_gray,cv::COLOR_BGR2GRAY);

    this->m_currentFilterIndx = 0;
}

QString FilterImage::currentFilter()
{
    return this->m_currentFilter;
}

void FilterImage::paint(QPainter *painter)
{

    qDebug() << "in paint func";
    QRectF bounding_rect = boundingRect();
    QImage scaled = this->current_image.scaledToHeight(bounding_rect.height());
    QPointF center = bounding_rect.center() - scaled.rect().center();

    if(center.x() < 0)
        center.setX(0);
    if(center.y() < 0)
        center.setY(0);
    painter->drawImage(center, scaled);
    qDebug() << "drawn!";
}



QImage FilterImage::image() const
{
    qDebug() << "image was requested";
    return this->current_image;
}

void FilterImage::setImage(const QImage &image)
{
    qDebug() << "image updated";
    this->current_image = image;
    update();
    emit imageChanged();
}

int FilterImage::currentIndex()
{
    return this->m_currentFilterIndx;
}

void FilterImage::setIndex(int idx)
{
    qDebug() << "in in dex";
    if(m_currentFilterIndx == idx)
        return;
    this->m_currentFilterIndx = idx;
    executeFiltering();
    emit indexChanged();
}

void FilterImage::updateImage(const QString filename)
{
    QString adapted = filename.mid(8);
    QImageReader reader(adapted);
    QImage new_image = reader.read();
    this->current_cv_image = cv::imread(adapted.toUtf8().constData());
    cv::cvtColor(this->current_cv_image,this->current_cv_image_gray,cv::COLOR_BGR2GRAY);
    cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
    cv::imshow( "Display window", this->current_cv_image_gray );                   // Show our image inside it.

    cv::waitKey(0);
    this->orig_image = new_image.copy();
    this->setImage(new_image.copy());
}


void FilterImage::setFilter(const QString &currentFilter)
{
    qDebug() << "in filter";

    if(currentFilter == this->m_currentFilter)
        return;

    qDebug() << "filter changed" << currentFilter;

    this->m_currentFilter = currentFilter;
    this->executeFiltering();
    emit filterChanged();

}


/*!
    @brief Function for executiing the used filter on it
*/
void FilterImage::executeFiltering(){

    qDebug() << this->m_currentFilterIndx;
    cv::Mat src_gray,dst,abs_dst,temp;

    switch(this->m_currentFilterIndx){
        case 0: this->setImage(this->orig_image); qDebug() << "just did the 0 thing"; break;
        case 1: {
                    cv::Sobel(this->current_cv_image_gray,dst,CV_16S,0,1,3,cv::BORDER_DEFAULT);
                    cv::convertScaleAbs(dst,abs_dst);
                    cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                    this->setImage(dest.copy());
                    break;
                }

        case 2:{
                cv::GaussianBlur(this->current_cv_image_gray,dst,cv::Size(3,3),0,0);
                cv::convertScaleAbs(dst,abs_dst);
                cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                this->setImage(dest.copy());
                 break;
                }
        case 3: {
                cv::medianBlur(this->current_cv_image_gray,dst,3);
                cv::convertScaleAbs(dst,abs_dst);
                cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                this->setImage(dest.copy());
                 break;
                }
    }
}

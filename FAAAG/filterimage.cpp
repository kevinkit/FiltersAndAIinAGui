#include "filterimage.h"
#include <QFileInfo>

/*!
 * \brief FilterImage::FilterImage
 * \param parent
 */
FilterImage::FilterImage(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    QImage qimg = QImage("file:/../../1.png");
    this->current_image = qimg;
    this->current_cv_image = cv::imread("./../1.png");

    this->orig_image = qimg;
    this->orig_image_cv = cv::imread("./../1.png");

    this->current_image_gray = qimg.copy();
    this->current_image_gray.convertTo(QImage::Format_Grayscale8);

    cv::cvtColor(cv::imread("./../1.png"),this->current_cv_image_gray,cv::COLOR_BGR2GRAY);

    //see: https://docs.opencv.org/3.4/d8/d01/tutorial_discrete_fourier_transform.html
    cv::Mat padded,complex,tmp,abs_dst,temp;
    cv::Mat gray = cv::imread("./../1.png",cv::IMREAD_GRAYSCALE);
    int m = cv::getOptimalDFTSize(gray.rows);
    int n = cv::getOptimalDFTSize(gray.cols);

    cv::copyMakeBorder(gray,padded,0,m-gray.rows,0,n-gray.cols,cv::BORDER_CONSTANT,cv::Scalar::all(0));
    cv::Mat planes[] = {cv::Mat_<float>(padded),cv::Mat::zeros(padded.size(),CV_32F)};
    cv::merge(planes,2,complex);

    cv::dft(complex, complex);

    cv::split(complex, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    cv::Mat mag = planes[0];

    //going to a log scale
    mag += cv::Scalar::all(1);
    cv::log(mag,mag);

    // crop the spectrum, if it has an odd number of rows or columns
    mag = mag(cv::Rect(0, 0, mag.cols & -2, mag.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = mag.cols/2;
    int cy = mag.rows/2;
    cv::Mat q0(mag, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1(mag, cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2(mag, cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3(mag, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    q0.copyTo(tmp);                     // swap quadrants (Top-Left with Bottom-Right)
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);


    cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX); // Transform the matrix with float values into a
                                                      // viewable image form (float between values 0 and 1).

    mag.copyTo(this->current_cv_Image_fft);

    cv::convertScaleAbs(255*mag,abs_dst);
    cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    this->current_image_fft = dest.copy();

    qDebug() << mag.channels();
    this->m_currentFilterIndx = 0;
}

/*!
 * \brief getter Function for the current filter applied as a string
 */
QString FilterImage::currentFilter()
{
    return this->m_currentFilter;
}

/*!
 * \brief FilterImage::paint Will repaint the shown image
 * \param painter QPainter Object pointer
 */
void FilterImage::paint(QPainter *painter)
{

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

void FilterImage::setRepresentation(int idx)
{
    if (this->m_currentRepresentation == idx)
        return;
    this->m_currentRepresentation = idx;
    this->executeFiltering();
    update();
    emit imageChanged();

}

/*!
 * \brief FilterImage::image Getter function for the current image
 * \return QImage 
 */
QImage FilterImage::image() const
{
    return this->current_image;
}

/*!
 * \brief FilterImage::setImage Setter function for the image, call with a copy to make sure 
 * that the memory is copied deep. Will call the update function and emit the signal the 
 * image was changed
 * \param image  
 */
void FilterImage::setImage(const QImage &image)
{
    this->current_image = image.copy();
   // QImage gray = image.convertToFormat(QImage::Format_Grayscale8);
   // this->current_image_gray = gray.copy();
    update();
    emit imageChanged();
}

int FilterImage::currentIndex()
{
    return this->m_currentFilterIndx;
}

int FilterImage::currentRepresentation()
{
    return this->m_currentRepresentation;
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

    //RGB
    this->orig_image = new_image;

    this->current_cv_image = cv::imread(adapted.toUtf8().constData());

    //Gray Image
    cv::cvtColor(this->current_cv_image,this->current_cv_image_gray,cv::COLOR_BGR2GRAY);
    QImage gray = new_image.convertToFormat(QImage::Format_Grayscale8);
    this->current_image_gray = gray.copy();

    //DFT
    cv::Mat padded,complex,tmp,abs_dst,temp;
    int m = cv::getOptimalDFTSize(this->current_cv_image_gray.rows);
    int n = cv::getOptimalDFTSize(this->current_cv_image_gray.cols);
    cv::copyMakeBorder(this->current_cv_image_gray,padded,0,m-this->current_cv_image_gray.rows,0,n-this->current_cv_image_gray.cols,cv::BORDER_CONSTANT,cv::Scalar::all(0));
    cv::Mat planes[] = {cv::Mat_<float>(padded),cv::Mat::zeros(padded.size(),CV_32F)};
    cv::merge(planes,2,complex);

    cv::dft(complex, complex);

    cv::split(complex, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    cv::magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    cv::Mat mag = planes[0];

    //going to a log scale
    mag += cv::Scalar::all(1);
    cv::log(mag,mag);

    // crop the spectrum, if it has an odd number of rows or columns
    mag = mag(cv::Rect(0, 0, mag.cols & -2, mag.rows & -2));

    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = mag.cols/2;
    int cy = mag.rows/2;
    cv::Mat q0(mag, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1(mag, cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2(mag, cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3(mag, cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    q0.copyTo(tmp);                     // swap quadrants (Top-Left with Bottom-Right)
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);


    cv::normalize(mag, mag, 0, 1, cv::NORM_MINMAX); // Transform the matrix with float values into a
                                                      // viewable image form (float between values 0 and 1).

    mag.copyTo(this->current_cv_Image_fft);

    cv::convertScaleAbs(255*mag,abs_dst);
    cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
    QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    this->current_image_fft = dest.copy();

    //set current Image
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
        case 0: {
             switch(this->m_currentRepresentation){
                case 0: this->setImage(this->orig_image); break;
                case 1: this->setImage(this->current_image_gray); break;
                case 2: this->setImage(this->current_image_fft); break;
                default : this->setImage(this->orig_image); break;

             }
             break;
        }

        this->setImage(this->orig_image); return;
        case 1: {
                    //switch according to representation
                    switch(this->m_currentRepresentation){
                    case 0:{
                        cv::Sobel(this->current_cv_image,dst,CV_16S,0,1,3,cv::BORDER_DEFAULT);
                        cv::convertScaleAbs(dst,abs_dst);
                        cv::cvtColor(abs_dst,temp,cv::COLOR_RGB2BGR);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                    }
                    case 1:{
                        cv::Sobel(this->current_cv_image_gray,dst,CV_16S,0,1,3,cv::BORDER_DEFAULT);
                        cv::convertScaleAbs(dst,abs_dst);
                        cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                        }
                    case 2:{
                        cv::Sobel(255*this->current_cv_Image_fft,dst,CV_16S,0,1,3,cv::BORDER_DEFAULT);
                        cv::convertScaleAbs(dst,abs_dst);
                        cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                        }

                    }
                    break;
                }
        case 2:{
                    //switch according to representation
                    switch(this->m_currentRepresentation){
                    case 0:{
                        cv::GaussianBlur(this->current_cv_image,dst,cv::Size(3,3),0,0);
                        cv::convertScaleAbs(dst,abs_dst);
                        cv::cvtColor(abs_dst,temp,cv::COLOR_RGB2BGR);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                    }
                    case 1:{
                        cv::GaussianBlur(this->current_cv_image_gray,dst,cv::Size(3,3),0,0);
                        cv::convertScaleAbs(dst,abs_dst);
                        cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                        }
                    case 2:{
                        cv::GaussianBlur(255*this->current_cv_Image_fft,dst,cv::Size(3,3),0,0);
                        cv::convertScaleAbs(dst,abs_dst);
                        cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                        }

                    }
                    break;
                }


        case 3:{

                    //switch according to representation
                    switch(this->m_currentRepresentation){
                    case 0:{
                        cv::medianBlur(this->current_cv_image,dst,3);
                        cv::convertScaleAbs(dst,abs_dst);
                        cv::cvtColor(abs_dst,temp,cv::COLOR_RGB2BGR);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                    }
                    case 1:{
                        cv::medianBlur(this->current_cv_image_gray,dst,3);
                        cv::convertScaleAbs(dst,abs_dst);
                        cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                        }
                    case 2:{
                        cv::medianBlur(255*this->current_cv_Image_fft,dst,3);
                        cv::convertScaleAbs(dst,abs_dst);
                        cvtColor(abs_dst, temp,cv::COLOR_GRAY2RGB);
                        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
                        this->setImage(dest.copy());
                        break;
                        }

                    }
                    break;
                }

         default: this->setImage(this->orig_image); return;
    }


}


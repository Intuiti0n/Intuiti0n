#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function
using namespace cv;

int main() {
    cv::Mat img = cv::imread("F:/universidade-eletronica/4ano/42VISAO/image.png",-1);
    Mat inv;
    Mat cinzenta;
    if( img.empty() ) return -1;
    cv::namedWindow( "Example1", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "Example2", cv::WINDOW_AUTOSIZE );

    //flip(img,inv,-1);//>0 horizontal, 0 vertical, <0 ambas
    cvtColor(img,cinzenta,CV_BGR2GRAY);
    //putText();
    /*desligar quadrado numa imagem tons de cinzento*/
    /*for(){
        for(){

        }
    }
    */
    cv::imshow( "Example1", img );
    cv::imshow( "Example2", cinzenta );
    cv::moveWindow("Example1",0,00);

    cv::waitKey( 0 );
    cv::destroyWindow( "Example1" );
}

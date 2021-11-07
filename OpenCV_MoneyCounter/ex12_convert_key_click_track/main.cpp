#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function

using namespace cv;
using namespace std;
Mat img = cv::imread("F:/universidade-eletronica/4ano/42VISAO/image.png",-1);
Mat convert= img;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDBLCLK ){
        cout << "double button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        cvtColor(img,convert,CV_RGB2Lab);
        imshow("Convert",convert);
    }

    else if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        cvtColor(img,convert,CV_RGB2GRAY);
        imshow("Convert",convert);
    }
    else if  ( event == EVENT_RBUTTONDOWN )
    {
        cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        cvtColor(img,convert,CV_RGB2HSV);
        imshow("Convert",convert);
    }
    else if  ( event == EVENT_MBUTTONDOWN )
    {
        cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        cvtColor(img,convert,CV_RGB2HLS);
        imshow("Convert",convert);
    }
    else if ( event == EVENT_MOUSEMOVE )
    {
        //cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }
}

int main() {
    //Mat img = cv::imread("F:/universidade-eletronica/4ano/42VISAO/image.png",-1);


    //if fail to read the image
    if ( img.empty() )
    {
        cout << "Error loading the image" << endl;
        return -1;
    }


    namedWindow( "Example1", cv::WINDOW_AUTOSIZE );//original
    namedWindow("Convert");//convertida

    //set the callback function for any mouse event
    setMouseCallback("Example1", CallBackFunc, NULL);

    //createTrackbar("hello", "Example1", 0, 255, 0 );
    //createTrackbar( "bye", "Convert", 0, 255, 0 );


    //destroyWindow( "Example1" );

    for(;;)
       {
           imshow( "Example1", img );
           int c = waitKey(0);
           if( (c & 255) == 27 )
           {
               cout << "Exiting ...\n";
               break;
           }
           switch( (char)c )
           {
           case '1':
               cvtColor(img,convert,CV_RGB2Lab);
               break;
           case '2':
               cvtColor(img,convert,CV_RGB2GRAY);
               break;
           case '3':
               cvtColor(img,convert,CV_RGB2HSV);
               break;
           case '4':
               cvtColor(img,convert,CV_RGB2HLS);
               break;
           case '5':
               cvtColor(img,convert,CV_RGB2GRAY);
               break;
           default:
               convert=img;
               break;
           }
           imshow("Convert",convert);
       }
    return 0;
}

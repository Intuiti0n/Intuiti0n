#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat img;
//função callback da trackbar, é chamada quando se chama a
/*
 * Draws a line segment connecting two points.

C++:
void line(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
*/
Point first(0,0);
Point last(250,250);
static volatile int flag=0;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    /*
    if  ( event == EVENT_LBUTTONDOWN )
    {
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_RBUTTONDOWN )
    {
        cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if  ( event == EVENT_MBUTTONDOWN )
    {
        cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
    }
    else if ( event == EVENT_MOUSEMOVE )
    {
        cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;
    }*/
    if  ( event == EVENT_LBUTTONDOWN ){
        string texto="x:"+ to_string(x)+ " Y:"+ to_string(y);
        circle(img,Point(x,y),1,Scalar(2));
        putText(img,texto,Point(x,y),FONT_HERSHEY_PLAIN,1.0,Scalar(255,0,0));
        //destroyWindow("Trackbar app");
    }
    imshow("Trackbar app",img);
}


int main(){
    img = imread("F:\\universidade-eletronica\\4ano\\42VISAO\\image.png");
    namedWindow("Trackbar app");
    //set the callback function for any mouse event
    setMouseCallback("Trackbar app", CallBackFunc, NULL);

    //line(img,first,last,Scalar(255,0,0));

    imshow("Trackbar app",img);

    waitKey(0);

    return 0;
}

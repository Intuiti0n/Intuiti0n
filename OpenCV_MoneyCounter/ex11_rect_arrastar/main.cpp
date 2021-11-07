#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat img(500,500,CV_8UC1,Scalar(0,0,0));


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    static Point first;
    static Point last;

    if  ( event == EVENT_LBUTTONDOWN ){
        first=Point(x,y);
    }

    if (event == EVENT_LBUTTONUP){
      last=Point(x,y);
      rectangle(img,last,first,Scalar(255,0,0),3);
    }
    imshow("Trackbar app",img);
}


int main(){
    //img = imread("F:\\universidade-eletronica\\4ano\\42VISAO\\image.png");
    namedWindow("Trackbar app",WINDOW_AUTOSIZE);
    //set the callback function for any mouse event
    setMouseCallback("Trackbar app", CallBackFunc, NULL);

    //line(img,first,last,Scalar(255,0,0));

    imshow("Trackbar app",img);

    waitKey(0);

    return 0;
}

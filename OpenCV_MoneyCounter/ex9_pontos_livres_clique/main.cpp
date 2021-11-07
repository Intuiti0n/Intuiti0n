#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat img(480,640,CV_32FC3,Scalar(255,255,255));


void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN ){
        Vec3b color = img.at<Vec3b>(Point(x,y));
        color[0]=color[1]=color[2]=0;// 0->B, 1->G, 2->R
        img.at<Vec3b>(Point(x,y)) = color;
    }
    imshow("Trackbar app",img);
}


int main(){
    //img = imread("F:\\universidade-eletronica\\4ano\\42VISAO\\image.png");
    namedWindow("Trackbar app",WINDOW_NORMAL);
    //set the callback function for any mouse event
    setMouseCallback("Trackbar app", CallBackFunc, NULL);

    //line(img,first,last,Scalar(255,0,0));

    imshow("Trackbar app",img);

    waitKey(0);

    return 0;
}

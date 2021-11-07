#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(){

Mat img,gray_image;
    VideoCapture cam(0);//capturar da camara do pc
    int i=0;
    namedWindow(("camera"));
    while(1)    {
        cam >> img;
        /*i++;
        if(i % 2 == 0)
        {
            cvtColor(img,gray_image,CV_BGR2GRAY);
            imshow("camera",gray_image);
            waitKey(100);
        }
        else
        {
            imshow("camera",img);
            waitKey(100);
        }*/
        imshow("camera",img);
        waitKey(50);
        if(waitKey(1) == 27)//para quando carregar no esc
            break;
    }
       cam.release();
       return 0;
}

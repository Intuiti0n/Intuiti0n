#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

const int sliderMax=100;
int slider;
Mat img;
//função callback da trackbar, é chamada quando se chama a
void onTrackBar(int pos, void *){
    Mat imgConvert;
    if(pos>0){
        Point ponto(20,50);
        int blue=255,green=0,red=0;
        Scalar cor(blue,green,red);
        cvtColor(img,imgConvert, CV_RGB2GRAY);
        putText(imgConvert,to_string(pos),ponto,FONT_HERSHEY_SIMPLEX,2.0,cor);
    }
    else
        imgConvert= img;

    imshow("Trackbar app",imgConvert);
}

int main(){
    img = imread("F:\\universidade-eletronica\\4ano\\42VISAO\\teste.jpg");
    namedWindow("Trackbar app");
    imshow("Trackbar app",img);

    slider=0;

    createTrackbar("RGB2GRAY","Trackbar app", &slider,sliderMax,onTrackBar);
    waitKey(0);

    return 0;
}

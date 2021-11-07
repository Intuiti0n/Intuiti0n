#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function

using namespace cv;
using namespace std;

const int sliderMax=255;
int slider1,slider2,slider3;

//Mat img1 =imread("F:/universidade-eletronica/4ano/42VISAO/small1.jpg",-1);
//Mat img2= imread("F:/universidade-eletronica/4ano/42VISAO/small2.jpg",-1);
Mat final = imread("F:/universidade-eletronica/4ano/42VISAO/small2.jpg",-1);


volatile double a=0.0;
volatile double b=0.0;
volatile double c=0.0;

//função callback da trackbar, é chamada quando se chama a
void onTrackBar(int pos, void *){
   a=pos/100.0;
   cout<<"pos:"<<pos<<endl;
   cout<<"a"<<a<<endl;
}


//função callback da trackbar, é chamada quando se chama a
void onTrackBar1(int pos, void *){
   b=slider2/100.0;
}

void onTrackBar2(int pos, void *){
   c=slider3/100.0;
}

int main(){
    slider1=0;
    slider2=0;
    slider3=0;

    namedWindow("Window",WINDOW_AUTOSIZE);

    createTrackbar("A","Window", &slider1,sliderMax,onTrackBar);
    createTrackbar("B","Window", &slider2,sliderMax,onTrackBar1);
    createTrackbar("C","Window", &slider3,sliderMax,onTrackBar2);

    while(1){
        //moveWindow("Window" , 0, 0);// Coluna, Linha
        Mat test = final & Scalar(slider1,slider2,slider3);
        imshow("Window",test);

        //destroyWindow("Window"); // Destroi janela
        //imwrite("F:/universidade-eletronica/4ano/42VISAO/exemplo.png", final);
        // grava imagem em ficheiro

        cout<<a<<endl<<b<<endl;
        waitKey(10);
    }


    waitKey(0);
    return 0;
}

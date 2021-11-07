#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>
#include <conio.h>

//using namespace viz;
using namespace cv;
using namespace std;


static void callbackButton( int event, void* ){

}

int main(){
    string imgloc="F:\\universidade-eletronica\\4ano\\42VISAO\\image.png";
    Mat img;
    Point ponto(20,50);
    int blue=255,green=0,red=0;
    Scalar cor(blue,green,red);

    img= imread(imgloc);
    if(img.empty()){
        cout<<"Empty image"<<endl;
        return -1;
    }

    //putText(img,"Texto que queremos",ponto,FONT_HERSHEY_SIMPLEX,2.0,cor);
    namedWindow ("Nome da janela",CV_WINDOW_AUTOSIZE|CV_GUI_EXPANDED);

    imshow("Nome da janela",img);
    /*
    //setMouseCallback();
    int tecla=0;
    while(tecla!=97){
    tecla=waitKey(0);
    }
    cout<<tecla<<endl;
    imshow("Nome da janela",img);
    waitKey(0);
    destroyWindow( "Nome da janela" );
    namedWindow("Window",CV_WINDOW_AUTOSIZE|CV_GUI_EXPANDED);
    imshow("Window",img);
    //createButton(NULL,callbackButton);//create a push button "button 0", that will call callbackButton.
    createButton("button2",callbackButton,NULL,CV_CHECKBOX,0);
    destroyWindow( "Window" );
    */

    while(1){
        Mat aux=img.clone();
        char c=waitKey(10);

        if(c=='a'){
            cvtColor(aux,aux,CV_BGR2GRAY);
            imshow("Nome da janela",aux);
        }
        else if(c=='s'){
            cvtColor(aux,aux,CV_BGR2HSV);
            imshow("Nome da janela",aux);
        }
        else if(c=='d'){
            cvtColor(aux,aux,CV_BGR2HLS);
            imshow("Nome da janela",aux);
        }

    }
    return 0;
}

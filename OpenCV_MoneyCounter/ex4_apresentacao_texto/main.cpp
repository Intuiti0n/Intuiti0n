#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

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

putText(img,"Texto que queremos",ponto,FONT_HERSHEY_SIMPLEX,2.0,cor);
namedWindow ("Nome da janela");
imshow("Nome da janela",img);

waitKey(0);

return 0;
}

#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H

#include <opencv2/opencv.hpp> //Include file for every supported OpenCV function
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

using namespace cv;
using namespace std;

#define SCREEN_HEIGHT 1366
#define SCREEN_WIDTH 768

#define CAMERA_HEIGHT   480
#define CAMERA_WIDTH    640

#define SLIDER_MAX 255
#define MAX_KERNEL_SIZE  21

/*
PROPRIEDADES DA CAMARA, USAR VideoCapture cam.get();
CV_CAP_PROP_POS_MSEC Current position of the video file in milliseconds or video capture timestamp.
CV_CAP_PROP_POS_FRAMES 0-based index of the frame to be decoded/captured next.
CV_CAP_PROP_POS_AVI_RATIO Relative position of the video file: 0 - start of the film, 1 - end of the film.
CV_CAP_PROP_FRAME_WIDTH Width of the frames in the video stream.
CV_CAP_PROP_FRAME_HEIGHT Height of the frames in the video stream.
CV_CAP_PROP_FPS Frame rate.
CV_CAP_PROP_FOURCC 4-character code of codec.
CV_CAP_PROP_FRAME_COUNT Number of frames in the video file.
CV_CAP_PROP_FORMAT Format of the Mat objects returned by retrieve() .
CV_CAP_PROP_MODE Backend-specific value indicating the current capture mode.
CV_CAP_PROP_BRIGHTNESS Brightness of the image (only for cameras).
CV_CAP_PROP_CONTRAST Contrast of the image (only for cameras).
CV_CAP_PROP_SATURATION Saturation of the image (only for cameras).
CV_CAP_PROP_HUE Hue of the image (only for cameras).
CV_CAP_PROP_GAIN Gain of the image (only for cameras).
CV_CAP_PROP_EXPOSURE Exposure (only for cameras).
CV_CAP_PROP_CONVERT_RGB Boolean flags indicating whether images should be converted to RGB.
CV_CAP_PROP_WHITE_BALANCE_U The U value of the whitebalance setting (note: only supported by DC1394 v 2.x backend currently)
CV_CAP_PROP_WHITE_BALANCE_V The V value of the whitebalance setting (note: only supported by DC1394 v 2.x backend currently)
CV_CAP_PROP_RECTIFICATION Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)
CV_CAP_PROP_ISO_SPEED The ISO speed of the camera (note: only supported by DC1394 v 2.x backend currently)
CV_CAP_PROP_BUFFERSIZE Amount of frames stored in internal buffer memory (note: only supported by DC1394 v 2.x backend currently)
*/
bool print_cam_settings(VideoCapture c){
    cout<<"Propriedades da camara"<<endl;
    cout<<"WIDTH:"<<c.get(CV_CAP_PROP_FRAME_WIDTH)<<endl;
    cout<<"HEIGHT:"<<c.get(CV_CAP_PROP_FRAME_HEIGHT)<<endl;
    cout<<"FPS:"<<c.get(CV_CAP_PROP_FPS)<<endl;
    cout<<"CODEC:"<<c.get(CV_CAP_PROP_FOURCC)<<endl;
    cout<<"MODE:"<<c.get(CV_CAP_PROP_MODE)<<endl;
    cout<<"BRIGHTNESS:"<<c.get(CV_CAP_PROP_BRIGHTNESS)<<endl;
    cout<<"CONTRAST:"<<c.get(CV_CAP_PROP_CONTRAST)<<endl;
    cout<<"SATURATION:"<<c.get(CV_CAP_PROP_SATURATION)<<endl;
    cout<<"HUE:"<<c.get(CV_CAP_PROP_HUE)<<endl;
    cout<<"GAIN:"<<c.get(CV_CAP_PROP_GAIN)<<endl;
    cout<<"EXPOSURE:"<<c.get(CV_CAP_PROP_EXPOSURE)<<endl;
    cout<<"RGB:"<<c.get(CV_CAP_PROP_CONVERT_RGB)<<endl;

    cout<<"---END_SETTINGS---"<<endl<<endl;
    return true;
}


/*
Caracteristicas de uma imagem:
HEIGHT
WIDTH
MP
CHANNELS

*/
void print_mat_settings(Mat x){
    if(x.empty()==true)
        cout<<"error loading img"<<endl;
    cout<<"Propriedades da imagem"<<endl;
    cout<<"AREA:"<< x.size().area()<<endl;
    cout<<"WIDTH:"<<x.size().width<<endl;
    cout<<"HEIGHT:"<<x.size().height<<endl;
    cout<<"CHANNELS:"<<x.channels()<<endl;
    cout<<"DEPTH:"<<x.depth()<<endl;
    cout<<"---END IMG PROPERTIES---"<<endl<<endl;
}


/*
Original_resize -> 1/4 imagem inicial
PyrMeanShifter -> imagem original com um "blur" de forma a diminuir ruido
Threshold -> preto e branco
Subtract -> ver moedas extraidas da original
*/


/*
void setup(void){
    bk= imread(path_back, 0);
    if(bk.data==NULL){cout << "Error loading image bk"<< path_back << endl;}

    img= imread(path_coins, 0);
    if(img.data==NULL){cout << "Error loading image bk"<< path_coins << endl;}

    std::cout << "Size: " << bk.size().height << ", " << bk.size().width <<endl;//verificar tamanho da imagem height x width
    //fazer o resize pra 1/4 da original
    resize(bk,bk,Size(bk.size().width/6,bk.size().height/6),0,0,INTER_AREA);
    resize(img,img,Size(img.size().width/6,img.size().height/6),0,0,INTER_CUBIC);
   namedWindow("Background");
   namedWindow("Original");
   imshow("Background",bk);
   imshow("Original",img);
}

    /*
    Point2f not_a_rect_shape[4];
    not_a_rect_shape[0]=(Point(61, 305));
    not_a_rect_shape[1]=(Point(311, 231));
    not_a_rect_shape[2]=(Point(126, 464));
    not_a_rect_shape[3] =(Point(396, 360));

    Point2f dst_vertices[4];
    dst_vertices[0] = Point(0, 0);
    dst_vertices[1] = Point(479, 0); // Bug was: had mistakenly switched these 2 parameters
    dst_vertices[2] = Point(0, 479);
    dst_vertices[3] = Point(639, 479);

     Mat warpAffineMatrix = getAffineTransform(not_a_rect_shape, dst_vertices);

*/

/*
//fazer o setup inicial da janela
void setup(void){
    std::cout << "Size: " << origin.size().height << ", " << origin.size().width <<endl;//verificar tamanho da imagem height x width
    //fazer o resize pra 1/4 da original
    //resize(origin,aux,Size(origin.size().width/4,origin.size().height/4),0,0,INTER_CUBIC);
    resize(origin,origin_resize,Size(306,408),0,0,INTER_CUBIC);//atençao: height e width estao trocadas, se estiverem fica uma elipse
    resize(grey_img,grey_img_resize,Size(306,408),0,0,INTER_CUBIC);//atençao: height e width estao trocadas, se estiverem fica uma elipse

    namedWindow("Original_resize",WINDOW_AUTOSIZE|CV_GUI_EXPANDED);//verificar com OPENGL como e que fica, fazer newbuild do opencv
    namedWindow("PyrMeanShifter",WINDOW_AUTOSIZE|CV_GUI_NORMAL);
    namedWindow("Threshold");
    namedWindow("Subtract");
//    namedWindow("Test");


    moveWindow("Original_resize",0,0);
    moveWindow("PyrMeanShifter",320,0);
    moveWindow("Threshold",640,0);
    moveWindow("Subtract",960,0);
//    moveWindow("Test",0,0);

//    createTrackbar("dp","Test", &slider1,16,onTrackBar);
//    createTrackbar("param1","Test", &slider2,300,onTrackBar1);
//    createTrackbar("param2","Test", &slider3,300,onTrackBar2);
//    createTrackbar("min_cir","Test", &slider4,100,onTrackBar3);
//    createTrackbar("max_cir","Test", &slider5,300,onTrackBar4);
}
*/
/*
    namedWindow("Janela",WINDOW_AUTOSIZE|CV_GUI_NORMAL);//verificar com OPENGL como e que fica, fazer newbuild do opencv
    AUTOSIZE NAO PERMITE FAZER RESIZE
    CV_GUI_NORMAL APARECE SEM AQUELAS OPÇOES NORMAIS COMO GUARDAR, ZOOM, ETC, FICA SEM BARRA DE MENU
    moveWindow("Janela" , 0,0);//definir em que zona do nosso ecra deve ser criada a janela

    createTrackbar("grey_min","win2", &slider1,SLIDER_MAX,onTrackBar);

    //centrar 1 unica janela:
    //moveWindow("Janela" , SCREEN_HEIGHT/2-(origin.size().height/2),SCREEN_WIDTH/2-  (origin.size().width/2));// Coluna, Linha, centrar imagem no ecra
}*/


/*função criada por mim
 * out  - matriz erodida
 * in   - matriz original
 *      - tipo de erosao ( MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE)
 *      - tamanho de erosao -> 0-21
 */

Mat erosao(Mat src,int erosion_elem=0,int erosion_size=0){
    int erosion_type=0;
    if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
    else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
    else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat dest;
    Mat element = getStructuringElement( erosion_type,Size( 2*erosion_size + 1, 2*erosion_size+1 ),Point( erosion_size, erosion_size ) );
    erode( src, dest, element );

    return dest;
}

/*função criada por mim
 * out  - matriz dilatada
 * in   - matriz original
 *      - tipo de dilatacao ( MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE)
 *      - tamanho de dilatacao -> 0-21
 */
Mat dilatacao(Mat src,int dilation_elem=0,int dilation_size=0){
    int dilation_type = 0;
    if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
    else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
    else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

    Mat dest;
    Mat element = getStructuringElement( dilation_type,Size( 2*dilation_size + 1, 2*dilation_size+1 ),Point( dilation_size, dilation_size ) );

    /// Apply the dilation operation
    dilate( src, dest, element );

    return dest;
}

/*
    //cv::threshold(cinzentos, filtrado, 127, 255, cv::THRESH_BINARY);
    // TYPE = BINARY, BINARY_INV, TRUNC, TOZERO, TOZERO_INV

    //AVISO: ADAPTATIVE THRESHOLD SO FUNCIONA NUMA IMAGEM EM ESCALA DE CINZENTOS
    thresholdType – Thresholding type that must be either THRESH_BINARY or THRESH_BINARY_INV .
    adaptiveMethod – Adaptive thresholding algorithm to use, ADAPTIVE_THRESH_MEAN_C or ADAPTIVE_THRESH_GAUSSIAN_C

    void adaptiveThreshold(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
    //adaptiveThreshold(grey_img, filtrado,188, cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY, 5, 0);

    inRange(cinzentos, lowerv, upperv, filtrado); //filtrar a imagem por pontos dentro do range
*/

#endif // MY_FUNCTIONS_H

/*
#include "my_functions.h"

static int slider1=0,slider2=0,slider3=0,slider4=0,slider5=0,slider6=0;

Mat origin = imread("F:/universidade-eletronica/4ano/42VISAO/coins2.jpg",-1);
Mat grey_img= imread("F:/universidade-eletronica/4ano/42VISAO/coins2.jpg",CV_8UC1);

//função callback da trackbar, é chamada quando se chama a
void onTrackBar(int pos, void *){
    cout<<"pos1:"<<pos<<endl;
}

//função callback da trackbar, é chamada quando se chama a
void onTrackBar1(int pos, void *){
    cout<<"pos2:"<<pos<<endl;
}

//função callback da trackbar, é chamada quando se chama a
void onTrackBar2(int pos, void *){
    cout<<"er_mode:"<<pos<<endl;
}

//função callback da trackbar, é chamada quando se chama a
void onTrackBar3(int pos, void *){
    cout<<"er_size:"<<pos<<endl;
}

//função callback da trackbar, é chamada quando se chama a
void onTrackBar4(int pos, void *){
    cout<<"er_size:"<<pos<<endl;
}

//função callback da trackbar, é chamada quando se chama a
void onTrackBar5(int pos, void *){
    cout<<"er_size:"<<pos<<endl;
}

//fazer o setup inicial da janela
void setup(void){
    std::cout << "Size: " << origin.size().height << ", " << origin.size().width <<endl;//verificar tamanho da imagem height x width


    namedWindow("Janela",WINDOW_AUTOSIZE|CV_GUI_NORMAL);//verificar com OPENGL como e que fica, fazer newbuild do opencv
    namedWindow("grey",WINDOW_AUTOSIZE|CV_GUI_NORMAL);
    namedWindow("threshold",WINDOW_AUTOSIZE|CV_GUI_NORMAL);
    namedWindow("dilate",WINDOW_AUTOSIZE|CV_GUI_NORMAL);
    namedWindow("erode",WINDOW_AUTOSIZE|CV_GUI_NORMAL);

    //moveWindow("Janela" , SCREEN_HEIGHT/2-(origin.size().height/2),SCREEN_WIDTH/2-  (origin.size().width/2));// Coluna, Linha, centrar imagem no ecra
    moveWindow("Janela" , 0,0);
    moveWindow("grey" , 0,0);
    moveWindow("threshold" , 900,200);
    moveWindow("dilate" , 400,200);
    moveWindow("erode" , 0,0);

    //createTrackbar("grey_min","threshold", &slider1,SLIDER_MAX,onTrackBar);
    //createTrackbar("grey_max","threshold", &slider2,SLIDER_MAX,onTrackBar1);
    //createTrackbar("dil_tipo","dilate", &slider3,2,onTrackBar2);
    //createTrackbar("dil_size","dilate", &slider4,MAX_KERNEL_SIZE,onTrackBar3);
    //createTrackbar("er_tipo","erode", &slider5,2,onTrackBar4);
    //createTrackbar("er_size","erode", &slider6,MAX_KERNEL_SIZE,onTrackBar5);
}



int main (int argc, char **argv ){
    Mat cinzentos, filtrado, RGB;
    setup();

    cv::cvtColor(origin, RGB, CV_BGR2RGB); // inverte o formato de RGB para BGR
    cv::cvtColor(origin, cinzentos, cv::COLOR_BGR2GRAY); // converte em cinzentos

    imshow("Janela",origin);
    imshow("grey",grey_img);

    while(1){
        imshow("grey",grey_img);
        imshow("threshold",filtrado);

        waitKey(10);
    }

}



int main (int argc, char **argv ){
    Mat cinzentos, filtrado, RGB;
    setup();

    cv::cvtColor(origin, RGB, CV_BGR2RGB); // inverte o formato de RGB para BGR
    cv::cvtColor(origin, cinzentos, cv::COLOR_BGR2GRAY); // converte em cinzentos

    imshow("Janela",origin);
    imshow("grey",grey_img);

    while(1){
        threshold(grey_img, filtrado, slider1, slider2, cv::THRESH_BINARY);
        imshow("grey",grey_img);
        imshow("threshold",filtrado);

        int c=waitKey(10);

        Mat img=filtrado;
        vector<Vec3f> circles;
            HoughCircles(filtrado, circles, CV_HOUGH_GRADIENT,
                         2, grey_img.rows/4, 200, 100);
            for( size_t i = 0; i < circles.size(); i++ )
                {
                     Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                     int radius = cvRound(circles[i][2]);
                     // draw the circle center
                     circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
                     // draw the circle outline
                     circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
                }
                imshow( "erode", img );
                waitKey(10);
    }
}

*/




/*
int main (int argc, char **argv ){
    Mat cinzentos, filtrado, RGB;
    setup();

    cv::cvtColor(origin, RGB, CV_BGR2RGB); // inverte o formato de RGB para BGR
    cv::cvtColor(origin, cinzentos, cv::COLOR_BGR2GRAY); // converte em cinzentos
    //precisa de #include <opencv2/imgproc/imgproc.hpp>
    //cv::threshold(cinzentos, filtrado, 127, 255, cv::THRESH_BINARY);
    // TYPE = BINARY, BINARY_INV, TRUNC, TOZERO, TOZERO_INV
    filtrado=cinzentos;
    imshow("Janela",origin);

    while(1){
        threshold(cinzentos, filtrado, slider1, slider2, cv::THRESH_BINARY);
        //AVISO: ADAPTATIVE THRESHOLD SO FUNCIONA NUMA IMAGEM EM ESCALA DE CINZENTOS
        //adaptiveThreshold(grey_img, filtrado,188, cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY, 5, 0);
        //adaptiveThreshold(grey_img, filtrado, slider1, ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY, 21, slider2);
        //inRange(cinzentos, slider1, slider2, filtrado); //filtrar a imagem por pontos dentro do range

        //erosao/dilatacao
        //Mat er=erosao(filtrado,slider3,slider4);
        //Mat aux=dilatacao(filtrado,slider3,slider4);
        //Mat final=erosao(aux,slider5,slider6);

        imshow("grey",cinzentos);
        imshow("threshold",filtrado);
        //imshow("dilate",aux);
        //imshow("erode",final);
        waitKey(10);
    }
    return 0;
}
*/

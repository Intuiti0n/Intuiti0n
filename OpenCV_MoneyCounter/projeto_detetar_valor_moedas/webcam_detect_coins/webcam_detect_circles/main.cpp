/*DANIEL GOMES A74729
 * ALGORITMO
tirar foto ao background, sem moedas -> bk.png
converter pra cinzento
GaussianBlur 7x7 Antes ou depois de subtrair?
Subtrair bk-img
Saturar subtraida
Threshold binario pra ficar preto e branco
Closing pra obter circulos com menos ruido
Dilatacao para obter circulos maiores que a propria moeda
And com img original para obter areas de interesse

Detetar circulos e tamanhos e qual e de referencia
Detetar primeiro a de referencia, guardar referencia

Detetar restantes, utilizar a referencia como comparacao,
Calcular valor total das moedas existentes a frente da camara
*/

//alterar diretorio para o que tiver o ficheiro my_functions
#include "../../my_functions.h"

using namespace cv;
using namespace std;

//COLOCAR DIRETORIO DA IMAGEM DE FUNDO TIRADA INICIALMENTE PARA CALIBRAÇAO
string path_bk = "C:\\Users\\Daniel\\Downloads\\opencv_detect_coins\\bk5.png";
//string path_coins = "F:\\universidade-eletronica\\4ano\\42VISAO\\4.jpg";//utilizada para testes iniciais com imagens estaticas

/*
IMG: IMAGEM CAPTURADA PELA CAMARA
GRAY: IMG ORIGINAL A PRETO E BRANCO, MAIS FACIL DE APLICAR CERTOS FILTROS/OPERAÇOES
SUB: subtraçao entre o background e a imagem da camara
BK: background image tirada antes das restantes
*/
Mat img,gray,sub,bk;//imagem original com as coins
Mat blured;
VideoCapture cam(0);//capturar da camara do pc

//1 cent,2,5,10,20,50,1€,2€
//tamanhos das moedas arrendondados as unidades, para usar na regra de 3 simples pra calcular valor total das moedas
short int coins_vec[]={16,19,21,20,22,24,23,25};

//SLIDERS DAS TRACKBARS
/*
 * 1-DP
 * 2-MINDIST
 * 3-MINRADIUS
 * 4-MAXRADIUS

*/
int slider1=27,slider2=10,slider3=2,slider4=35,slider5=128;

//função callback da trackbar, é chamada quando se chama a
void onTrackBar(int pos, void *){
    //draw_circles();
}
//função callback da trackbar, é chamada quando se chama a
void onTrackBar1(int pos, void *){
    //draw_circles();
}
//função callback da trackbar, é chamada quando se chama a
void onTrackBar2(int pos, void *){
    //draw_circles();
}

//função callback da trackbar, é chamada quando se chama a
void onTrackBar3(int pos, void *){
    //draw_circles();
}
//função callback da trackbar, é chamada quando se chama a
void onTrackBar4(int pos, void *){
    //draw_circles();
}
//função callback da trackbar, é chamada quando se chama a
void onTrackBar5(int pos, void *){
    Mat aux=sub.clone();
    threshold(aux,aux,slider5,255,THRESH_BINARY);
    imshow("Dif",aux);
}

void test_opening(int tipo,int size, Mat src){
    Mat opening;
    Mat element = getStructuringElement( tipo, Size( 2*size + 1, 2*size+1 ), Point( size, size ) );
    /// Apply the specified morphology operation
      morphologyEx( src, opening, 3, element );
      //imshow( "opening", opening );
}


int main() {
    static int med=0,count=0;//media dos valores de raio da moeda de 50 centimos, para calibraçao. count = numero de vezes que detetamos a moeda ate calibrar
    bool calibration=false;
    cam >> img;

    cvtColor(img,gray,CV_BGR2GRAY);//converter imagem da camara para cinzento
    bk=imread(path_bk);//imagem de background para mat bk

    print_cam_settings(cam);//imprimir as settings da camara
    print_mat_settings(bk);

    namedWindow(("camera"));//live feed da camara
    namedWindow("Dif");//diferença entre background e camara
    namedWindow("Blured");//imagem desfocada

    //moveWindow("Dif",300,300);
    //moveWindow("Blured",500,0);

    subtract(bk,img,sub);
    cvtColor(sub,sub,CV_BGR2GRAY);
    //threshold(sub,sub,200,255,THRESH_BINARY);
    //imshow("camera",img);
    //imshow("Dif",sub);
    createTrackbar("thres","Dif", &slider5,255,onTrackBar5);
    //waitKey(0);//para debug
    //INICIO DO ALGORITMO:
    cout<<"start algorithm"<<endl;

    GaussianBlur(gray,blured,Size(7,7),0);//esta a resultar bem
    /*pyrMeanShiftFiltering(img,blured,20,20);//resulta pior do que o gaussianblur
    cvtColor(blured,blured,CV_BGR2GRAY);
    */
    //imshow("Blured",blured);
    /*
    createTrackbar("dp","Blured", &slider1,100,onTrackBar);
    createTrackbar("min_dist","Blured", &slider2,200,onTrackBar1);
    createTrackbar("param1","Blured", &slider3,200,onTrackBar2);
    createTrackbar("param2","Blured", &slider4,200,onTrackBar3);
    */

    while(calibration==false){


        Mat test,saturated;
        cam >> img;
        cvtColor(img,gray,CV_BGR2GRAY);//converter para cinzento
        //GaussianBlur(gray,blured,Size(7,7),0);//esta a resultar bem, verificar diferenças entre blur antes e depois de subtrair
        moveWindow("Blured",650,0);
        imshow("Blured",blured);
        subtract(bk,img,sub);//subtrair esta ao fundo tirado com a camara sem moedas
        sub.convertTo(saturated, CV_8UC1, 1.0, 20.0);
        cvtColor(saturated,saturated,CV_BGR2GRAY);
        threshold(saturated,test,50,255,THRESH_BINARY);

        test_opening(0,15,test);//isto e um closing, ta com o nome errado
        test=dilatacao(test,2,15);


        //imshow("Dif",test);
        Mat test_and;
        bitwise_and(test,gray,test_and);
        namedWindow("And");
        imshow("And",test_and);
        imshow("camera",img);

        Mat aux=img;
        //vetor onde vao ser inseridos os circulos detetados
        vector<Vec3f> circles;
        //Funçao de deteçao de circulos
        /*
         * apos varios testes e a que resulta melhor a uma distancia de 30-50cm
         * 2.7 resolucao,
         * 20 minDist entre circulos
         * 100 param 1
         * 100 param2
         * 20 minRadius
         * 35 maxRadius
*/
        HoughCircles(test_and.clone(), circles, CV_HOUGH_GRADIENT,2.7, 20, 100, 100,20,35);

        for( size_t i = 0; i < circles.size(); i++ )
            {
                 Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                 int radius = cvRound(circles[i][2]);
                 // draw the circle center
                 circle( aux, center, 3, Scalar(0,255,0), -1, 8, 0 );
                 // draw the circle outline
                 circle( aux, center, radius, Scalar(0,0,255), 3, 8, 0 );
                 cout<<"Raio:"<<radius<<endl;
                 count++;
                 med+=radius;
            }
        if(count==20){
            med=med/20;
            calibration=true;
            cout<<"Media diametro="<<med*2<<endl;
        }
                moveWindow("circles",0,0);

                imshow( "circles", aux );
                //cout<<"numero de circulos:"<<circles.size()<<endl;
       waitKey(100);
    }

    waitKey(0);
    while(1){
        Mat test,saturated;
        cam >> img;
        cvtColor(img,gray,CV_BGR2GRAY);//converter para cinzento
        //GaussianBlur(gray,blured,Size(7,7),0);//esta a resultar bem, verificar diferenças entre blur antes e depois de subtrair
        moveWindow("Blured",650,0);
        imshow("Blured",blured);
        subtract(bk,img,sub);//subtrair esta ao fundo tirado com a camara sem moedas
        sub.convertTo(saturated, CV_8UC1, 1.0, 20.0);
        cvtColor(saturated,saturated,CV_BGR2GRAY);
        threshold(saturated,test,50,255,THRESH_BINARY);

        test_opening(0,15,test);//isto e um closing, ta com o nome errado
        test=dilatacao(test,2,15);


        //imshow("Dif",test);
        Mat test_and;
        bitwise_and(test,gray,test_and);
        namedWindow("And");
        imshow("And",test_and);
        imshow("camera",img);

        Mat aux=img;
        //vetor onde vao ser inseridos os circulos detetados
        vector<Vec3f> circles;
        //Funçao de deteçao de circulos
        /*
         * apos varios testes e a que resulta melhor a uma distancia de 30-50cm
         * 2.7 resolucao,
         * 20 minDist entre circulos
         * 100 param 1
         * 100 param2
         * 20 minRadius
         * 35 maxRadius
*/
        HoughCircles(test_and.clone(), circles, CV_HOUGH_GRADIENT,2.7, 20, 100, 100,20,35);
        /*
        DETETAR CIRCULOS
        COMPARAR RAIOS DOS CIRCULO DETETADO NA CALIBRAÇAO (MOEDA DE 50 CENT PARA CALIBRAR)
        DETETAR RAIOS DOS CIRCULOS QUE VAO APARECENDO, ATRIBUIR UM VALOR ATRAVES DA COMPARACAO
        PROBLEMA: Valores de raio variam demasiado
        como estabilizar valores??
        VER QUAL O NUMERO MAXIMO DE CIRCULOS DETETADOS DURANTE 2 SEGUNDOS, ASSUMIR QUE ESSE VALOR ESTA CORRETO
        CALCULAR VALOR A PARTIR DAI?
*/
        cout<<"numero de circulos detetados:"<<circles.size()<<endl;
        for( size_t i = 0; i < circles.size(); i++ )
            {
                 Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                 int radius = cvRound(circles[i][2]);
                 // draw the circle center
                 circle( aux, center, 3, Scalar(0,255,0), -1, 8, 0 );
                 // draw the circle outline
                 circle( aux, center, radius, Scalar(0,0,255), 3, 8, 0 );
                 cout<<"Raio do "<<(int)i+1<<":"<<radius<<endl;
            }
                moveWindow("circles",0,0);
                imshow( "circles", aux );


       waitKey(10);
    }
    waitKey(0);

    /*
    //Para usar a webcam, tirar 1 pic inicial ao fundo sem imagens
    ////VideoCapture cam(0);
    if(!cam.isOpened()){  // check if we succeeded
        cout<<"erro, camara nao abriu!!<<endl;
        return -1;
        }
    cam.read(bk);
    std::cout << "Size: " << bk.size().height << ", " << bk.size().width <<endl;//verificar tamanho da imagem height x width
    //fazer o resize caso necessário
    */
}

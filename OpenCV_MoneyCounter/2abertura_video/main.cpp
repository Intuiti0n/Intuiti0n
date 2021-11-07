#include "opencv2/opencv.hpp"

using namespace cv;

int main() {

    Mat frame;
    //F:\universidade-eletronica\4ano\42VISAO\exercicios_praticos\ex2\2abertura_video
    //string path = "F:\\universidade-eletronica\\4ano\\42VISAO\\exercicios_praticos\\ex2\\2abertura_video\\kaleo.mp4";
    string path="F:/universidade-eletronica/4ano/42VISAO//768x576.avi";
    VideoCapture capture(path);

    namedWindow("my_window");
    while(1){
        capture >> frame;
        //cout<<
        imshow("my_window", frame);

        waitKey(10);
    }
        waitKey(0);
}

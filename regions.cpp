#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){

    int p1[2], p2[2];

    cout << "Informe as coordenadas dos pontos P1 e P2" << endl;

    cout << "P1X: " << endl;
    cin >> p1[0];

    cout << "P1Y: " << endl;
    cin >> p1[1];

    cout << "P2X: " << endl;
    cin >> p2[0];

    cout << "P2Y: " << endl;
    cin >> p2[1];

    cv::Mat image; // Estrutura para representação da imagem
    cv::Vec3b val; // Estrutura para definição das cores

    image= cv::imread("biel.png", cv::IMREAD_GRAYSCALE);         //Leitura da imagem
    if(!image.data)                              
        std::cout << "não abriu bolhas.png" << std::endl;

    cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

    for(int i=p1[0]; i<p2[0];i++){
        for(int j=p1[1]; j<p2[1]; j++){
            image.at<uchar>(i,j) = image.at<uchar>(i,j) * (-1) ;  //uchar para passar representação decimal
        }
    }

    cv::imwrite("biel-modificado.png", image);
    cv::imshow("janela", image);
    cv::waitKey();
      
    return 0;
}
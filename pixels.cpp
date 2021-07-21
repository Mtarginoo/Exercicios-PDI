#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
    cv::Mat image; // Estrutura para representação da imagem
    //cv::Vec3b val; // Estrutura para definição das cores

    image= cv::imread("bolhas.png", cv::IMREAD_GRAYSCALE);         
    if(!image.data)                              
        std::cout << "não abriu bolhas.png" << std::endl;

    cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

    for(int i=200; i<210;i++){
        for(int j=10; j<200; j++){
            image.at<uchar>(i,j)=255;
        }
    }

    cv::imshow("janela", image);
    cv::waitKey();

    image= cv::imread("bolhas.png", cv::IMREAD_COLOR);

    for(int i=200; i<210; i++){
        for(int j=10; j<200; j++){
            image.at<Vec3b>(i,j)=val;
        }
    }

    cv::imshow("janela", image);
    cv::waitKey();

    return 0;
}
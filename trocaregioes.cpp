#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
    cv::Mat image, image_trocada;                                                                                 // Estrutura para representação da imagem
    cv::Vec3b val;                                                                                                // Estrutura para definição das cores

    image = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
    image_trocada = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);                                                //Leitura da imagem
    if(!image.data)                              
        std::cout << "não abriu lena.jpg" << std::endl;

    cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

    for(int i = 0; i < image.size().height/2; i++){
        for(int j = 0; j < image.size().width/2; j++){
            image_trocada.at<uchar>(i + image.size().height/2,j + image.size().width/2) = image.at<uchar>(i,j);  //uchar para passar representação decimal
        }
    }

    for(int i = image.size().height/2; i < image.size().height; i++){
        for(int j = image.size().width/2; j < image.size().width; j++){
            image_trocada.at<uchar>(i - image.size().height/2, j - image.size().width/2) = image.at<uchar>(i,j);  //uchar para passar representação decimal
        }
    }

    for(int i = image.size().height/2; i < image.size().height; i++){
        for(int  j = 0; j < image.size().width/2; j++){
            image_trocada.at<uchar>(i - image.size().height/2, j + image.size().width/2) = image.at<uchar>(i,j);  //uchar para passar representação decimal
        }
    }

    for(int i = 0; i < image.size().height/2; i++){
        for(int j = image.size().width/2; j < image.size().width; j++){
            image_trocada.at<uchar>(i + image.size().height/2, j - image.size().width/2) = image.at<uchar>(i,j);  //uchar para passar representação decimal
        }
    }

    cv::imshow("janela", image_trocada);                                                                          
    cv::waitKey();
      
    return 0;
}
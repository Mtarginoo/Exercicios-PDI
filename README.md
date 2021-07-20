# Exercicios de Processamento Digital de Imagens em OpenCV
Exercícios de programação com OpenCV realizados na disciplina DCA0445 - Processamento Digital de Imagens, componente optativo do curso de Engenharia de Computação da UFRN, ministrada pelo Prof. Dr Agostinho de Medeiros Brito Jr.

Autores:
- Lourival Alexandre 
- Matheus Targino Barbosa 

## Capítulo 2 - Manipulando pixels em uma imagem
### Criando regiões
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace cv;
        using namespace std;

        int main(int, char**){
        cv::Mat image; // Estrutura para representação da imagem
        cv::Vec3b val; // Estrutura para definição das cores

        image= cv::imread("bolhas.png", cv::IMREAD_GRAYSCALE);         //Leitura da imagem
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

        val[0] = 255; // B
        val[1] = 0; // G
        val[2] = 0; // R

        for(int i=200; i<210; i++){
          for(int j=10; j<200; j++){
            image.at<Vec3b>(i,j)=val;
          }
        }

        cv::imshow("janela", image);
        cv::waitKey();

        return 0;
       }

### Trocando regiões

## Capítulo 3 - Preeenchendo regiões

### O problema de rotulação

### Identificando buracos

## Capítulo 4 - Manipulação de histogramas

### Equalização de histograma

### Detector de movimentos

## Capítulo 5 - Filtragem no domínio espacial I

### Filtro laplaciano do gaussiano

## Capítulo 6 - Filtragem no domínio espacial II

### Tilt-shift em imagem

### Tilt-shift em vídeo


#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){

    Mat image;
    int width, heigth;
    int nfuros;

    //Primeira etapa: remover objetos da borda

    Point p;
    image = imread("bolhas.png", IMREAD_GRAYSCALE);
    
    if(!image.data){
        cout << "imagem nao carregou corretamente\n";
        return(-1);
    }

    width = image.cols;
    heigth = image.rows;
    cout << width << "x" << heigth << endl;

    for(int i=0; i<width-1; i++){
        if(image.at<uchar>(0, i) == 255){
            p.x = i;
            p.y = 0;
            floodFill(image, p, 0);
        }
    }

    for(int i=0; i<width-1; i++){
        if(image.at<uchar>(heigth-1, i) == 255){
            p.x = i;
            p.y = heigth-1;
            floodFill(image,p,0);
        }
    }

    for(int i=0; i<heigth-1; i++){
        if(image.at<uchar>(i, 0) == 255){
            p.x = 0;
            p.y = i;
            floodFill(image,p,0);
        }
    }

    for(int i=0; i<heigth-1; i++){
        if(image.at<uchar>(i, width-1) == 255){
            p.x = width-1;
            p.y = i;
            floodFill(image,p,0);
        }
    }

    imshow("image", image);
    waitKey();

    //Segunda etapa: Deixar o fundo com a cor branca

    p.x = 0;
    p.y = 0;
    floodFill(image, p, 255);

    //Tereceira etapa: Percorrer imagem da esquerda para direta, se encontrar furo
    //incrementa contador e floodfill com 255 no buraco e no objeto.

    nfuros=0;
    for(int i=0; i<heigth; i++){
        for(int j=0; j<width; j++){
            if(image.at<uchar>(i,j) == 0){
                // achou um objeto
                nfuros++;
                p.x=j;
                p.y=i;
  		        // preenche o objeto com o contador
		        cv::floodFill(image,p,nfuros);
            }
        }
    }

    cout << "A figuras possui " << nfuros << " bolhas com furos\n";

    imshow("image", image);
    waitKey();
    return 0;
}
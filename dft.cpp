#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;
using namespace cv;

#define RADIUS 20

void on_trackbar_frequency(int, void*) {}

void on_trackbar_noise_gain(int, void*) {}

void menu(){
    cout << "e : habilita/desabilita interferencia\n"
            "m : habilita/desabilita o filtro mediano\n"
            "g : habilita/desabilita o filtro gaussiano\n"
            "p : realiza uma amostra das imagens\n"
            "s : habilita/desabilita subtração de fundo\n"
            "b : realiza uma amostra do fundo da cena\n"
            "n : processa o negativo\n";
}

// troca os quadrantes da imagem da DFT
void deslocaDFT(Mat& image){
    Mat tmp, A, B, C, D;

    //se a imagem tiver tamanho impar, recorta a região para
    // evitar cópias de tamanho desigual
    image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
    int cx = image.cols / 2;
    int cy = image.rows / 2;

    //reorganiza os quadrantes da transformada
    //A B -> D C
    //C D    B A

    A = image(Rect(0,0,cx,cy));
    B = image(Rect(cx,0,cx,cy));
    C = image(Rect(0,cy,cx,cy));
    D = image(Rect(cx,cy,cx,cy));

    // A <-> D
    A.copyTo(tmp);
    D.copyTo(A);
    tmp.copyTo(D);

    // C <-> B
    C.copyTo(tmp);
    B.copyTo(C);
    tmp.copyTo(B);
}

int main(int, char**) {
    VideoCapture cap;
    Mat imaginaryInput, complexImage, multsp;
    Mat padded, filter, mag;
    Mat image, imagegray, tmp, magI;
    Mat_<float> realInput, zeros, ondes;
    Mat backgroundImage;
    vector<Mat> planos;

    //habilita/desabilita ruido
    bool noise = true;
    // frequencia do ruido
    int freq = 10;
    int freq_max;
    // granho do ruido
    int gain_int = 0;
    int gain_max = 100;
    float gain = 0;

    //habilita filtro da mediana
    bool median = false;
    // habilita o filtro gaussiano
    bool gaussian = false;
    // habilita o negativo da imagem
    bool negative = false;

    //realiza amostragem da imagem
    bool sample = false;

    //caputra backgroun
    bool background = false;

    // subtrai fundo da imagem
    bool subtract = false;

    // valor do ruído
    float mean;

    // guarda tecla capturada
    char key;

    // valores ideiis dos tamanhos da imagem
    // para calculo da DFT
    int dft_M, dft_N;

    // abre a câmera
    cap.open(0);

    // apresenta as opcoes de interacao
    menu();

    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    if(!cap.isOpened()) return -1;

    cap >> image;

    dft_M = getOptimalDFTSize(image.rows);
    dft_N = getOptimalDFTSize(image.cols);

    freq_max = dft_M / 2 - 1;
    namedWindow("original", 1);
    createTrackbar("frequencia", "original", &freq, freq_max,
                    on_trackbar_frequency);
    
    on_trackbar_frequency(freq, 0);

    createTrackbar("amp. ruido", "original", &gain_int, gain_max, on_trackbar_frequency);

    on_trackbar_noise_gain(gain_int, 0);

    // realiza o padding da imagem
    copyMakeBorder(image, padded, 0, dft_M - image.rows, 0, dft_N - image.cols, BORDER_CONSTANT, Scalar::all(0));

    
}
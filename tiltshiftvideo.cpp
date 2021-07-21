#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int matriz_media_tam = 7;

int main(int argvc, char **argv)
{
  VideoCapture video;
  
  video.open(0);
  if (!video.isOpened())
  {
    cout << "Erro ao abrir video" << endl;
    return -1;
  }

  video.set(CAP_PROP_FRAME_WIDTH, 640);
  video.set(CAP_PROP_FRAME_HEIGHT, 480);
  int largura = video.get(CAP_PROP_FRAME_WIDTH);
  int altura = video.get(CAP_PROP_FRAME_HEIGHT);

  float media[matriz_media_tam * matriz_media_tam];
  for (int i = 0; i < matriz_media_tam; i++)
  {
    for (int j = 0; j < matriz_media_tam; j++)
    {
      media[i * matriz_media_tam + j] = 1.0 / (matriz_media_tam * matriz_media_tam);
    }
  }

  Mat masc_media(matriz_media_tam, matriz_media_tam, CV_32F, media);

  Mat ponderada(altura, largura, CV_32FC3);
  Mat ponderada_negativa(altura, largura, CV_32FC3);

  int centro = 6*altura / 10, l1 = -70, l2 = 70, aceleracao = 10;
  float d = 30;

  for (int i = 0; i < altura; i++)
  {
    float fx = 0.0;
    if (d != 0)
    {
      fx = -0.5 * (tanh((i - centro + l1) / d) - tanh((i - centro + l2) / d));
    }

    for (int j = 0; j < largura; j++)
    {
      ponderada.at<Vec3f>(i, j)[0] = fx;
      ponderada.at<Vec3f>(i, j)[1] = fx;
      ponderada.at<Vec3f>(i, j)[2] = fx;
      ponderada_negativa.at<Vec3f>(i, j)[0] = 1.0 - fx;
      ponderada_negativa.at<Vec3f>(i, j)[1] = 1.0 - fx;
      ponderada_negativa.at<Vec3f>(i, j)[2] = 1.0 - fx;
    }
  }

  Mat imagem, imagem_borrada;

  while (true)
  {
    for (int i = 0; i < aceleracao; i++)
    {
      video >> imagem;
    }

    imagem.convertTo(imagem, CV_32FC3);

    vector<Mat> canais;
    split(imagem, canais);

    filter2D(canais[0], canais[0], canais[0].depth(), masc_media, Point(3, 3), 0);
    filter2D(canais[1], canais[1], canais[1].depth(), masc_media, Point(3, 3), 0);
    filter2D(canais[2], canais[2], canais[2].depth(), masc_media, Point(3, 3), 0);

    merge(canais, imagem_borrada);

    Mat resultado, res1, res2;

    multiply(imagem, ponderada, res1);
    multiply(imagem_borrada, ponderada_negativa, res2);

    addWeighted(res1, 1, res2, 1, 0, resultado);

    resultado.convertTo(resultado, CV_8UC3);

    imshow("tiltshift", resultado);

    if (waitKey(50) == 27)
      break;
  }

  return 0;
}
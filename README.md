# Exercicios de Processamento Digital de Imagens em OpenCV
Exercícios de programação com OpenCV realizados na disciplina DCA0445 - Processamento Digital de Imagens, componente optativo do curso de Engenharia de Computação da UFRN, ministrada pelo Prof. Dr Agostinho de Medeiros Brito Jr.

Autores:
- Lourival Alexandre 
- Matheus Targino Barbosa 

Os códigos abaixos foram escritos em linguagem C++, usando a biblioteca OpenCV em ambiente Ubuntu 20.04. Para compilar e executar cada código basta utilizar os comandos "make <nome_do_arquivo>" e "./<nome_do_arquivo>" no mesmo diretório em que se econtra o código e o arquivo Makefile, que pode ser baixado [aqui](/Makefile).  

## Capítulo 2 - Manipulando pixels em uma imagem
### Criando regiões

![biel_png](/biel.png)

```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace cv;
        using namespace std;

        int main(int, char**){
        cv::Mat image; 
        cv::Vec3b val; 

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

        val[0] = 255; 
        val[1] = 0; 
        val[2] = 0; 

        for(int i=200; i<210; i++){
          for(int j=10; j<200; j++){
            image.at<Vec3b>(i,j)=val;
          }
        }

        cv::imshow("janela", image);
        cv::waitKey();

        return 0;
       }
```
### Trocando regiões
```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace cv;
        using namespace std;

        int main(){
        cv::Mat image, image_trocada;                                                                              
        cv::Vec3b val;                                                                                               

        image = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);
        image_trocada = cv::imread("biel.png", cv::IMREAD_GRAYSCALE);                                               
        if(!image.data)                              
                std::cout << "não abriu bolhas.png" << std::endl;

        cv::namedWindow("janela", cv::WINDOW_AUTOSIZE);

        for(int i=0; i<image.size().height;i++){
                for(int j=0; j<image.size().width; j++){
                        if((i >= 0 && i < image.size().height/2) && (j >=0 && j < image.size().width/2)){
                                image_trocada.at<uchar>(i + image.size().height/2,j + image.size().width/2) = image.at<uchar>(i,j);
                        }
                        else if((i >= image.size().height/2 && i < image.size().height) && (j >= image.size().width/2 && j < image.size().width)){
                                image_trocada.at<uchar>(i - image.size().height/2, j - image.size().width/2) = image.at<uchar>(i,j);
                        }
                        else if((i >= image.size().height/2 &&  i < image.size().height) && (j >= 0 && j < image.size().width/2)){
                                image_trocada.at<uchar>(i - image.size().height/2, j + image.size().width/2) = image.at<uchar>(i,j);
                        }
                        else{
                                image_trocada.at<uchar>(i + image.size().height/2, j - image.size().width/2) = image.at<uchar>(i,j);
                        }
                 }
         }
   
        cv::imshow("janela", image_trocada);                                                                          
        cv::waitKey();
      
        return 0
        }
```
## Capítulo 3 - Preeenchendo regiões

### O problema de rotulação
O problema da rotulação acontece quando existem mais de 255 objetos na imagem devido ao tipo de dado utilizado para representar os pixels da imagem. É possível melhorar o processo de rotulação apenas mudando o tipo da variável que representa cada pixel, usando um tipo que suporte um valor maior vai aumentar a possibilidade de tonalidades a serem utilizadas no labelling

### Identificando buracos
```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace cv;

        int main(int argc, char **argv)
        {
            cv::Mat image, realce;
            int width, height;
            int nobjects, colorobjects, bolhascomburacos;

            cv::Point p;
            image = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

            if (!image.data)
            {
                std::cout << "imagem nao carregou corretamente\n";
                return (-1);
            }

            width = image.cols;
            height = image.rows;
            std::cout << width << "x" << height << std::endl;

            p.x = 0;
            p.y = 0;

            cv::imshow("image", image);

            // eliminando objetos da borda
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    // Se tiver em uma das bordas
                    if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                    {
                        if (image.at<uchar>(i, j) == 255)
                        {
                            // achou um objeto
                            p.x = j;
                            p.y = i;
                            // preenche o objeto com o contador
                            cv::floodFill(image, p, 0);
                        }
                    }
                }
            }

            cv::imshow("image", image);
            cv::imwrite("exercicio3-2a.png", image);
            waitKey();


            nobjects = 0;
            colorobjects = 0;

            // busca objetos presentes
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (image.at<uchar>(i, j) == 255)
                    {
                        // achou um objeto
                        nobjects++;
                        colorobjects++;
                        p.x = j;
                        p.y = i;
                        if (colorobjects == 255)
                        {
                            colorobjects = 1;
                        }
                        // preenche o objeto com o contador
                        cv::floodFill(image, p, colorobjects);
                    }
                }
            }

            cv::equalizeHist(image, realce);
            cv::imshow("realce labelling", realce);
            cv::imwrite("exercicio3-2b.png", image);
            waitKey();

            // floodfill background
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (image.at<uchar>(i, j) == 0)
                    {
                        p.x = j;
                        p.y = i;
                        cv::floodFill(image, p, 255);
                        i = height;
                        break;
                    }
                }
            }

            cv::equalizeHist(image, realce);
            cv::imshow("realce floodfill background", realce);
            cv::imwrite("exercicio3-2c.png", image);
            waitKey();

            bolhascomburacos = 0;
            // remove objetos com buracos
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (image.at<uchar>(i, j) == 0)
                    {
                        // achou um buraco
                        bolhascomburacos++;
                        p.x = j;
                        p.y = i;
                        // preenche o buraco com 255
                        cv::floodFill(image, p, 255);

                        p.x = j-1;
                        //preenche a bolha com buraco com 255
                        cv::floodFill(image, p, 255);
                    }
                }
            }


            std::cout << "a figura tem " << nobjects << " bolhas total\n";
            std::cout << "a figura tem " << nobjects-bolhascomburacos << " bolhas sem buracos\n";
            std::cout << "a figura tem " << bolhascomburacos << " bolhas com buracos\n";
            cv::equalizeHist(image, realce);
            cv::imshow("image bolhas sem buracos", realce);
            cv::imwrite("exercicio3-2d.png", image);
            cv::waitKey();
            return 0;
        }
```
## Capítulo 4 - Manipulação de histogramas

### Equalização de histograma
```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace std;
        using namespace cv;

        int main(int argc, char** argv){
          Mat image, equalized;           
          int width, height;       
          VideoCapture cap(0); 
          vector<Mat> planes; 
          int key;

                cap.open(0);

          if(!cap.isOpened()){
            cout << "cameras indisponiveis" << endl;
            return -1;
          }

          cap.set(CAP_PROP_FRAME_WIDTH, 640);
          cap.set(CAP_PROP_FRAME_HEIGHT, 480);
          width = cap.get(CAP_PROP_FRAME_WIDTH); 
          height = cap.get(CAP_PROP_FRAME_HEIGHT);

          cout << "largura = " << width << endl;
          cout << "altura  = " << height << endl;

          while(1){
            cap >> image; 
            flip(image, image, 1);
            cvtColor(image, image, COLOR_BGR2GRAY); 
            equalizeHist(image, equalized);

            imshow("Imagem", image);
            imshow("Captura equalizada", equalized);
            key = waitKey(30);
            if(key == 27) break;
          }
          return 0;
        }
```
### Detector de movimentos
```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace std;
        using namespace cv;

        int main(int argc, char** argv){
          cv::Mat image;           
          int width, height;       
          cv::VideoCapture cap(0); 
          std::vector<cv::Mat> planes; 
          cv::Mat histR, histG, histB, hist_anterior; 
          int nbins = 64; 
          float range[] = {0, 255}; 
          const float *histrange = { range }; 
          bool uniform = true; 
          bool acummulate = false;
          int key;
          int dif = 0;


          cap.open(0);

          if(!cap.isOpened()){
            std::cout << "cameras indisponiveis" << std::endl;
            return -1;
          }


          cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
          cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
          width = cap.get(cv::CAP_PROP_FRAME_WIDTH); 
          height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

          std::cout << "largura = " << width << std::endl;
          std::cout << "altura  = " << height << std::endl;


          int histw = nbins, histh = nbins/2;
          cv::Mat histImgR(histh, histw, CV_8UC3, cv::Scalar(0,0,0));
          cv::Mat histImgG(histh, histw, CV_8UC3, cv::Scalar(0,0,0));
          cv::Mat histImgB(histh, histw, CV_8UC3, cv::Scalar(0,0,0));

          cap >> image;
          cv::split (image, planes); 
          cv::calcHist(&planes[0], 1, 0, cv::Mat(), hist_anterior, 1,
                         &nbins, &histrange,
                         uniform, acummulate);

          while(1){
            cap >> image; 
            cv::split (image, planes); 
            cv::calcHist(&planes[0], 1, 0, cv::Mat(), histR, 1,
                         &nbins, &histrange,
                         uniform, acummulate);
            cv::calcHist(&planes[1], 1, 0, cv::Mat(), histG, 1,
                         &nbins, &histrange,
                         uniform, acummulate);
            cv::calcHist(&planes[2], 1, 0, cv::Mat(), histB, 1,
                         &nbins, &histrange,
                         uniform, acummulate);


            for(int i=0; i<nbins; i++){
                dif += abs(histR.at<float>(i) - hist_anterior.at<float>(i));
            }

            if(dif > 12000){
                cout << "Movimento detectado! - diferenca: " << dif << endl;
            }

            hist_anterior = histR.clone();

            cv::normalize(histR, histR, 0, histImgR.rows, cv::NORM_MINMAX, -1, cv::Mat());
            cv::normalize(histG, histG, 0, histImgG.rows, cv::NORM_MINMAX, -1, cv::Mat());
            cv::normalize(histB, histB, 0, histImgB.rows, cv::NORM_MINMAX, -1, cv::Mat());

            histImgR.setTo(cv::Scalar(0));
            histImgG.setTo(cv::Scalar(0));
            histImgB.setTo(cv::Scalar(0));

            for(int i=0; i<nbins; i++){
              cv::line(histImgR,
                       cv::Point(i, histh),
                       cv::Point(i, histh-cvRound(histR.at<float>(i))),
                       cv::Scalar(0, 0, 255), 1, 8, 0);
              cv::line(histImgG,
                       cv::Point(i, histh),
                       cv::Point(i, histh-cvRound(histG.at<float>(i))),
                       cv::Scalar(0, 255, 0), 1, 8, 0);
              cv::line(histImgB,
                       cv::Point(i, histh),
                       cv::Point(i, histh-cvRound(histB.at<float>(i))),
                       cv::Scalar(255, 0, 0), 1, 8, 0);
            }
            histImgR.copyTo(image(cv::Rect(0, 0       ,nbins, histh)));
            histImgG.copyTo(image(cv::Rect(0, histh   ,nbins, histh)));
            histImgB.copyTo(image(cv::Rect(0, 2*histh ,nbins, histh)));

            cv::imshow("image", image);
            dif = 0;
            key = cv::waitKey(30);
            if(key == 27) break;
          }
          return 0;
        }
```
## Capítulo 5 - Filtragem no domínio espacial I

### Filtro laplaciano do gaussiano
```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        void printmask(cv::Mat &m) {
          for (int i = 0; i < m.size().height; i++) {
            for (int j = 0; j < m.size().width; j++) {
              std::cout << m.at<float>(i, j) << ",";
            }
            std::cout << "\n";
          }
        }

        int main(int, char **) {
          cv::VideoCapture cap;  // open the default camera
          float media[] = {0.1111, 0.1111, 0.1111, 0.1111, 0.1111,
                           0.1111, 0.1111, 0.1111, 0.1111};
          float gauss[] = {0.0625, 0.125,  0.0625, 0.125, 0.25,
                           0.125,  0.0625, 0.125,  0.0625};
          float horizontal[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
          float vertical[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
          float laplacian[] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
          float boost[] = {0, -1, 0, -1, 5.2, -1, 0, -1, 0};
          float laplgauss[] = {0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, -16, 2, 1, 0, 1, 2, 1, 0, 0, 0, 1, 0, 0};

          cv::Mat frame, framegray, frame32f, frameFiltered;
          cv::Mat mask(3, 3, CV_32F);
          cv::Mat result;
          double width, height;
          int absolut;
          char key;

          cap.open(0);

          if (!cap.isOpened())  // check if we succeeded
            return -1;

          cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
          cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
          width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
          height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
          std::cout << "largura=" << width << "\n";
          ;
          std::cout << "altura =" << height << "\n";
          ;
          std::cout << "fps    =" << cap.get(cv::CAP_PROP_FPS) << "\n";
          std::cout << "format =" << cap.get(cv::CAP_PROP_FORMAT) << "\n";

          cv::namedWindow("filtroespacial", cv::WINDOW_NORMAL);
          cv::namedWindow("original", cv::WINDOW_NORMAL);

          mask = cv::Mat(3, 3, CV_32F, media);

          absolut = 1;  // calcs abs of the image

          while(1) {
            cap >> frame;  // get a new frame from camera
            cv::cvtColor(frame, framegray, cv::COLOR_BGR2GRAY);
            cv::flip(framegray, framegray, 1);
            cv::imshow("original", framegray);
            framegray.convertTo(frame32f, CV_32F);
            cv::filter2D(frame32f, frameFiltered, frame32f.depth(), mask,
                         cv::Point(1, 1), 0);
            if (absolut) {
              frameFiltered = cv::abs(frameFiltered);
            }

            frameFiltered.convertTo(result, CV_8U);

            cv::imshow("filtroespacial", result);

            key = (char)cv::waitKey(10);
            if (key == 27) break;  // esc pressed!
            switch (key) {
              case 'a':
                absolut = !absolut;
                break;
              case 'm':
                mask = cv::Mat(3, 3, CV_32F, media);
                printmask(mask);
                break;
              case 'g':
                mask = cv::Mat(3, 3, CV_32F, gauss);
                printmask(mask);
                break;
              case 'h':
                mask = cv::Mat(3, 3, CV_32F, horizontal);
                printmask(mask);
                break;
              case 'v':
                mask = cv::Mat(3, 3, CV_32F, vertical);
                printmask(mask);
                break;
              case 'l':
                mask = cv::Mat(3, 3, CV_32F, laplacian);
                printmask(mask);
                break;
              case 'b':
                mask = cv::Mat(3, 3, CV_32F, boost);
                break;
              case 'x':
                mask = cv::Mat(5, 5, CV_32F, laplgauss);
                break;
              default:
                break;
            }
          }
          return 0;
        }
```
## Capítulo 6 - Filtragem no domínio espacial II

### Tilt-shift em imagem

### Tilt-shift em vídeo


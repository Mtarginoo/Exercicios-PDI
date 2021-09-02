# Exercícios de Processamento Digital de Imagens em OpenCV
Exercícios de programação com OpenCV realizados na disciplina DCA0445 - Processamento Digital de Imagens, componente optativo do curso de Engenharia de Computação da UFRN, ministrada pelo Prof. Dr Agostinho de Medeiros Brito Jr.

Autores:
- Lourival Alexandre 
- Matheus Targino Barbosa 

Os códigos abaixos foram escritos em linguagem C++, usando a biblioteca OpenCV em ambiente Ubuntu 20.04. Para compilar e executar cada código basta utilizar os comandos "make <nome_do_arquivo>" e "./<nome_do_arquivo>" no mesmo diretório em que se econtra o código e o arquivo Makefile, que pode ser baixado [aqui](/Makefile).  

## Capítulo 2 - Manipulando pixels em uma imagem
### Criando regiões

O primeiro programa desenvolvido tem por objetivo solicitar ao usuário dois pontos, que correspondem as coordenadas de um retângulo e dentro deste retângulo, a imagem deverá apresentar seus pixels em negativo. 

O programa deve ler uma imagem, neste caso, a figura "biel.png" para em seguida percorrer a imagem na região definida pelo usuário atribuíndo cada pixel o seu valor multiplicado por -1. A Figura abaixo ilustra a imagem utilizada neste exemplo.

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

A figura abaixo ilustra o resultado do processamento do programa acima para os pontos P1 = (100,150) e P2 = (200, 250).

![biel_png](/biel-modificado.png)


### Trocando regiões

O programa abaixo tem por objetivo conseguir ler uma imagem e fazer uma troca nos quadrantes da mesma, de forma similar a figura abaixo:

![biel_png](/biel-troca.png)

Inicialmente é realizada a leitura da imagem e criado uma cópia, para que o procedimento de troca de regiões possa ser executado na cópia, permitindo que a imagem original seja utilizada para controle das iterações 

A estratégia para que tal resultado fosse obtido é apresentado no trecho de código abaixo. A ideia consiste em percorrer toda a imagem e verificar qual quadrante está sendo percorrido no momento, dependendo do quadrante atual, a troca é realizada na figura copiada.

```c++
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
```

A figura lena.jpg foi utilizada como entrada para o programa de troca de quadrantes. 

![biel_png](/lena.jpg)

O código completo está apresentado abaixo:

```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace cv;
        using namespace std;

        int main(){
            cv::Mat image, image_trocada;                                                                                 
            cv::Vec3b val;                                                                                                

            image = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);
            image_trocada = cv::imread("lena.jpg", cv::IMREAD_GRAYSCALE);                                                
            if(!image.data)                              
                std::cout << "não abriu lena.jpg" << std::endl;

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

            return 0;
        }
```

A figura abaixo apresenta o resultado do processamento do programa.

![biel_png](/lena-troca.jpg)

## Capítulo 3 - Preeenchendo regiões

### O problema de rotulação
O problema da rotulação acontece quando existem mais de 255 objetos na imagem devido ao tipo de dado utilizado para representar os pixels da imagem. É possível melhorar o processo de rotulação apenas criando uma nova variável que ficará responsável pela cor de cada label, fazendo esta resetar quando chegar em 254 e usando a variavel nobjects para apenas contar o número de objetos.

### Identificando buracos

O programa a seguir tem a finalidade de apresentar o número de objetos que possuem e não possuem furos, além de conseguir contar uma quantidade ilimitada de objetos.

![bolhas.png](/bolhas.png)

A estratégia utilizada foi, incialmente realizar a remoção dos objetos que tocam a borda da imagem, pois não é possível saber se eles possuem ou não furos, dado que parte deles está fora da visualização da cena. Foi feito uma varredura nos pixels da borda e sempre que um objeto é encontrado, é aplicado o algoritmo floodfill a partir daquele pixel, preenchendo-o com 0, deste modo, o objeto é "transformado" no fundo da imagem e removido da cena.

```c++
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
                            // preenche o objeto com 0
                            cv::floodFill(image, p, 0);
                        }
                    }
                }
            }
```

![bolhas1.png](/exercicio3-2a.png)

Após a etapa de remoção de objetos da borda foi feito o labelling, adicionando a variável "colorobjects" para definir as cores dos objetos que já foram contados e a variável nobjects fazendo apenas a contagem. Ao final desta etapa temos o valor de quantos objetos existem na cena.

```c++
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
```

![bolhas2.png](/exercicio3-2b.png)

Após a etapa de labelling dos objetos foi feito o floodfill no pixel (0,0) com a cor 255 afim de auxiliar a detecção de elementos que tem ou não buracos.

```c++
        // floodfill background aplicado no pixel (0,0)
        p.x = 0;
        p.y = 0;
        cv::floodFill(image, p, 255);
```

![bolhas3.png](/exercicio3-2c.png)

Após a etapa de floodfill do background foi feito a contagem dos objetos com buracos e sua remoção da cena. A contagem foi feita varrendo toda a cena e verificando se existia algum pixel com a cor 0 já que o fundo agora é 255, todos os pixel com a cor 0 representam os buracos nos objetos. Quando encontrado o buraco, aplica o floodfill no pixel que esta com a cor 0 e no pixel acima, ou a sua esquerda como preferir, para fazer a remoção do mesmo.

```c++
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
```

![bolhas4.png](/exercicio3-2d.png)

Após essas etapas é só mostrar na tela o valor das variáveis "nobjects" para o número total de objetos na cena sem contar os da borda, "nobjects-bolhascomburacos" para o número de objetos sem buracos e "bolhascomburacos" para o número de objetos com buracos.

O código completo está apresentado abaixo:

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

            // floodfill background aplicado no pixel (0,0)
            p.x = 0;
            p.y = 0;
            cv::floodFill(image, p, 255);


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

O programa abaixo tem por objetivo a aquisição de uma cena a partir de uma câmera de video e realizar o cálculo do histograma equalizado em tempo real. 

Os objetos image e equalized são usados, respectivamente, para armazenar a imagem capturada e a imagem processada no procedimento de equalização do histograma. O acesso a câmera é feito através do objeto cap, pelo método cap.open(0), no qual o parâmetro indica a câmera a ser requisitada para o sistema operacional (caso o computador esteja conectado a mais de um dispositivo).

```c++
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

```
O programa roda em um loop infinito, fazendo o redirecionamento do fluxo das imagens capturadas pelo objeto cap para image. a captura é invertida pela função flip e convertida para escala de cinza pela função cvtColor. Com a função equalizeHist é feito o cálculo do histograma normalizado e em seguida é exibido em tela a imagem captura sem nenhum processamento (apenas invertida) e a imagem cujo o histograma foi equalizado.

```c++
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

A figura abaixo apresenta o resultado do programa. 

![histogramaEqualizado.png](/histogramaEqualizado.png)

O código completo está apresentado abaixo:

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

O programa a seguir tem a função de fazer a detecção de movimentos em uma cena capturada por um dispositivo de video em tempo real. A estratégia utilizada para a resolução do problema foi a utilização do cálculo da diferença entre os histogramas calculados a cada itereção do programa. O histograma da imagem varia de acordo com a variação das cores capturadas, seja por mudança de iluminação ou posicionamento dos objetos. Desta forma, analisar a diferença entre dois histogramas pode ser útil para o processo de detecção de movimentos.

```c++
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
```

A captura do video é redirecionada para o objeto image, que por sua vez tem seus canais de cor divididos no objeto planes, onde cada índice (0, 1 e 2) armazenam cada canal de cor RGB. O cálculo da comparação do histograma é realizado apenas com o canal de cor RED, o que é o sulficente para esta aplicação. O histograma atual é percorrido e para cada barra (bin) é acumulado o valor da difernça entre o histograma atual e o histograma anterior. Caso esse valor seja maior que 12000 (valor que melhor se comportou e foi obtido experimentalmente) é considerado que houve movimentação na cena, caso contrário, é suposto que não houve movimento.

O resultado do programa bem como o código fonte completo pode ser visualizado abaixo.

![motionDetector.png](/motionDetector.png)

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

O programa abaixo tem a finalidade de implementar, além dos filtros pré-existentes, no código disponibilizado pelo professor o kernel Laplaciano do Gaussiano. Este kernel calcula as derivadas segundas de uma imagem, desta forma, torna zero áreas com intensidades constantes e nas áreas onde existe mudança de intensidade, a resposta do Laplaciano do Gaussiano será positiva no lado mais escuro e negativa no lado mais claro. A matriz correspondente ao kernel Laplaciano do Gaussiano está mostrada na figura abaixo.

![LoG.png](/LoG.png)

O kernel é armazenado na variável laplgauss em forma de um vetor.

```c++
  float laplgauss[] = {0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, -16, 2, 1, 0, 1, 2, 1, 0, 0, 0, 1, 0, 0};
```

Caso seja precionada a tecla x durante a execução do programa o filtro será aplicado na imagem capturada pela câmera.

```c++
case 'x':
                mask = cv::Mat(5, 5, CV_32F, laplgauss);
                break;
```
Abaixo pode ser visualizado as imagens correspondentes a cena capturada sem nenhum processamento e a aplicação do filtro Laplaciano do Gaussiano. Também é apresentado o código completo da implementação do programa.

![lap_gauss.png](/lap_gauss.png)

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

Utilizando o programa exemplos/addweighted.cpp como referência, implementamos um programa para a realização do tilt-shift em uma imagem colorida cujo centro, região de decaimento e posição vertical do efeito podem ser alterados por meio de sliders. Para a realização desse efeito, foram criadas duas matrizes cujos valores do eixo x foram dados pela seguinte equação:

![tiltequa.png](/tiltequa.png)

Em que centro indica o centro da região em foco, l1 e l2 os limites dessa região e d o quão suave será a transição entre a imagem focada e a borrada.

A matriz resultante desse cálculo é usada para ponderar a imagem sem efeito, e sua inversa 1−f(x) para ponderar a imagem borrada. Em seguida, ambas são somadas, criando o efeito do tilt-shift.

```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>

        using namespace cv;
        using namespace std;

        float l1 = -100, l2 = 50, d = 6, centro = 100;

        int matriz_media_tam = 7;
        int altura, largura;

        int slider_altura = 0;
        int slider_altura_max = 100;

        int slider_decaimento = 0;
        int slider_decaimento_max = 100;

        int slider_deslocamento = 0;
        int slider_deslocamento_max = 100;

        Mat imagem, imagem_borrada;

        char TrackbarName[50];

        void aplicar_Efeito();

        void on_trackbar_deslocamento(int, void *)
        {
                centro = slider_deslocamento * altura / 100;

                aplicar_Efeito();
        }

        void on_trackbar_altura(int, void *)
        {
                int alt = altura * slider_altura / 100;
                l1 = -alt / 2;
                l2 = alt / 2;

                aplicar_Efeito();
        }

        void on_trackbar_decaimento(int, void *)
        {
                d = slider_decaimento;

                aplicar_Efeito();
        }

        void aplicar_Efeito()
        {
                Mat ponderada(altura, largura, CV_32FC3);
                Mat ponderada_negativa(altura, largura, CV_32FC3);

                for (int i = 0; i < altura; i++)
                {
                        float fx = 0.0;
                        if (d != 0)
                        {
                                fx = -0.5 * (tanh((i - centro + l1) / d) - tanh((i - centro + l2) / d));
                        }
                        else{
                                fx = -0.5 * (tanh((i - centro + l1) / 0.01) - tanh((i - centro + l2) / 0.01));
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

                Mat resultado, res1, res2;

                multiply(imagem, ponderada, res1);
                multiply(imagem_borrada, ponderada_negativa, res2);

                addWeighted(res1, 1, res2, 1, 0, resultado);

                resultado.convertTo(resultado, CV_8UC3);

                imshow("tiltshift", resultado);
        }

        int main(int argvc, char **argv)
        {
                float media[matriz_media_tam * matriz_media_tam];
                for (int i = 0; i < matriz_media_tam; i++)
                {
                        for (int j = 0; j < matriz_media_tam; j++)
                        {
                                media[i * matriz_media_tam + j] = 1.0 / (matriz_media_tam * matriz_media_tam);
                        }
                }
                Mat masc_media(matriz_media_tam, matriz_media_tam, CV_32F, media);

                vector<Mat> canais;

                imagem = imread(argv[1]);
                imagem.convertTo(imagem, CV_32FC3);

                split(imagem, canais);

                filter2D(canais[0], canais[0], canais[0].depth(), masc_media, Point(3, 3), 0);
                filter2D(canais[1], canais[1], canais[1].depth(), masc_media, Point(3, 3), 0);
                filter2D(canais[2], canais[2], canais[2].depth(), masc_media, Point(3, 3), 0);

                merge(canais, imagem_borrada);

                largura = imagem.cols;
                altura = imagem.rows;

                namedWindow("tiltshift", 1);

                sprintf(TrackbarName, "Altura x %d", slider_altura_max);
                createTrackbar(TrackbarName, "tiltshift",
                                &slider_altura,
                                slider_altura_max,
                                on_trackbar_altura);
                
                on_trackbar_altura(slider_altura, 0);

                sprintf(TrackbarName, "Decaimento x %d", slider_decaimento_max);
                createTrackbar(TrackbarName, "tiltshift",
                                &slider_decaimento,
                                slider_decaimento_max,
                                on_trackbar_decaimento);
  
                on_trackbar_decaimento(slider_decaimento, 0);

                sprintf(TrackbarName, "Deslocamento x %d", slider_deslocamento_max);
                createTrackbar(TrackbarName, "tiltshift",
                                &slider_deslocamento,
                                slider_deslocamento_max,
                                on_trackbar_deslocamento);
                
                on_trackbar_deslocamento(slider_deslocamento, 0);

                aplicar_Efeito();

                waitKey(0);
                return 0;
        }

```

A seguir é possível ver a imagem sem e com o efeito tiltshift.

![tiltshift original.png](/tiltshift_original.png)

![tiltshift efeito.png](/tiltshift_efeito.png)

### Tilt-shift em vídeo

Ainda usando exemplos/addweighted.cpp como base, foi criado um programa que aplica o efeito de tilt-shift e stop motion em um vídeo colorido. Para isso, além de efetuar os mesmos procedimentos do exercício anterior para o tilt-shift, foi colocado um laço que descarta aceleracao frames do video antes de processar um frame, criando o efeito de stop motion.

```c++
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
                        {
                                break;
                        }
                }

                return 0;
        }


```

![tiltshiftvideo.png](/tiltshiftvideo.png)

## Capítulo 7 - Filtragem no domínio da frequência

### Filtro Homomórfico

descrição

O programa recebe como entrada uma imagem em tons de cinza. Ao pressionar as teclas configuradas são alterados os parâmetros de iluminânica, refletância, frequência de corte e valor da constante. Inicialmente é realizada uma etapa de pré-procesamento para que seja aplicado o padding na imagem. Logo após, é inicializada a matriz responsável por guardar as componentes real e imaginária da imagem filtrada.

```c++
        #include <iostream>
        #include <opencv2/opencv.hpp>
        #include <opencv2/imgproc/imgproc.hpp>

        #define RADIUS 20

        using namespace cv;
        using namespace std;

        // troca os quadrantes da imagem da DFT
        void deslocaDFT(Mat& image ){
                Mat tmp, A, B, C, D;

                // se a imagem tiver tamanho impar, recorta a regiao para
                // evitar cópias de tamanho desigual
                image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
                int cx = image.cols/2;
                int cy = image.rows/2;

                // reorganiza os quadrantes da transformada
                // A B   ->  D C
                // C D       B A
                A = image(Rect(0, 0, cx, cy));
                B = image(Rect(cx, 0, cx, cy));
                C = image(Rect(0, cy, cx, cy));
                D = image(Rect(cx, cy, cx, cy));

                // A <-> D
                A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

                // C <-> B
                C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
        }

        int main(int , char**){
                VideoCapture cap;
                Mat imaginaryInput, complexImage, multsp;
                Mat padded, filter, mag;
                Mat image, imagegray, tmp;
                Mat_<float> realInput, zeros;
                  vector<Mat> planos;

                  float Gh = 1.0, Gl = 1.0, d = 1.0, c = 1.0;
                  double radius;

                  // guarda tecla capturada
                  char key;

                  // valores ideais dos tamanhos da imagem
                  // para calculo da DFT
                  int dft_M, dft_N;

                  // abre a câmera default
                  cap.open(0);
                  if(!cap.isOpened())
                    return -1;

                  // captura uma imagem para recuperar as
                  // informacoes de gravação
                  cap >> image;

                  // identifica os tamanhos otimos para
                  // calculo do FFT
                  dft_M = getOptimalDFTSize(image.rows);
                  dft_N = getOptimalDFTSize(image.cols);

                  // realiza o padding da imagem
                  copyMakeBorder(image, padded, 0,
                                 dft_M - image.rows, 0,
                                 dft_N - image.cols,
                                 BORDER_CONSTANT, Scalar::all(0));

                  // parte imaginaria da matriz complexa (preenchida com zeros)
                  zeros = Mat_<float>::zeros(padded.size());

                  // prepara a matriz complexa para ser preenchida
                  complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));

                  // a função de transferência (filtro frequencial) deve ter o
                  // mesmo tamanho e tipo da matriz complexa
                  filter = complexImage.clone();

                  // cria uma matriz temporária para criar as componentes real
                  // e imaginaria do filtro ideal
                  tmp = Mat(dft_M, dft_N, CV_32F);

                  // prepara o filtro homomorfico
                  for(int i=0; i<dft_M; i++)
                  {
                    for(int j=0; j<dft_N; j++)
                    {
                      radius = (double) (i - dft_M / 2) * (i - dft_M / 2) + (j - dft_N / 2) * (j - dft_N / 2);
                      tmp.at<float> (i, j) = (Gh - Gl) * (1 - exp(-c * (radius / pow(d, 2)))) + Gl;
                    }
                  }

                  // cria a matriz com as componentes do filtro e junta
                  // ambas em uma matriz multicanal complexa
                  Mat comps[]= {tmp, tmp};
                  merge(comps, 2, filter);

                  for(;;){
                    cap >> image;
                    cvtColor(image, imagegray, COLOR_BGR2GRAY);
                    imshow("original", imagegray);

                    // realiza o padding da imagem
                    copyMakeBorder(imagegray, padded, 0,
                                   dft_M - image.rows, 0,
                                   dft_N - image.cols,
                                   BORDER_CONSTANT, Scalar::all(0));

                    // limpa o array de matrizes que vao compor a
                    // imagem complexa
                    planos.clear();
                    // cria a compoente real
                    realInput = Mat_<float>(padded);
                    // insere as duas componentes no array de matrizes
                    planos.push_back(realInput);
                    planos.push_back(zeros);

                    // combina o array de matrizes em uma unica
                    // componente complexa
                    merge(planos, complexImage);

                    // calcula o dft
                    dft(complexImage, complexImage);

                    // realiza a troca de quadrantes
                    deslocaDFT(complexImage);

                    // aplica o filtro frequencial
                    mulSpectrums(complexImage,filter,complexImage,0);

                    // limpa o array de planos
                    planos.clear();

                    // troca novamente os quadrantes
                    deslocaDFT(complexImage);

                    cout << "Gl = " << Gl << " Gh = " << Gh << " D0 = " << d << " c = " << c << endl;
                    // calcula a DFT inversa
                    idft(complexImage, complexImage);

                    // limpa o array de planos
                    planos.clear();

                    // separa as partes real e imaginaria da
                    // imagem filtrada
                    split(complexImage, planos);

                    // normaliza a parte real para exibicao
                    normalize(planos[0], planos[0], 0, 1, NORM_MINMAX);
                    imshow("filtrada", planos[0]);

                    key = (char) waitKey(10);
                    if( key == 27 ) break; // esc pressed!
                    switch(key){
                      // aumenta o componente de iluminância (Gl)
                    case 'a':
                      Gl = Gl + 1;
                      break;
                      // diminui o componente de iluminância (Gl)
                    case 's':
                      Gl = Gl - 1;
                      break;
                      // aumenta o componente de refletância (Gh)
                    case 'd':
                      Gh = Gh + 1;
                      break;
                      // diminui o componente de refletância (Gh)
                    case 'f':
                      Gh = Gh - 1;
                      // aumenta o componente de frequencia de corte (d)
                    case 'g':
                      d = d + 1;
                      break;
                      // diminui o componente de frequencia de corte (d)
                    case 'h':
                      d = d - 1;
                      break;
                      // aumenta a constante (c)
                    case 'j':
                      c = c + 1;
                      break;
                      // diminui a constante (c)
                    case 'k':
                      c = c - 1;
                      break;
                    }
                  }
                  return 0;
        }


```

A seguir é possível ver as imagens.

![Seleção_014.png](/Seleção_014.png)


## Capítulo 8 - Detecção de bordas com o algoritmo de Canny

### Canny - Pontilhismo

descrição

```c++
#include <iostream>
#include "opencv2/opencv.hpp"
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;


#define STEP 4
#define JITTER 2
#define RAIO 5

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];

Mat image,imgray, border,points;
  int width, height;
  Vec3b colors;
  int x, y;
  vector<int> yrange;
  vector<int> xrange;

void on_trackbar_canny(int, void*){

  Canny(imgray, border, top_slider, 3*top_slider);
  imshow("cannyborders.png", border);
  points = Mat(height, width, CV_8UC3, Scalar(255,255,255));
  std::random_shuffle(xrange.begin(), xrange.end());
  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){

      if(border.at<uchar>(j,i) == 255)
      {
          x = i+rand()%(2*JITTER)-JITTER+1;
          y = j+rand()%(2*JITTER)-JITTER+1;
          colors = image.at<Vec3b>(y,x);
          circle(points, Point(x,y),2, CV_RGB(colors[2],colors[1],colors[0]), -1, LINE_AA);
      }
      else{
          x = i+rand()%(2*JITTER)-JITTER+1;
          y = j+rand()%(2*JITTER)-JITTER+1;
          colors = image.at<Vec3b>(x,y);
          circle(points,
                 cv::Point(y,x),
                 RAIO,
                 CV_RGB(colors[2],colors[1],colors[0]),
                 -1,
                 LINE_AA);
      }
    }
  }
  imshow("canny",points);

}

int main(int argc, char**argv){

  image= imread(argv[1],IMREAD_COLOR);
  cvtColor(image,imgray, COLOR_BGR2GRAY);

  srand(time(0));

  if(!image.data){
  cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;

  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }
  
  namedWindow("canny",1);
  
  sprintf(TrackbarName, "Limiar Inferior:");

  createTrackbar( TrackbarName, "canny",
                &top_slider,
                top_slider_max,
                on_trackbar_canny );

  on_trackbar_canny(top_slider, 0 );

  waitKey();
  imwrite("cannypontos.png",points);
  return 0;
}

```

A seguir é possível ver as imagens com a arte do pontilhismo com Limiar inferior=100.

![pontilhismo100.png](/pontilhismo100.png)

![pontilhismo100result.png](/pontilhismo100result.png)

A seguir é possível ver as imagens com a arte do pontilhismo com Limiar inferior=200.

![pontilhismo200.png](/pontilhismo200.png)

![pontilhismo200result.png](/pontilhismo200result.png)

## Capítulo 9 - Quantização vetorial com k-means

### K-means

descrição

```c++

#include <opencv2/opencv.hpp>
#include <cstdlib>
//#include <string>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
        int nClusters = 6;
        Mat rotulos;
        int nRodadas = 1;
        Mat centros;

        stringstream saida_nome;
        string saida;
        int cont = 0;

        Mat img = imread("imagem.jpg", IMREAD_COLOR);
        Mat samples(img.rows * img.cols, 3, CV_32F);

        while (cont < 20) {
                for (int y = 0; y < img.rows; y++) {
                        for (int x = 0; x < img.cols; x++) {
                                for (int z = 0; z < 3; z++) {
                                        samples.at<float>(y + x * img.rows, z) = img.at<Vec3b>(y, x)[z];
                                }
                        }
                }

                kmeans(samples,
                        nClusters,
                        rotulos,
                        TermCriteria(TermCriteria::MAX_ITER|TermCriteria::EPS, 10000, 0.0001),
                        nRodadas,
                        KMEANS_RANDOM_CENTERS,
                        centros);

                Mat rotulada(img.size(), img.type());
                for (int y = 0; y < img.rows; y++) {
                        for (int x = 0; x < img.cols; x++) {
                                int indice = rotulos.at<int>(y + x * img.rows, 0);
                                rotulada.at<Vec3b>(y, x)[0] = (uchar)centros.at<float>(indice, 0);
                                rotulada.at<Vec3b>(y, x)[1] = (uchar)centros.at<float>(indice, 1);
                                rotulada.at<Vec3b>(y, x)[2] = (uchar)centros.at<float>(indice, 2);
                        }
                }
                saida_nome.str(""); //limpa o string stream
                saida_nome << "resultado" << cont << ".png";
                saida = saida_nome.str();

                //imshow("clustered image 2", rotulada);
                imwrite(saida, rotulada);
                cont++;
        }
        //waitKey(0);
}

```

A seguir é possível ver imagem original e a imagem após 19 iterações do metódo k-means.

![imagem.jpg](/imagem.jpg)

![resultado19.png](/resultado19.png)

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

![tiltshift.png](/tiltshift.png)

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


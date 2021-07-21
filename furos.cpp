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
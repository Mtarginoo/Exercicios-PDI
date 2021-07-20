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
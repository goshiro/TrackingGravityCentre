#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
  cv::VideoCapture cap;
  cap.open(argv[1]);
  cv::namedWindow("movie", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
  
  cv::Mat img;
  cv::Mat gray;
  cv::Mat bin;
  
  FILE *fp;
  fp = fopen("center.txt", "w");
  
  if ( fp == NULL ) {
    std::cout<< "Can't create out put file" << std::endl;
    return 0;
  }
  
  while ( 1 ) {
    cap >> img;
    
    gray = cv::Mat(img.size(), CV_8U);
    cv:cvtColor(img, gray, CV_RGB2GRAY);
    
    
    bin = gray.clone();
    cv::threshold(gray, bin, 127, 255, CV_THRESH_BINARY);
    
    int m00 = 0;
    int m10 = 0;
    int m01 = 0;
    
    for ( int y = 0; y < bin.rows; y++ ) {
      for ( int x = 0; x < bin.cols; x++ ) {
        if ( *(bin.data + x + y * bin.cols) == 255 ) {
          m00++;
          m10 += x;
          m01 += y;
        }
      }
    }
    
    double cx, cy;
    cx = cy = 0.0;
    if ( m00 > 0 ) {
      cx = (double)m10 / (double)m00;
      cy = (double)m01 / (double)m00;
    }
    
    fprintf(fp, "%lf, %lf\n", cx, cy);
    
    std::cout << cx << ", " << cy << std::endl;
    cv::imshow("movie", bin);

    char ch = cv::waitKey(30);
    if ( ch == 27 ) break;
  }
  
  fclose(fp);
  
 return 0;
}

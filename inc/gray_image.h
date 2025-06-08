#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
  int** pixels;
public:
  GrayImage();
  GrayImage(int w,int h,int** p);
  GrayImage(const GrayImage& copy);
  ~GrayImage();
  bool LoadImage(string filename);
  void DumpImage(string filename);
  void Display_X_Server();
  void Display_ASCII();
  void Display_CMD();
  Image* horizontalflip();
  Image* mosaic(int block=8);
  Image* Gaussian(double sigma=10,int k=2);
  Image* laplacian(int d=0);
  Image* fisheye(float k=0.5);
  int getdata(int w,int h);
  void modifydata(int w,int h,int d);
};

#endif
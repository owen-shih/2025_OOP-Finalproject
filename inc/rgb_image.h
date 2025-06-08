#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
private:
  int*** pixels;
public:
  RGBImage();
  RGBImage(int w,int h,int ***p);
  RGBImage(const RGBImage& copy);
  ~RGBImage();
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
  Image* invert();
  Image* emboss();
  Image* oilpainting(int r=3);
  int getdata(int w,int h,int c);
  void modifydata(int w,int h,int c,int d);
};

#endif



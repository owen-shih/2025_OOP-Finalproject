#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"
#include <bits/stdc++.h>
using namespace std;

class Image{
protected:
  int iwidth;
  int iheight;
  Data_Loader data;
public:
  Image();
  Image(int w,int h);
  virtual~Image();
  virtual bool LoadImage(string filename)=0;
  virtual void DumpImage(string filename)=0;
  virtual void Display_X_Server()=0;
  virtual void Display_ASCII()=0;
  virtual void Display_CMD()=0;
  virtual Image* horizontalflip()=0;
  virtual Image* mosaic(int block=8)=0;
  virtual Image* laplacian(int d=0)=0;
  virtual Image* Gaussian(double sigma=10,int k=2)=0;
  virtual Image* fisheye(float k=0.5)=0;
  int get_width();
  int get_height();

};

#endif
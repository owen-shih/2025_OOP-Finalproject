#include "image.h"
#include <bits/stdc++.h>
using namespace std;
Image::Image():iwidth(0),iheight(0){}
Image::Image(int width,int height):iwidth(width),iheight(height){}
Image::~Image()
{;}
int Image::get_width()
{
  return iwidth;
}
int Image::get_height()
{
  return iheight;
}
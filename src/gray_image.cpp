#include "gray_image.h"
#include <bits/stdc++.h>
using namespace std;

GrayImage::GrayImage():pixels(nullptr){}
GrayImage::GrayImage(int w,int h,int**p):Image(w,h),pixels(p){}
GrayImage::GrayImage(const GrayImage& copy):Image(copy.iwidth,copy.iheight){
  pixels=new int*[iheight];
  for(int i=0;i<iheight;i++)
  {
    pixels[i]=new int[iwidth];
    for(int j=0;j<iwidth;j++)
        pixels[i][j]=copy.pixels[i][j];
  }
}
GrayImage::~GrayImage()
{
  if(pixels!=nullptr)
  {
    for(int i=0;i<iheight;i++)
        delete []pixels[i];
    delete []pixels;
  }
}
bool GrayImage::LoadImage(string filename){
  pixels=data.Load_Gray(filename,&iwidth,&iheight);
  if(pixels!=nullptr)
    return true;
  else
    return false;
}
void GrayImage::DumpImage(string filename){
  data.Dump_Gray(iwidth,iheight,pixels,filename);
}
void GrayImage::Display_X_Server(){
  data.Display_Gray_X_Server(iwidth,iheight,pixels);
}
void GrayImage::Display_ASCII(){
  data.Display_Gray_ASCII(iwidth,iheight,pixels);
}
void GrayImage::Display_CMD(){;}
int GrayImage::getdata(int w,int h){
  return pixels[w][h];
}
void GrayImage::modifydata(int w,int h,int d){
  pixels[w][h]=d;
}
Image* GrayImage::horizontalflip(){
  //create an 3D array for modify
  int**temp=new int*[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int[iwidth];
    for(int j=0;j<iwidth;j++)
      temp[i][j]=pixels[i][j];
  }
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth/2;j++)
    {
      int t=iwidth-j-1;
      for(int k=0;k<3;k++)
        swap(temp[i][j],temp[i][t]);
    }
  }
  return new GrayImage(iwidth,iheight,temp);
}
Image* GrayImage::mosaic(int block){
  //create an 3D array for modification
  int**temp=new int*[iheight];
  for(int i=0;i<iheight;i++)
    temp[i]=new int[iwidth];
  
  for(int i=0;i<iheight;i=i+block)
  {
    for(int j=0;j<iwidth;j=j+block)
    {
      int sum=0;
      int hbottom=min(block,iheight-i); //when it comes to edge,that the
      int wbottom=min(block,iwidth-j);// remians is smaller than block;
      for(int p=0;p<hbottom;p++)
      {
         for(int q=0;q<wbottom;q++)
         {
           for(int c=0;c<3;c++)
             sum=sum+pixels[i+p][j+q];
         }
      }
      int value;
        value=sum/(hbottom*wbottom);
      for(int p=0;p<hbottom;p++)
      {
        for(int q=0;q<wbottom;q++)
            temp[i+p][j+q]=value;
      }
    }
  }
  return new GrayImage(iwidth,iheight,temp);
}  
Image* GrayImage::Gaussian(double sigma,int k){
  int**temp=new int*[iheight];
  for(int i=0;i<iheight;i++)
    temp[i]=new int[iwidth];
    
  double G[2*k+1][2*k+1];
  double sum=0;
  for(int gi=-k;gi<=k;gi++)
  {
    for(int gj=-k;gj<=k;gj++)
    {
      G[gi+k][gj+k]=(1.0/2.0*M_PI*sigma*sigma)*exp(-1*(gi*gi+gj*gj)/(sigma*sigma));
      sum=sum+G[gi+k][gj+k];
    }
  }
  for(int gi=-k;gi<=k;gi++)
  {
    for(int gj=-k;gj<=k;gj++)
      G[gi+k][gj+k]=G[gi+k][gj+k]/sum;
  }
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      double t=0;
      for(int gi=-k;gi<=k;gi++)
      {
        for(int gj=-k;gj<=k;gj++)
        {
          int ii=i+gi,jj=j+gj;
          if(ii<0)
            ii=0;
          if(ii>=iheight)
            ii=iheight-1;
          if(jj<0)
            jj=0;
          if(jj>=iwidth) 
            jj=iwidth-1;
          t=t+G[gi+k][gj+k]*pixels[ii][jj];
        }  
      }

        int v=t;
        if(v<0)
          v=0;
        if(v>255)
          v=255;
        temp[i][j]=v;
    }
  }
  return new GrayImage(iwidth,iheight,temp);
}
Image* GrayImage::laplacian(int d){
  int**temp=new int*[iheight];
  for(int i=0;i<iheight;i++)
    temp[i]=new int[iwidth];
    
  int kernal1[3][3]={{0,-1,0},{-1,5,-1},{0,-1,0}};
  int kernal2[3][3]={{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};
  if(d==0)
  {
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      int t=0;
      for(int ki=-1;ki<=1;ki++)
      {
        for(int kj=-1;kj<=1;kj++)
        {
          int ii=i+ki;
          int jj=j+kj;
          if(ii<0)
            ii=0;
          if(ii>=iheight)
            ii=iheight-1;
          if(jj<0)
            jj=0;
          if(jj>=iwidth)
            jj=iwidth-1;
          t=t+kernal1[ki+1][kj+1]*pixels[ii][jj];
        }
      }
        int v=t;
        if(v<0)
          v=0;
        if(v>255)
          v=255;
        temp[i][j]=v;
    }
  }
  }
  else
  {
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      int t=0;
      for(int ki=-1;ki<=1;ki++)
      {
        for(int kj=-1;kj<=1;kj++)
        {
          int ii=i+ki;
          int jj=j+kj;
          if(ii<0)
            ii=0;
          if(ii>=iheight)
            ii=iheight-1;
          if(jj<0)
            jj=0;
          if(jj>=iwidth)
            jj=iwidth-1;
          t=t+kernal2[ki+1][kj+1]*pixels[ii][jj];
        }
      }
        int v=t;
        if(v<0)
          v=0;
        if(v>255)
          v=255;
        temp[i][j]=v;
    }
  }
 }
 return new GrayImage(iwidth,iheight,temp);
}
Image* GrayImage::fisheye(float k){   
  int**temp=new int*[iheight];
  for(int i=0;i<iheight;i++)
    temp[i]=new int[iwidth];
    
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      //normalize to [-1,1]
      float u=(j-iwidth/2.0)/(iwidth/2.0);
      float v=(i-iheight/2.0)/(iheight/2.0);
      //polar coordinate
      float r=sqrt(u*u+v*v);
      float angle=atan2(v,u);
      //outside the circle
      if(r>1)
      {
        temp[i][j]=0;
      }
      else
      {
        r=pow(r,k);
        //turn back
        float uu=r*cos(angle);
        float vv=r*sin(angle);
        int sj=uu*(iwidth/2.0)+iwidth/2.0;
        int si=vv*(iheight/2.0)+iheight/2.0;
        temp[i][j]=pixels[si][sj];
      }
    }
  }
  return new GrayImage(iwidth,iheight,temp);
}





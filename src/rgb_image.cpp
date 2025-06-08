#include "rgb_image.h"
#include <bits/stdc++.h>
using namespace std;
RGBImage::RGBImage():pixels(nullptr){}
RGBImage::RGBImage(int w,int h,int***p):Image(w,h),pixels(p){}
RGBImage::RGBImage(const RGBImage& copy):Image(copy.iwidth,copy.iheight){
  pixels=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    pixels[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      pixels[i][j]=new int[3];
      for(int c=0;c<3;c++)
      {
        pixels[i][j][c]=copy.pixels[i][j][c];
      }
    }
  }
}
RGBImage::~RGBImage()
{
  if(pixels!=nullptr)
  {
    for(int i=0;i<iheight;i++)
    {
      for(int j=0;j<iwidth;j++)
        delete []pixels[i][j];
      delete []pixels[i];
    
    }
    delete []pixels;
  }
}
bool RGBImage::LoadImage(string filename){
  pixels=data.Load_RGB(filename,&iwidth,&iheight);
  if(pixels!=nullptr)
    return true;
  else
    return false;
}
void RGBImage::DumpImage(string filename){
  data.Dump_RGB(iwidth,iheight,pixels,filename);
}
void RGBImage::Display_X_Server(){
  data.Display_RGB_X_Server(iwidth,iheight,pixels);
}
void RGBImage::Display_ASCII(){
  data.Display_RGB_ASCII(iwidth,iheight,pixels);
}
void RGBImage::Display_CMD(){;}
int RGBImage::getdata(int w,int h,int c){
  return pixels[w][h][c];
}
void RGBImage::modifydata(int w,int h,int c,int d){
  pixels[w][h][c]=d;
}
Image* RGBImage::horizontalflip(){
  //create an 3D array for modify
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
      for(int c=0;c<3;c++)
        temp[i][j][c]=pixels[i][j][c];
    }
  }
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth/2;j++)
    {
      int t=iwidth-j-1;
      for(int k=0;k<3;k++)
        swap(temp[i][j][k],temp[i][t][k]);
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}
Image* RGBImage::mosaic(int block){
  //create an 3D array for modification
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
    }
  }
  
  for(int i=0;i<iheight;i=i+block)
  {
    for(int j=0;j<iwidth;j=j+block)
    {
      int sum[3]{};
      int hbottom=min(block,iheight-i); //when it comes to edge,that the
      int wbottom=min(block,iwidth-j);// remians is smaller than block;
      for(int p=0;p<hbottom;p++)
      {
         for(int q=0;q<wbottom;q++)
         {
           for(int c=0;c<3;c++)
           {
             sum[c]=sum[c]+pixels[i+p][j+q][c];
           }
         }
      }
      int value[3];
      for(int c=0;c<3;c++)
        value[c]=sum[c]/(hbottom*wbottom);
      for(int p=0;p<hbottom;p++)
      {
        for(int q=0;q<wbottom;q++)
        {
          for(int c=0;c<3;c++)
            temp[i+p][j+q][c]=value[c];
        }
      }
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}  
Image* RGBImage::Gaussian(double sigma,int k){
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
    }
  }
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
      double t[3]{0};
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
          for(int c=0;c<3;c++)
            t[c]=t[c]+G[gi+k][gj+k]*pixels[ii][jj][c];
        }  
      }
      for(int c=0;c<3;c++)
      {
        int v=t[c];
        if(v<0)
          v=0;
        if(v>255)
          v=255;
        temp[i][j][c]=v;
      }
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}
Image* RGBImage::laplacian(int d){
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
    }
  }
  int kernal1[3][3]={{0,-1,0},{-1,5,-1},{0,-1,0}};
  int kernal2[3][3]={{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};
  if(d==0)
  {
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      int t[3]{0};
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
          for(int c=0;c<3;c++)
            t[c]=t[c]+kernal1[ki+1][kj+1]*pixels[ii][jj][c];
        }
      }
      for(int c=0;c<3;c++)
      {
        int v=t[c];
        if(v<0)
          v=0;
        if(v>255)
          v=255;
        temp[i][j][c]=v;
      }
    }
  }
}
  else
  {
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      int t[3]{0};
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
          for(int c=0;c<3;c++)
            t[c]=t[c]+kernal2[ki+1][kj+1]*pixels[ii][jj][c];
        }
      
      }
      for(int c=0;c<3;c++)
      {
        int v=t[c];
        if(v<0)
          v=0;
        if(v>255)
          v=255;
        temp[i][j][c]=v;
      }
    }
  }
 }
 return new RGBImage(iwidth,iheight,temp);
}
Image* RGBImage::fisheye(float k){   
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
    }
  }
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
        temp[i][j][0]=0;
        temp[i][j][1]=0;
        temp[i][j][2]=0;
      }
      else
      {
        r=pow(r,k);
        //turn back
        float uu=r*cos(angle);
        float vv=r*sin(angle);
        int sj=uu*(iwidth/2.0)+iwidth/2.0;
        int si=vv*(iheight/2.0)+iheight/2.0;
        for(int c=0;c<3;c++)
          temp[i][j][c]=pixels[si][sj][c];
      }
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}
Image* RGBImage::invert(){
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
      for(int c=0;c<3;c++)
        temp[i][j][c]=255-pixels[i][j][c];
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}
Image* RGBImage::emboss(){
  int k[3][3]={{-2,-1,0},{-1,1,1},{0,1,2}};
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
    }
  }
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      int t[3]{0};
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
          for(int c=0;c<3;c++)
            t[c]=t[c]+k[ki+1][kj+1]*pixels[ii][jj][c];
        }
      }
      for(int c=0;c<3;c++)
        temp[i][j][c]=t[c]+128;
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}
Image* RGBImage::oilpainting(int r){
  int***temp=new int**[iheight];
  for(int i=0;i<iheight;i++)
  {
    temp[i]=new int*[iwidth];
    for(int j=0;j<iwidth;j++)
    {
      temp[i][j]=new int[3];
    }
  }
  for(int i=0;i<iheight;i++)
  {
    for(int j=0;j<iwidth;j++)
    {
      int times[3][256]={0};
      for(int ki=-r;ki<=r;ki++)
      {
        for(int kj=-r;kj<=r;kj++)
        {
          int ii=i+ki;
          int jj=j+kj;
          if((ii>=0)&&(ii<iheight)&&(jj>=0)&&(jj<iwidth))
          {
            for(int c=0;c<3;c++)
              times[c][pixels[ii][jj][c]]++;//accumulate the number of r,g,bness(0-255) appear in square r*r
          }
        }
      }
      int maxt[3];
      maxt[0]=times[0][0];
      maxt[1]=times[1][0];
      maxt[2]=times[2][0];
      int maxindex[3]{0};
      for(int k=0;k<256;k++)
      {
        if(times[0][k]>maxt[0])
        {
          maxindex[0]=k;
          maxt[0]=times[0][k];
        }
        if(times[1][k]>maxt[1])
        {
          maxindex[1]=k;
          maxt[1]=times[1][k];
        }
        if(times[2][k]>maxt[2])
        {
          maxindex[2]=k;
          maxt[2]=times[2][k];
        }
      }
      temp[i][j][0]=maxindex[0];//let the pixels be the one that appears the most
      temp[i][j][1]=maxindex[1];
      temp[i][j][2]=maxindex[2];
    }
  }
  return new RGBImage(iwidth,iheight,temp);
}

#include "bit_field_filter.h"

#include <bits/stdc++.h>
using namespace std;
void loadcase(Image* img,string file){
  
  img->LoadImage("Image-Folder/"+file);
  cout<<"The original picture."<<endl;
  img->Display_X_Server();
  cout<<"Do you want to display in ASCII?(y/n) : ";
  string ans;
  getline(cin,ans);
  if(ans=="y")
    img->Display_ASCII();
  cout<<"Case 1 : horizontal"<<endl<<"Case 2 : mosaic"<<endl<<"Case 3 : gaussian"<<endl<<"Case 4 : laplacain"<<endl<<"Case 5 : fisheye"<<endl;
  cout<<"Enter the filter : ";
  string op;
  getline(cin,op);
  int8_t option=0;
  stringstream ss(op);
  int time=(op.begin(),op.end(),'&');
  for(int i=0;i<time;i++)
  {
    int temp;
    char a;
    ss>>temp>>a;
    switch (temp) {                 
        case 1: option = option | case_one;   break;
        case 2: option = option | case_two;   break;
        case 3: option = option | case_three; break;
        case 4: option = option | case_four;  break;
        case 5: option = option | case_five;  break;
    }
  }
  if(option & case_one)
    cout<<"Case 1 detected"<<endl;
  if(option & case_two)
    cout<<"Case 2 detected"<<endl;
  if(option & case_three)
    cout<<"Case 3 detected"<<endl;
  if(option & case_four)
    cout<<"Case 4 detected"<<endl;
  if(option & case_five)
    cout<<"Case 5 detected"<<endl;
  filter(img,option,file);
  
}
void filter(Image* img,int8_t option,string filename){
  Image* temp;
  if(option&case_one)
  {
    cout<<"Processing horizontalflip......"<<endl;
    temp=img->horizontalflip();
    delete img;
    img=temp;
    img->Display_X_Server();
    cout<<"Do you want to dump the image?(y/n) : ";
    string ans;
    getline(cin,ans);
    if(ans=="y")
    {  
      string sub=filename.substr(filename.length()-4,4);
      filename=filename.substr(0,filename.length()-4);
      filename+="_horizontal"+sub;
      img->DumpImage("DumpedImage/"+filename);
    }
  }
  if(option&case_two)
  {
    cout<<"Processing mosaic......"<<endl;
    string t;
    cout<<"Enter the block's size : ";
    getline(cin,t);
    if(t=="")
      temp=img->mosaic();
    else
    {
    int block=stoi(t);
    temp=img->mosaic(block);
    }
    delete img;
    img=temp;
    img->Display_X_Server();
    cout<<"Do you want to dump the image?(y/n) : ";
    string ans;
    getline(cin,ans);
    if(ans=="y")
    {
      string sub=filename.substr(filename.length()-4,4);
      filename=filename.substr(0,filename.length()-4);
      filename+="_mosiac"+sub;
      img->DumpImage("DumpedImage/"+filename);
    }
  }
  if(option&case_three)
  {
    cout<<"Processing Gaussian......"<<endl;
    temp=img->Gaussian();
    delete img;
    img=temp;
    img->Display_X_Server();
    cout<<"Do you want to dump the image?(y/n) : ";
    string ans;
    getline(cin,ans);
    if(ans=="y")
    {
      string sub=filename.substr(filename.length()-4,4);
      filename=filename.substr(0,filename.length()-4);
      filename+="_Gaussian"+sub;
      img->DumpImage("DumpedImage/"+filename);
    }
  }
  if(option&case_four)
  {
    cout<<"Processing laplacian......"<<endl;
    cout<<"Enter 0 or 1 to choose a type : ";
    string t;
    getline(cin,t);
    cout<<"Processing laplacian......"<<endl;
    if(t=="0")
      temp=img->laplacian(0);
    else
      temp=img->laplacian(1);
    delete img;
    img=temp;
    img->Display_X_Server();
    cout<<"Do you want to dump the image?(y/n) : ";
    string ans;
    getline(cin,ans);
    if(ans=="y")
    {
      string sub=filename.substr(filename.length()-4,4);
      filename=filename.substr(0,filename.length()-4);
      filename+="_laplacian"+sub;
      img->DumpImage("DumpedImage/"+filename);
    }
  }
  if(option&case_five)
  {
    cout<<"Processing fisheye......"<<endl;
    cout<<"Enter the effect : ";
    string t;
    getline(cin,t);
    if(t=="")
      temp=img->fisheye();
    else
    {
    float k=stof(t);
    temp=img->fisheye(k);
    }
    delete img;
    img=temp;
    img->Display_X_Server();
    cout<<"Do you want to dump the image?(y/n) : ";
    string ans;
    getline(cin,ans);
    if(ans=="y")
    {
      string sub=filename.substr(filename.length()-4,4);
      filename=filename.substr(0,filename.length()-4);
      filename+="_fisheye"+sub;
      img->DumpImage("DumpedImage/"+filename);
    }
  }
  cout<<"End of processing."<<endl;
  delete img;
}
  
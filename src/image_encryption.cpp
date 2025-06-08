#include "image_encryption.h"
#include <bits/stdc++.h>
using namespace std;
ImageEncryption::ImageEncryption():filename(""),picture(0,0,nullptr){}
ImageEncryption::ImageEncryption(string file):filename(file){
  picture.LoadImage("Image-Folder/"+filename);
  cout<<"This the originalpicture : "<<endl;
  picture.Display_X_Server();
}
vector<bool> ImageEncryption::tobits(const string& input){
  vector<bool> bits;
  bits.reserve(input.length()*8+16);
  bitset<16> l(input.length());//turn length of the input into 8bits
  for(int i=15;i>=0;i--)
    bits.push_back(l[i]);
  for(size_t i=0;i<input.length();i++)
  {
    bitset<8>b(input[i]);//turn char into 8bits
    for(int j=7;j>=0;j--)
      bits.push_back(b[j]);
  }
  return bits;
}
RGBImage* ImageEncryption::encryption(const string& input){
  vector<bool> bits=tobits(input);
  RGBImage* en=new RGBImage(picture);
  size_t capacity=en->get_height()*en->get_width()*3;
  if(bits.size()>capacity)
  {
    cout<<"The message is too long";
    delete en;
    return nullptr;
  }
  size_t k=0;
  for(int i=0;i<(en->get_height())&&k<bits.size();i++)
  {
    for(int j=0;j<(en->get_width())&&k<bits.size();j++)
    {
      
      for(int c=0;c<3&&k<bits.size();c++)
      {
        uint8_t rgbbits=static_cast<uint8_t>(en->getdata(i,j,c));
        //change LSB:
        //0xFE=1111 1110? ,& operation let lsb become 0
        // | operation write the bits into the lsb position
        rgbbits=(rgbbits & 0xFE) | bits[k];
        en->modifydata(i,j,c,static_cast<int>(rgbbits));
        k++;
      }
    }
  }
  return en;
}
string ImageEncryption::decryption(RGBImage* encrypt){
  vector<bool> ans;
  int k=0;
  int len[16];
  for(int i=0;i<(encrypt->get_height())&&k<16;i++)
  {
    for(int j=0;j<(encrypt->get_width())&&k<16;j++)
    {
      for(int c=0;c<3&&k<16;c++)
      {
        uint8_t rgbbits=static_cast<uint8_t>(encrypt->getdata(i,j,c));
        //get LSB:by doing & operation with 00000001
        len[k]=(rgbbits & 1);
        k++;
      }
    }
  }
  //decrypt lenght
  int length=0;
  for(int i=0;i<16;i++)
    length=(length<<1) | len[i];//<<left shift opertion
  int bitlength=length*8+16;
  vector <bool>bits;
  k=0;
  for(int i=0;i<(encrypt->get_height())&&k<bitlength;i++)
  {
    for(int j=0;j<(encrypt->get_width())&&k<bitlength;j++)
    {
      for(int c=0;c<3&&k<bitlength;c++)
      {
        uint8_t rgbbits=static_cast<uint8_t>(encrypt->getdata(i,j,c));
        //get LSB:by doing & operation with 00000001
        bits.push_back(rgbbits & 1);
        k++;
      }
    }
  }
  //decrypt input
  string message;
  for(int z=16;z<bitlength;z+=8)
  {
    int temp=0;
    for(int i=0;i<8;i++)
      temp=(temp<<1) | bits[z+i];
    char ch=temp;
    cout<<ch;
    message+=ch;
  }
  return message;
}













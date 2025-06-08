#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "image_encryption.h"
#include "bit_field_filter.h"
#include "image_encryption.h"
int main(){
    string process="y";
    string file;
    
    cout<<endl<<endl<<"*********************************************************"<<endl
                    <<"*********************************************************"<<endl<<endl;
    while(process!="n")
    {
    cout<<"Below are all functions : "<<endl;
    cout<<"1. Gray Image Processing."<<endl;
    cout<<"2. RGB Image Processing."<<endl;
    cout<<"3. Image Encryption."<<endl;
    cout<<"4. Image Decryption."<<endl<<endl;
    cout<<"Enter an option : ";
    string option;
    getline(cin,option);
    if(option=="1")
    {
      Data_Loader data_loader;
      vector<string> filenames;
      cout<<endl<<"***** Gray Image Processing *****"<<endl<<endl;
      data_loader.List_Directory("Image-Folder", filenames);
      for(const auto &filename : filenames){
          cout << filename << endl;
      }
      cout<<endl<<"Choose a picture for Gray Image Processing :";
      getline(cin,file);
      Image* img=new GrayImage();
      loadcase(img,file);
      cout<<endl<<"***** Gray Image Processing *****"<<endl<<endl;
    }
    if(option=="2")
    {
      Data_Loader data_loader;
      vector<string> filenames;
      cout<<endl<<"***** RGB Image Processing *****"<<endl<<endl;
      data_loader.List_Directory("Image-Folder", filenames);
      for(const auto &filename : filenames){
          cout << filename << endl;
      }
      cout<<endl<<"Choose a picture for RGB Image Processing :";
      getline(cin,file);
      Image* img=new RGBImage();
      loadcase(img,file);
      cout<<endl<<"***** RGB Image Processing *****"<<endl;
    }
    if(option=="3")
    {
      Data_Loader data_loader;
      vector<string> filenames;
      cout<<endl<<"***** Image Encryption *****"<<endl<<endl;
      data_loader.List_Directory("Image-Folder", filenames);
      for(const auto &filename : filenames){
          cout << filename << endl;
      }
      cout<<endl<<"Choose a picture for Image Encryption :";
      getline(cin,file);
      cout<<"Enter a message you want to encrypt : ";
      string message;
      getline(cin,message);
      cout<<"Start encrypting ...... "<<endl;
      ImageEncryption test(file);
      Image* img=new RGBImage;
      img=test.encryption(message);
      cout<<"Encrypted picture : "<<endl;
      img->Display_X_Server();
      file=file.substr(0,file.length()-4);
      file+="_encrypted.png";
      img->DumpImage("DumpedImage/"+file);
      cout<<"The picture has been dumped as : "<<file<<"_encrpypted.png at DumpedImage folder. "<<endl;
      delete img;
      cout<<"End of encryption."<<endl;
      cout<<endl<<"***** Image Encryption *****"<<endl<<endl;
    }
    if(option=="4")
    {
      Data_Loader data_loader;
      vector<string> filenames;
      cout<<endl<<"***** Image Decryption *****"<<endl<<endl;
      data_loader.List_Directory("DumpedImage", filenames);
      for(const auto &filename : filenames){
          cout << filename << endl;
      }
      cout<<endl<<"Choose a picture for Image Decryption :";
      getline(cin,file);
      cout<<"The encrypted picture : "<<file<<endl;
      ImageEncryption test;
      cout<<"Start decrypting ...... "<<endl;
      RGBImage*  img=new RGBImage;
      img->LoadImage("DumpedImage/"+file);
      cout<<"The hidden message : ";
      cout<<test.decryption(img)<<endl;
      delete img;
      cout<<"End of decryption."<<endl;
      cout<<endl<<"***** Image Decryption *****"<<endl<<endl;
    }
    // some photo mosaic driven code here
    // more ...*/
    

    
    
    
    cout<<"Do you want to continue?(y/n) : ";
    getline(cin,process);
    cout<<endl<<endl;
    }
    cout<<"End of program.";
    cout<<endl<<endl<<"*********************************************************"<<endl
                    <<"*********************************************************"<<endl<<endl;
    return 0;
}

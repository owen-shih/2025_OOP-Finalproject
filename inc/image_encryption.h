#ifndef _IMAGE_ENCRYPTION_H_
#define _IMAGE_ENCRYPTION_H_
#include "rgb_image.h"
class ImageEncryption{
  private:
    string filename;
    RGBImage picture;
  public:
  ImageEncryption();
  ImageEncryption(string filename);
  RGBImage* encryption(const string& input);
  vector<bool> tobits(const string& input);
  string decryption(RGBImage* encrypt);
};

#endif

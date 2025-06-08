#ifndef BIT_FIELD_FILTER_H
#define BIT_FIELD_FILTER_H
#include <bits/stdc++.h>
#include "gray_image.h"
#include "rgb_image.h"
#define case_one   0b00000001  //horizontal
#define case_two   0b00000010  //mosaic
#define case_three 0b00000100  //gaussian
#define case_four  0b00001000  //laplacian
#define case_five  0b00100000  //fisheye
void loadcase(Image* img,string file);
void filter(Image* img,int8_t option,string filename);
#endif
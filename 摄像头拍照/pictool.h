#pragma once

void drawpoint(byte* picstart, int bitcount, int linebytes, Point p, Color c);
void drawpoint(byte* picstart, int h, int w, int bitcount, Point p, Color c);
void drawrect(byte* picstart, int bitcount, int linebytes, System::Drawing::Rectangle rec, System::Drawing::Color c, int bordersize);
ASVLOFFSCREEN getimgbybmpdata(byte* data, int width, int height);
ASVLOFFSCREEN getimgbyfile(const char* picpath);
bool readBmp24(const char* path, uint8_t **imageData, int *pWidth, int *pHeight);//in,out,out,out
uint8_t ** Bmp32ToBmp24(HBITMAP hbmp32);
uint8_t * fanzhuan24(uint8_t * data, int width, int hight);
bool freeimg(ASVLOFFSCREEN offInput1);
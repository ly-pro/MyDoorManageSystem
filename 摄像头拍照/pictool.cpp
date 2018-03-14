#include "stdafx.h"


void drawpoint(byte* picstart, int bitcount, int linebytes, Point p, Color c) {
	picstart[p.Y*linebytes + p.X * bitcount] = c.B;//B
	picstart[p.Y*linebytes + p.X * bitcount + 1] = c.G;//G
	picstart[p.Y*linebytes + p.X * bitcount + 2] = c.R;//R
	if (bitcount == 4) {
		picstart[p.Y*linebytes + p.X * bitcount + 3] = c.A;//A
	}
}

void drawpoint(byte* picstart, int h, int w, int bitcount, Point p, Color c) {
	int linebytes = (w + 3) / 4 * 4 * bitcount;
	picstart[p.Y*linebytes + p.X * bitcount] = c.B;//B
	picstart[p.Y*linebytes + p.X * bitcount + 1] = c.G;//G
	picstart[p.Y*linebytes + p.X * bitcount + 2] = c.R;//R
	if (bitcount == 4) {
		picstart[p.Y*linebytes + p.X * bitcount + 3] = c.A;//A
	}
}
void drawrect(byte* picstart, int bitcount, int linebytes, System::Drawing::Rectangle rec, System::Drawing::Color c, int bordersize) {
	bordersize /= 2;
	for (int x = rec.X;x < rec.X + rec.Width;++x) {
		drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(x, rec.Y), c);//上面
		for (int b = 0;b < bordersize;++b) {
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(x, rec.Y - b), c);
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(x, rec.Y + b), c);
		}

		drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(x, rec.Y + rec.Height), c);//下面
		for (int b = 0;b < bordersize;++b) {
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(x, rec.Y + rec.Height - b), c);
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(x, rec.Y + rec.Height + b), c);
		}
	}
	for (int y = rec.Y;y < rec.Y + rec.Height;++y) {
		drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(rec.X, y), c);//左边
		for (int b = 0;b < bordersize;++b) {
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(rec.X + b, y), c);
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(rec.X - b, y), c);
		}
		drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(rec.X + rec.Width, y), c);//右边
		for (int b = 0;b < bordersize;++b) {
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(rec.X + rec.Width + b, y), c);
			drawpoint(picstart, bitcount, linebytes, System::Drawing::Point(rec.X + rec.Width - b, y), c);
		}
	}
}
ASVLOFFSCREEN getimgbybmpdata(byte* data, int width, int height) {
	ASVLOFFSCREEN offInput1 = { 0 };
	offInput1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	offInput1.ppu8Plane[0] = data;
	offInput1.i32Width = width;
	offInput1.i32Height = height;
	offInput1.pi32Pitch[0] = offInput1.i32Width * 3;
	return offInput1;
}
ASVLOFFSCREEN getimgbyfile(const char* picpath) {
	ASVLOFFSCREEN offInput1 = { 0 };
	offInput1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	offInput1.ppu8Plane[0] = nullptr;
	readBmp24(picpath, (uint8_t**)&offInput1.ppu8Plane[0], &offInput1.i32Width, &offInput1.i32Height);
	offInput1.pi32Pitch[0] = offInput1.i32Width * 3;
	return offInput1;
}
bool readBmp24(const char* path, uint8_t **imageData, int *pWidth, int *pHeight)//in,out,out,out
{
	if (path == NULL || imageData == NULL || pWidth == NULL || pHeight == NULL)
	{
		return false;
	}
	FILE *fp;
	fopen_s(&fp, path, "rb");
	if (fp == NULL)
	{
		return false;
	}
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	*pWidth = head.biWidth;
	*pHeight = head.biHeight;
	int biBitCount = head.biBitCount;
	int temp = 1706400;
	if (24 == biBitCount)
	{
		int lineByte = ((*pWidth) * biBitCount / 8 + 3) / 4 * 4;
		//*imageData = (uint8_t *)malloc(lineByte * (*pHeight));
		uint8_t * data = (uint8_t *)malloc(lineByte * (*pHeight));
		fseek(fp, 54, SEEK_SET);
		fread(data, 1, lineByte * (*pHeight), fp);
		/*for (int i = 0; i < *pHeight; i++)//将bmp上下倒置得到真实图像
		{
		for (int j = 0; j < *pWidth; j++)
		{
		int x = i * (*pWidth) * 3 + j * 3;
		int y = (((*pHeight) - 1) - i) * lineByte + j * 3;
		memcpy((*imageData) + x, data + y, 3);
		}
		}*/
		//dump(*imageData, lineByte * (*pHeight),"imageData");
		//dump(data, lineByte * (*pHeight), "data");
		*imageData = data;
		//free(data);
	}
	else if (32 == biBitCount) {
		delete *imageData;
		//*imageData = *Bmp32ToBmp24(path);
		int lineByte = ((*pWidth) * biBitCount / 8 + 3) / 4 * 4;
		uint8_t * data = (uint8_t *)malloc(lineByte * (*pHeight));
		fseek(fp, 54, SEEK_SET);
		fread(data, 1, lineByte * (*pHeight), fp);
		//dump(data, lineByte * (*pHeight), "2");
		HBITMAP bmp = CreateBitmap(*pWidth, *pHeight, 1, 32, data);
		*imageData = *Bmp32ToBmp24(bmp);
		uint8_t *tp = *imageData;
		*imageData = fanzhuan24(*imageData, *pWidth, *pHeight);
		delete tp;

		free(data);
		//dump(*imageData,temp,"3");
	}
	else {
		fclose(fp);
		printf("图片要求24位或32位深度的bmp格式\n");
		return false;
	}
	fclose(fp);
	return true;
}
uint8_t ** Bmp32ToBmp24(HBITMAP hbmp32) {
	BITMAP bmp;//获取位图信息
	GetObject(hbmp32, sizeof(BITMAP), &bmp);

	//printf("Image Bit Depth : %dnWidth : %d , Height : %d\n",
	//	bmp.bmBitsPixel, bmp.bmWidth, bmp.bmHeight);//显示位图颜色模式和图像宽高

	//计算24位图像每行的字节数
	int BytesPerLine = 3 * bmp.bmWidth;
	while (BytesPerLine % 4 != 0)
		BytesPerLine++;

	BITMAPINFOHEADER bih = { 0 };//位图信息头
	bih.biBitCount = 24;//每个像素字节大小
	bih.biCompression = BI_RGB;
	bih.biHeight = bmp.bmHeight;//高度
	bih.biPlanes = 1;
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biSizeImage = BytesPerLine * bmp.bmHeight;//图像数据大小
	bih.biWidth = bmp.bmWidth;//宽度

	BITMAPFILEHEADER bfh = { 0 };//位图文件头
	bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//到位图数据的偏移量
	bfh.bfSize = bfh.bfOffBits + bih.biSizeImage;//文件总的大小
	bfh.bfType = (WORD)0x4d42;

	byte * p = new byte[bih.biSizeImage];
	byte *pnew = new byte[bih.biSizeImage];
	byte *ppnew = pnew;
	//获取当前32位图像数据
	GetDIBits(GetDC(NULL), hbmp32, 0, bmp.bmHeight, p, (LPBITMAPINFO)&bih, DIB_RGB_COLORS);

	int lineByte = ((bmp.bmWidth) * bih.biBitCount / 8 + 3) / 4 * 4;
	static uint8_t *tp = nullptr;
	uint8_t **newimg = &tp;
	//*newimg = (uint8_t *)malloc(lineByte * (bmp.bmHeight));
	uint8_t * data = (uint8_t *)malloc(lineByte * (bmp.bmHeight));
	byte b = 0;//用于填充
	for (int i = 0; i < bmp.bmWidth * bmp.bmHeight; i++)
	{
		memcpy(pnew, &(p[i * 3]), 3);
		pnew += 3;
		if (i % bmp.bmWidth == bmp.bmWidth - 1)//填充字节
		{
			for (int k = 0; k < (BytesPerLine - bmp.bmWidth * 3); k++) {
				memcpy(pnew++, &b, sizeof(byte));
			}
		}

	}
	memcpy(data, ppnew, lineByte * (bmp.bmHeight));
	/*for (int i = 0; i < bmp.bmHeight; i++)
	{
	for (int j = 0; j < bmp.bmWidth; j++)
	{
	int x = i * (bmp.bmWidth) * 3 + j * 3;
	int y = (((bmp.bmHeight) - 1) - i) * lineByte + j * 3;
	memcpy((*newimg) + x, data + y, 3);
	}
	}*/
	//free(data);
	delete[] p;
	delete[] ppnew;
	DeleteObject(hbmp32);
	*newimg = data;
	//dump(*newimg, lineByte * (bmp.bmHeight), "1.bmp");
	return newimg;
}
uint8_t * fanzhuan24(uint8_t * data, int width, int hight) {
	int lineByte = (width * 24 / 8 + 3) / 4 * 4;
	uint8_t * imageData = nullptr;
	imageData = (uint8_t *)malloc(lineByte * hight);
	for (int i = 0; i < hight; i++)//将bmp上下倒置得到真实图像
	{
		for (int j = 0; j < width; j++)
		{
			int x = i * width * 3 + j * 3;
			int y = ((hight - 1) - i) * lineByte + j * 3;
			memcpy(imageData + x, data + y, 3);
		}
	}
	return imageData;
}
bool freeimg(ASVLOFFSCREEN offInput1) {
	free(offInput1.ppu8Plane[0]);
	return 1;
}
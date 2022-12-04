#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmpHeader.h"

#define BYTE unsigned char
#ifndef M_PI
#define M_PI 3.141592654
#endif

#define BASE 15

#define widthbytes(bits) (((bits)+31)/32*4)

void main(int argc, char** argv)
{
	FILE *fp;
	BITMAPFILEHEADER bmpHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	RGBQUAD palrgb[256];
	char input[128], output[128];
	int i, j, imageSize, size;

	unsigned char *inimg;
	unsigned char *outimg;

	strcpy(input, argv[1]);
	strcpy(output, argv[2]);
	

	if((fp = fopen(input, "rb")) == NULL){
		fprintf(stderr, "Error : Failed to open file...\n");
		exit(EXIT_FAILURE);
	}

	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	size = widthbytes(bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth);
	//if(!bmpInfoHeader.SizeImage)
	imageSize = bmpInfoHeader.biHeight * size;
		printf("%d\n\n",imageSize);

	printf("Resolution %d x %d\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);
	printf("Bit Count : %d\n", bmpInfoHeader.biBitCount);
	
	inimg = (BYTE*)malloc(sizeof(BYTE)*bmpInfoHeader.SizeImage);
	outimg = (BYTE*)malloc(sizeof(BYTE)*bmpInfoHeader.SizeImage);
	fread(inimg, sizeof(BYTE), bmpInfoHeader.SizeImage, fp);
	fclose(fp);

	int elemSize = bmpInfoHeader.biBitCount / 8;
	size = bmpInfoHeader.biWidth * elemSize;
	bmpInfoHeader.SizeImage = size * bmpInfoHeader.biHeight;

	for(i = 0; i < bmpInfoHeader.biHeight; i++){
		for(j = 0; j < size; j+=elemSize){
#if 0
			outimg[j+i*size+0] = inimg[size-j+i*size+0];
			outimg[j+i*size+1] = inimg[size-j+i*size+1];
			outimg[j+i*size+2] = inimg[size-j+i*size+2];
			
#else 
			outimg[j+i*size+0] = inimg[j+(bmpInfoHeader.biHeight-i)*size+0];
			outimg[j+i*size+1] = inimg[j+(bmpInfoHeader.biHeight-i)*size+1];
			outimg[j+i*size+2] = inimg[j+(bmpInfoHeader.biHeight-i)*size+2];
#endif
		}
	}
	bmpHeader.bfOffBits += 256*sizeof(RGBQUAD);

	if((fp = fopen(output, "wb")) == NULL){
		fprintf(stderr, "Error : Failed to open file...\n");
		exit(EXIT_FAILURE);
	}

	fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	fwrite(palrgb, sizeof(unsigned int), 256, fp);
	fwrite(outimg, sizeof(unsigned char), bmpInfoHeader.SizeImage, fp);

	free(inimg);
	free(outimg);

	fclose(fp);
}
			

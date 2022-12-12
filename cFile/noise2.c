#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <limits.h>

#include "bmpHeader.h"

#define BYTE unsigned char
typedef unsigned int u_int;
#define widthbytes(bits) (((bits)+31)/32*4)
inline unsigned char clip(int value, int min, int max);
unsigned char clip(int value, int min, int max)
{
    return(value > max? max : value < min? min : value);
}

int main(int argc, char** argv) {
	FILE* fp; 
	RGBQUAD palrgb[256];

	char input[128], output[128];
	
	int i, j, k, size; 
	float srcX, srcY;
	int index; 
	float r,g,b,gray;
	int graysize; 
	int index2;
	
	unsigned char *inimg;
	
	/* usage a.out in.bmp out.bmp */
	strcpy(input, argv[1]); 
	strcpy(output, argv[2]);
		
	if((fp=fopen(input, "rb")) == NULL) { 
		fprintf(stderr, "Error : Failed to open file...₩n"); 
		return -1;
	}

#if 1
	BITMAPFILEHEADER bmpHeader;
	fread(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
#else	
	fread(&type, sizeof(unsigned short int), 1, fp); 
	fread(&file_size, sizeof(unsigned int), 1, fp); 
	fread(&reserved1, sizeof(unsigned short int), 1, fp); 
	fread(&reserved2, sizeof(unsigned short int), 1, fp); 
	fread(&offset, sizeof(unsigned int), 1, fp);
#endif
	
#if 1
      BITMAPINFOHEADER bmpInfoHeader;
	fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp); 
#else
	fread(&header_size, sizeof(unsigned int), 1, fp); 
	fread(&width, sizeof(int), 1, fp);
	fread(&height, sizeof(int), 1, fp);	
	fread(&planes, sizeof(unsigned short int), 1, fp); 
	fread(&bmpInfoHeader.biBitCount, sizeof(unsigned short int), 1, fp); 
	fread(&compression, sizeof(unsigned int), 1, fp); 
	fread(&bmpInfoHeader.SizeImage, sizeof(unsigned int), 1, fp); 
	fread(&hresolution, sizeof(int), 1, fp); 
	fread(&vresolution, sizeof(int), 1, fp); 
	fread(&ncolors, sizeof(unsigned int), 1, fp); 
	fread(&importantcolors, sizeof(unsigned int), 1, fp);
#endif

	size=widthbytes(bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth); 
	graysize = widthbytes(8 *  bmpInfoHeader.biWidth);
	
	if(!bmpInfoHeader.SizeImage) 
		bmpInfoHeader.SizeImage = bmpInfoHeader.biHeight*size;
	
	inimg=(BYTE*)malloc(sizeof(BYTE)*bmpInfoHeader.SizeImage); 
	outimg=(BYTE*)malloc(sizeof(BYTE)*bmpInfoHeader.SizeImage); 
	fread(inimg, sizeof(BYTE), bmpInfoHeader.SizeImage, fp); 
	
	fclose(fp);
	srand((u_int)time(NULL));

    
    int elemSize = bmpInfoHeader.biBitCount / 8;
	int cnt = atoi(argv[1]);
    for(i=0; i<cnt; i++) { 
            int pos = rand() % (bmpInfoHeader.biWidth * bmpInfoHeader.biHeight);
            int value = rand() & 0b11111111;
			for(k=0; k<elemSize; k++) {
                int tmp = inimg[pos*elemSize+k] + value; 
			
    			inimg[pos*elemSize+k]= clip(k, 0, 255);
            }
	 }	   
	 
	//size=widthbytes(bmpInfoHeader.biBitCount*bmpInfoHeader.biWidth); 
	//bmpInfoHeader.SizeImage=bmpInfoHeader.biHeight*size; 
	//offset+=256*sizeof(RGBQUAD);
	
	if((fp=fopen(output, "wb"))==NULL) { 
		fprintf(stderr, "Error : Failed to open file...₩n"); 
		return -1;
	}

#if 1 
	fwrite(&bmpHeader, sizeof(BITMAPFILEHEADER), 1, fp);
#else	
	fwrite(&type, sizeof(unsigned short int), 1, fp); 
	fwrite(&file_size, sizeof(unsigned int), 1, fp); 
	fwrite(&reserved1, sizeof(unsigned short int), 1, fp); 
	fwrite(&reserved2, sizeof(unsigned short int), 1, fp); 
	fwrite(&offset, sizeof(unsigned int), 1, fp); 
#endif
	
#if 1 
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp); 
#else
	fwrite(&header_size, sizeof(unsigned int), 1, fp); 
	fwrite(&width, sizeof(int), 1, fp);
	fwrite(&height, sizeof(int), 1, fp);
	fwrite(&planes, sizeof(unsigned short int), 1, fp); 
	fwrite(&bmpInfoHeader.biBitCount, sizeof(unsigned short int), 1, fp);		
	fwrite(&compression, sizeof(unsigned int), 1, fp); 
	fwrite(&bmpInfoHeader.SizeImage, sizeof(unsigned int), 1, fp); 
	fwrite(&hresolution, sizeof(int), 1, fp); 
	fwrite(&vresolution, sizeof(int), 1, fp); 
	fwrite(&ncolors, sizeof(unsigned int), 1, fp); 
	fwrite(&importantcolors, sizeof(unsigned int), 1, fp);
#endif

	//fwrite(palrgb, sizeof(unsigned int), 256, fp); 
	
	fwrite(inimg, sizeof(unsigned char), bmpInfoHeader.SizeImage, fp);
	
	free(inimg); 
	free(inimg);
	
	fclose(fp); 
	
	return 0;
}

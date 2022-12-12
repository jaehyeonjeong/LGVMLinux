#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"  //숙제 조건중 bmpHeader.h 헤더만 사용하기위해 포함시킴 

#define widthbytes(bits)  (((bits)+31)/32*4) //넓이를 4의 배수로 맞춰주기 위한 패딩

typedef unsigned char BYTE; //타입 재정의를 사용해 BTYE변수를 unsigned char로 재정의		

int main(int argc, char** argv)
{
	FILE *fp;		//불러오는 파일의 변수
	BITMAPFILEHEADER bmpFileHeader; //파일 헤더 구조체 변수 정의
	BITMAPINFOHEADER bmpInfoHeader;	//파일 정보 구조체 변수 정의
	RGBQUAD palrgb[256];			//팔레트 구조체 변수 정의, 구조체 인자 마다 [0~255] 배열 선언 
	char input[128];				//

	int r, g, b;
	unsigned int imagesize;   

	int i, j, size, index;
	BYTE *inimg;
 
	strcpy(input, argv[1]);
 
	if((fp = fopen(input, "rb")) == NULL) {
		fprintf(stderr, "Error : Failed to open file...\n");
		exit(EXIT_FAILURE);
	}

	fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);

	fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);

	size = widthbytes(bmpInfoHeader.biBitCount * bmpInfoHeader.biWidth);

	imagesize = bmpInfoHeader.SizeImage;
	if(!imagesize) imagesize = bmpInfoHeader.biHeight * size;
	inimg = (BYTE*)malloc(sizeof(BYTE)*imagesize);
	fread(inimg, sizeof(BYTE), imagesize, fp);
 
	for(i = 0; i < bmpInfoHeader.biHeight; i++) {
		index = (bmpInfoHeader.biHeight-i-1) * size; 
		for(j = 0 ; j < bmpInfoHeader.biWidth; j++) { 
			r = (int)inimg[index+3*j+2];
			g = (int)inimg[index+3*j+1];
			b = (int)inimg[index+3*j+0];
			printf("(%d, %d, %d)\n", b, g, r);
		};
	};


	free(inimg);
	fclose(fp);

    return 0;
}

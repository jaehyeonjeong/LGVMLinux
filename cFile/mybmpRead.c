#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"  //숙제 조건중 bmpHeader.h 헤더만 사용하기위해 포함시킴 

typedef unsigned char BYTE; //타입 재정의를 사용해 BTYE변수를 unsigned char로 재정의		
typedef unsigned int u_int; //unsigned int 재정의
int main(int argc, char** argv)
{
	FILE *fp;		//불러오는 파일의 변수
	BITMAPFILEHEADER bmpFileHeader; //파일 헤더 구조체 변수 정의
	BITMAPINFOHEADER bmpInfoHeader;	//파일 정보 구조체 변수 정의
	RGBQUAD palrgb[256];			//팔레트 구조체 변수 정의, 구조체 인자 마다 [0~255] 배열 선언 

	int r, g, b;	//픽셀 r, g, b원소 정의
	u_int imagesize;   //이미지 크기 변수 선언

	int i, j, size, index;		//for문 변수, size, index변수 선언
	BYTE *inimg;			//입력 이미지 변수 선언
 
 	/*비트맵 실행*/
	if(argc != 2){			//실행 개수가 2가 아닌경우
		fprintf(stderr, "usage %s input.bmp\n", argv[0]); //실행 파일 에러
		return -1;
	}


	if((fp = fopen(argv[1], "rb")) == NULL) {	//입력 파일이 없는 경우
		fprintf(stderr, "Error : Failed to open file...\n");	//에러 발생
		return -1;
	}

	fread(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);	//비트맵 파일 구조체 읽기

	fread(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);	//비트맵 정보 구조체 읽기

	int elemSize = bmpInfoHeader.biBitCount / 8;		//픽샐당 가지고 있는 3원소(rgb)
	size = bmpInfoHeader.biWidth * elemSize;			//3원소를 포함한 이미지의 너비

	imagesize = bmpInfoHeader.SizeImage;		//입력된 비트맵의 이미지 크기
	if(!imagesize) imagesize = bmpInfoHeader.biHeight * size;	//만일 이미지의 크기가 없으면 크기 정의
	inimg = (BYTE*)malloc(sizeof(BYTE)*imagesize);	//입력된 이미지 동적 할당
	fread(inimg, sizeof(BYTE), imagesize, fp);	//입력된 이미지 읽기
 
	for(i = 0; i < bmpInfoHeader.biHeight; i++) {	//비트맵의 높이 
		index = (bmpInfoHeader.biHeight-i-1) * size; //비트맵이 반전되어 있기 때문에 하단에 인덱스 위치변수를 취함
		for(j = 0 ; j < bmpInfoHeader.biWidth; j++) { //비트맵의 너비
			r = (int)inimg[index+elemSize*j+2];	//위치된 픽셀 비트맵 너비 안의 R원소 정의
			g = (int)inimg[index+elemSize*j+1]; //위치된 픽셀 비트맵 너비 안의 G원소 정의
			b = (int)inimg[index+elemSize*j+0];	//위치된 픽셀 비트맵 너비 안의 B원소 정의
			printf("(%d, %d, %d)\n", b, g, r);	//비트맵 픽셀당 BGR원소 출력
		}
	}


	free(inimg); //입력 이미지 동적 할당 해제
	fclose(fp);	//파일 닫기

    return 0;
}

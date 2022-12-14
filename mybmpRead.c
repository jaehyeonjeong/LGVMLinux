#include <stdio.h>		//표준 입출력 함수를 위한 헤더 파일
#include <stdlib.h>
#include <string.h>
#include "bmpHeader.h"  //숙제 조건중 bmpHeader.h 헤더만 사용하기위해 포함시킴 

typedef unsigned char BYTE; //타입 재정의를 사용해 BTYE변수를 unsigned char로 재정의		
typedef unsigned int u_int; //unsigned int 재정의
int main(int argc, char** argv)
{
	FILE *fp, *copyfp;		//불러오는 파일의 변수, 복사된 파일
	BITMAPFILEHEADER bmpFileHeader; //파일 헤더 구조체 변수 정의
	BITMAPINFOHEADER bmpInfoHeader;	//파일 정보 구조체 변수 정의
	RGBQUAD *palrgb;			//팔레트 구조체 변수 정의, 구조체 인자 마다 [0~255] 배열 선언, 이후 포인터로 변경

	int r, g, b;	//픽셀 r, g, b원소 정의
	u_int imagesize;   //이미지 크기 변수 선언

	int i, j, size, index;		//for문 변수, size, index변수 선언
	BYTE *inimg;			//입력 이미지 변수 선언
 
 	/*비트맵 실행*/
	if(argc != 3){			//실행 개수가 2가 아닌경우
		fprintf(stderr, "usage %s input.bmp\n", *(argv+0)); //실행 파일 에러
		return -1;
	}

	/*복사의 원본이 되는 파일을 읽기 모드로 연다.*/
	if((fp = fopen(*(argv+1), "rb")) == NULL) {	//입력 파일이 없는 경우
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
	palrgb = (RGBQUAD*)malloc(sizeof(RGBQUAD)*256);	//팔레트 256개 추가, 포인터 변수로 선언하여 동적 할당
	
	memset(palrgb, 0, sizeof(RGBQUAD)*256);			//팔레트 할당 정보 초기화
	fread(inimg, sizeof(BYTE), imagesize, fp);	//입력된 이미지 읽기
    fclose(fp); 
#if 0
	for(i = 0; i < bmpInfoHeader.biHeight; i++) {	//비트맵의 높이 
		for(j = 0 ; j < bmpInfoHeader.biWidth; j++) { //비트맵의 너비
			r = (int)inimg[index+elemSize*j+2];	//위치된 픽셀 비트맵 너비 안의 R원소 정의
			g = (int)inimg[index+elemSize*j+1]; //위치된 픽셀 비트맵 너비 안의 G원소 정의
			b = (int)inimg[index+elemSize*j+0];	//위치된 픽셀 비트맵 너비 안의 B원소 정의
			printf("(%d, %d, %d)\n", b, g, r);	//비트맵 픽셀당 BGR원소 출력
		}
	}
#else
	for(i = 0; i < bmpInfoHeader.biWidth * bmpInfoHeader.biHeight; i++){ //2중 for문을 1중 for문으로 변경
		r = (int)inimg[elemSize*i+2];		//위치된 픽셀 비트맵 너비 안의 R원소 정의
		g = (int)inimg[elemSize*i+1];		//위치된 픽셀 비트맵 너비 안의 G원소 정의
		b = (int)inimg[elemSize*i+0];		//위치된 픽셀 비트맵 너비 안의 B원소 정의
		printf("(%d, %d, %d)\n", b, g, r);	//비트맵 픽셀당 BGR원소 출력
	}
#endif

	/*복사할 결과 파일을 쓰기 모드(새로운 파일 생성 | 기존에 파일 내용 지움)로 연다.*/
	if((copyfp = fopen(*(argv+2), "wb")) == NULL){
		fprintf(stderr, "Error Failed write File..");
		return -1;
	}
	/*원본 파일에서 파일 내용을 읽어서 복사할 파일에 쓴다*/
#if 1
	/*RGB 팔렛트 추가*/	
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD) * 256; //팔레트 256만큼 추가
	bmpFileHeader.bfSize = bmpFileHeader.bfOffBits + bmpInfoHeader.SizeImage;	//버퍼 크기는 RGBQUAD만 추가한 이미지 크기
#endif
	fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, copyfp); //복사파일에 BITMAPFILEHEADER 구조체 추가
	fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, copyfp); //복사파일에 BITMAPINFOHEADER 구조체 추가
	fwrite(palrgb, sizeof(RGBQUAD), 256, copyfp);				 //복사파일에 RGBQUAD 256만큼 구조체 추가 
	fwrite(inimg, sizeof(BYTE), imagesize, copyfp);				//복사파일을 이미지 사이즈 호출
	fclose(copyfp);		//copyfp 파일 닫기
	free(inimg);	//입력 이미지 동적 할당 해제
	free(palrgb);	//팔레트 정보 동적 할당 해제
	
    return 0;
}

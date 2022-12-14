#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat image = imread("../Images/lena.bmp", IMREAD_COLOR);
	CV_Assert(image.data);

	Mat bgr[3];
	split(image, bgr);

	Mat bgr_arr[] = {bgr[0], bgr[1], bgr[2]};
	Mat mer_bgr;
	merge(bgr_arr, 3, mer_bgr); 
	imshow("image", image);
	imshow("blue 채널", bgr[0]);
	imshow("green 채널", bgr[1]);
	imshow("red 채널", bgr[2]);
	imshow("mer 패널", mer_bgr);
	waitKey(0);


	return 0;
}

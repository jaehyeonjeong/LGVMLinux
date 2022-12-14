#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat image(200, 300, CV_8U, Scalar(255));
	namedWindow("키보드 이벤트", WINDOW_AUTOSIZE);
	imshow("키보드 이벤트", image);

	while(1)
	{
		int key = waitKeyEx(100);
	//	cout << hex << key << endl;
		if(key == 27) break;

		switch (key)
		{
			case 'a' : cout << "a키 입력" << endl; break;
			case 'b' : cout << "b키 입력" << endl; break;
			case 0x41 : cout << "A키 입력" << endl; break;
			case 66: cout << "B키 입력" << endl; break;

			case 0xff51: cout << "왼쪽 화살표 키 입력" << endl; break;
			case 0xff52: cout << "윗쪽 화살표 키 입력" << endl; break;
			case 0xff53: cout << "오른쪽 화살표 키 입력" << endl; break;
			case 0xff54: cout << "아래쪽 화살표 키 입력" << endl; break;
		}
	}
	return 0;
}

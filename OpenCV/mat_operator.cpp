#include <opencv2/opencv.hpp>
 using namespace cv;
 using namespace std;
 
 int main()
 {   
    float data[] = {
         1, 0, 2,
         -3, 4, 6,
         -1, -2, 3
     };      
     Mat m1(3, 3, CV_32F, data);
     Mat m2(Matx13f(6, 30, 8));
     Mat m2_t = m2.t();
     
     Mat m1_inv = m1.inv(DECOMP_LU);
     Mat x = m1_inv * m2_t;
     
     cout << "[m1] = " << endl << m1 << endl;
     cout << "[m1_inv(역행렬)] =" << endl << m1_inv << endl << endl;
     cout << "[m2(전치행렬)] = " << endl << m2_t << endl;
    
     cout << "연립방정식의 해 x1, x2, x3 =" << x.t() << endl << endl;
	
	 Matx<uchar, 2, 2> m3;
	 
	 m3(0, 0) = -50;
	 m3(0, 1) = 300;
	 m3(1, 0) = saturate_cast<uchar>(-50);
	 m3(1, 1) = saturate_cast<uchar>(300);

	 cout << "[m3] = " << endl << m3 << endl;

	return 0;
 }   


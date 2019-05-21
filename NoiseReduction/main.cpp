// Image processing, Noise reduction
// Namhyeon Kim, 2019. 05. 20.

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
	Mat original = imread("original.png", 0);
	Mat gaussian10 = imread("Gaussian_0.10.png", 0);
	Mat gaussian20 = imread("Gaussian_0.20.png", 0);
	Mat result;

	original.convertTo(original, CV_8UC1);

	fastNlMeansDenoising(gaussian10, gaussian10, 30, 7, 21);
	fastNlMeansDenoising(gaussian20, gaussian20, 30, 7, 21);
	//GaussianBlur(gaussian, result, Size(5, 5), 1, 0, BORDER_REFLECT);

	imshow("Original", original);
	imshow("Gaussian", gaussian10);
	imshow("Gaussian2", gaussian20);
	//imshow("Result", result);


	waitKey();
	
	return 0;
}

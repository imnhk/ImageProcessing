// Image processing, Noise reduction
// Namhyeon Kim, 2019. 05. 22.

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
	Mat original = imread("original.png", 0);
	Mat img[5];
	Mat result[5];

	img[0] = imread("Gaussian_0.10.png", 0);
	img[1] = imread("pepper_0.05.png", 0);
	img[2] = imread("salt_0.05.png", 0);
	img[3] = imread("salt_pepper_0.05.png", 0);
	img[4] = imread("uniform_0.10.png", 0);

	imshow("Original", original);

	imshow("Gaussian_Before", img[0]);
	imshow("Pepper_Before", img[1]);
	imshow("Salt_Before", img[2]);
	imshow("Salt_Pepper_Before", img[3]);
	imshow("Uniform_Before", img[4]);

	// Gaussian, Uniform noise는 Non-local Means Denoising algorithm 으로 잘 제거된다.
	fastNlMeansDenoising(img[0], img[0], 15, 5, 21); 
	fastNlMeansDenoising(img[4], img[4], 15, 5, 21);

	// Salt, Pepper noise는 medianBlur 로 잘 제거된다.
	medianBlur(img[1], img[1], 3);
	medianBlur(img[2], img[2], 3);
	medianBlur(img[3], img[3], 3);

	imshow("Gaussian_After", img[0]);
	imshow("Pepper_After", img[1]);
	imshow("Salt_After", img[2]);
	imshow("Salt_Pepper_After", img[3]);
	imshow("Uniform_After", img[4]);

	waitKey();
	
	return 0;
}
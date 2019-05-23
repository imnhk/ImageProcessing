// Image processing, Noise reduction
// Namhyeon Kim, 2019. 05. 22.

#include <opencv2/opencv.hpp>

using namespace cv;

double getPSNR(const Mat& I1, const Mat& I2);

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

	// Gaussian, Uniform noise는 Non-local Means Denoising algorithm 으로 잘 제거된다.
	fastNlMeansDenoising(img[0], result[0], 15, 5, 21);
	fastNlMeansDenoising(img[4], result[4], 15, 5, 21);

	// Salt, Pepper noise는 medianBlur 로 잘 제거된다.
	medianBlur(img[1], result[1], 3);
	medianBlur(img[2], result[2], 3);
	medianBlur(img[3], result[3], 3);

	imshow("Gaussian_Before", img[0]);
	imshow("Pepper_Before", img[1]);
	imshow("Salt_Before", img[2]);
	imshow("Salt_Pepper_Before", img[3]);
	imshow("Uniform_Before", img[4]);

	imshow("Gaussian_After", result[0]);
	imshow("Pepper_After", result[1]);
	imshow("Salt_After", result[2]);
	imshow("Salt_Pepper_After", result[3]);
	imshow("Uniform_After", result[4]);

	printf("----- PSNR -----\n");
	for (int i = 0; i < 5; i++) {
		printf("Image %d: %lf\n", i+1, getPSNR(img[i], original));
	}

	waitKey();
	
	return 0;
}

double getPSNR(const Mat& mat1, const Mat& mat2)
{
	Mat diff;
	absdiff(mat1, mat2, diff);   
	diff.convertTo(diff, CV_32F);
	diff = diff.mul(diff);       

	Scalar s = sum(diff);

	double sse = s.val[0] + s.val[1] + s.val[2];

	double mse = sse / (double)(mat1.channels() * mat1.total());
	double psnr = 10.0 * log10((255 * 255) / mse);
	return psnr;
}
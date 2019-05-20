// Image processing, histogram equalization
// Namhyeon Kim, 2019. 04. 12

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
	Mat image = imread("image2.jpg", 0);
	image.convertTo(image, CV_8UC1);
	int pixelCounts = image.cols*image.rows;

	Mat newImage;
	newImage.create(image.size(), CV_8UC1);

	// Initialize histogram
	int histogram[256];
	for (int i = 0; i < 256; i++) {
		histogram[i] = 0;
	}
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			histogram[image.at<uchar>(i, j)]++;
		}
	}

	// Accumulate histogram
	for (int i = 1; i < 256; i++) {
		histogram[i] += histogram[i-1];
	}

	// Histogram equalization
	int intensity;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			// Intensity transformation
			intensity = image.at<uchar>(i, j);
			newImage.at<uchar>(i, j) = intensity * histogram[intensity] / pixelCounts;
		}
	}

	imshow("Result", newImage);
	waitKey();

	return 0;
}

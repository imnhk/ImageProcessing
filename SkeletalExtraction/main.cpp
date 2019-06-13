// Image processing, Skeletal extraction
// Namhyeon Kim, 2019. 06. 13.

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int, char**)
{
	const int ARR_LEN = 10;

	Mat srcImage = imread("sk3.png", 0);
	Mat resImage = Mat(srcImage.size(), CV_8UC1);

	Mat A[ARR_LEN];
	Mat S[ARR_LEN];
	Mat T[ARR_LEN];

	Mat kernel = getStructuringElement(MORPH_CROSS, Size(3, 3));

	double max;

	A[0] = 255 - srcImage;
	resImage = 0;

	for (int i = 0; i < ARR_LEN - 1; i++) {

		// Opening
		morphologyEx(A[i], T[i], MORPH_OPEN, kernel);

		// S[i] = A[i] - T[i]
		S[i] = ~T[i] & A[i];

		erode(A[i], A[i+1], kernel);

		// Result = S[0]+S[1]+S[2]+ ...
		resImage = resImage | S[i];

		// S[i] 가 전부 검은색일 때 멈춘다
		minMaxLoc(S[i], NULL, &max);
		if (max == 0) {
			imshow("Result", resImage);
			break;
		}
	}

	waitKey();
	return 0;
}

/*마지막 과제는 손글씨 입력 파일(sk?.png)파일을 입력 받아 획의 두께를 최소한으로 바꾸는 과정(Skeleton extraction)을 구현하는 것입니다. (결과 그림을 참고하십시오.)
Skeletonization 과정은 다음과 같습니다.

0. 먼저 영상을 역상으로 바꿉니다.

1. 입력영상을 A0, A0를 opening한 영상을 T0라고 할 때 S0 = A0-T0 라하면 (여기서 '-'는 집합 연산) S0은 Opening에 의해 사라진 가는 선이 됩니다.

2. 다음 두꺼운 선을 가늘게 하기 위해 A를 erode 하면 A1을 얻으면, A1의 경우 S0에 나타나는 선은 없어지고, 약간 두꺼운 선이 가늘어집니다.

3. A1을 opening 한 영상을 T1로 하고, S1=A1-T1합니다.

4. 2-3 과정을 반복하여 S0, S1, S2, S3... 을 계산합니다.

5. 과정은 Sn이 전부 검은색일때 멈추면 됩니다.

6. 결과 영상은 S0+S1+S2+S3... 으로 나타납니다. ('+' 연산 역시 집합 연산입니다.)

7. 결과를 출력합니다.

Source code만 제출합니다.

(Hint. '-' operation은 bitwise_and(~T, A...) 의 형식을 사용하시고, '+' 는 bitwise_or나 | operator를 이용하시면 쉽습니다.
또한 영상의 모듬 픽셀이 0인지 알기 위해서는 최소값, 최대값을 찾는 minMaxLoc 함수를 사용하시면 편리합니다. 결과 그림은 cross se를 사용한 것입니다.)*/
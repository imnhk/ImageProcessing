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

		// S[i] �� ���� �������� �� �����
		minMaxLoc(S[i], NULL, &max);
		if (max == 0) {
			imshow("Result", resImage);
			break;
		}
	}

	waitKey();
	return 0;
}

/*������ ������ �ձ۾� �Է� ����(sk?.png)������ �Է� �޾� ȹ�� �β��� �ּ������� �ٲٴ� ����(Skeleton extraction)�� �����ϴ� ���Դϴ�. (��� �׸��� �����Ͻʽÿ�.)
Skeletonization ������ ������ �����ϴ�.

0. ���� ������ �������� �ٲߴϴ�.

1. �Է¿����� A0, A0�� opening�� ������ T0��� �� �� S0 = A0-T0 ���ϸ� (���⼭ '-'�� ���� ����) S0�� Opening�� ���� ����� ���� ���� �˴ϴ�.

2. ���� �β��� ���� ���ð� �ϱ� ���� A�� erode �ϸ� A1�� ������, A1�� ��� S0�� ��Ÿ���� ���� ��������, �ణ �β��� ���� ���þ����ϴ�.

3. A1�� opening �� ������ T1�� �ϰ�, S1=A1-T1�մϴ�.

4. 2-3 ������ �ݺ��Ͽ� S0, S1, S2, S3... �� ����մϴ�.

5. ������ Sn�� ���� �������϶� ���߸� �˴ϴ�.

6. ��� ������ S0+S1+S2+S3... ���� ��Ÿ���ϴ�. ('+' ���� ���� ���� �����Դϴ�.)

7. ����� ����մϴ�.

Source code�� �����մϴ�.

(Hint. '-' operation�� bitwise_and(~T, A...) �� ������ ����Ͻð�, '+' �� bitwise_or�� | operator�� �̿��Ͻø� �����ϴ�.
���� ������ ��� �ȼ��� 0���� �˱� ���ؼ��� �ּҰ�, �ִ밪�� ã�� minMaxLoc �Լ��� ����Ͻø� ���մϴ�. ��� �׸��� cross se�� ����� ���Դϴ�.)*/
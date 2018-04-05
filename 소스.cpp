#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define PI	3.14159265359

using namespace std;

int main(void)
{
	int N;	//시행횟수
	int dimension;		//차원
	double * dimensions;	//차원의 구성 요소(x축,y축,z축 ...)
	double volume = 1.0;	//n차원 육면체의 부피
	double radius;
	double HyperSphere_Volume;	//n차원 구의 부피
	double MonteCarlo_HyperSphere_Volume;	//MonteCarlo 방식으로 구한 n차원 구의 부피
	double MeasuringEfficiency;	//오차율
	double HyperSphere_constant[10] = {
		0,
		2.0,
		PI,
		(double)4 / 3 * PI,
		(double)1 / 2 * pow(PI,2),
		(double)8 / 15 * pow(PI,2),
		(double)1 / 6 * pow(PI,3),
		(double)16 / 105 * pow(PI,3),
		(double)1 / 24 * pow(PI,4),
		(double)32 / 945 * pow(PI,4)
	};

	double HyperSphere_Equation = 0.0;
	int Ns = 0;	//성공 횟수

	srand((unsigned)time(NULL));

	cout << "초 구(HyperSphere)의 부피(Volume)구하기" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << "구하고자 하는 구의 차원을 입력하세요 : ";
	cin >> dimension;
	cout << "시행횟수를 입력하세요 : ";
	cin >> N;
	cout << "초 구(HyperSphere)의 반지름 입력 : ";
	cin >> radius;

	//n차원 구성요소 동적할당
	dimensions = new double[dimension];

	for (int i = 0; i < dimension; i++)
		volume *= (2 * radius);	//n차원 정육면체의 부피

	for (long i = 0; i < N; i++) {

		for (int j = 0; j < dimension; j++) {
			dimensions[j] = 2 * radius * (double)rand() / (double)RAND_MAX; // 0 ~ 2R
			//cout << dimensions[j] << endl;
		}

		//n차원 구의 방정식
		HyperSphere_Equation = 0.0;
		for (int k = 0; k < dimension; k++)
			HyperSphere_Equation += pow(dimensions[k] - radius, 2);

		HyperSphere_Equation /= pow(radius, 2);
		//cout << HyperSphere_Equation << endl;
		if (HyperSphere_Equation < 1)
			Ns++;

		//cout << (x - a / 2) * (x - a / 2) / (a / 2 * a / 2) +
		//	(y - b / 2) * (y - b / 2) / (b / 2 * b / 2) +
		//	(z - c / 2) * (z - c / 2) / (c / 2 * c / 2) << " " << endl;
	}

	MonteCarlo_HyperSphere_Volume = (double)Ns / (double)N * volume;	//MonteCarlo 방식 부피
	HyperSphere_Volume = HyperSphere_constant[dimension] * pow(radius,dimension);	//실제 타원체 부피
	MeasuringEfficiency = abs(HyperSphere_Volume - MonteCarlo_HyperSphere_Volume) / HyperSphere_Volume * 100;	//오차율

	cout << fixed;
	cout << setprecision(5);

	cout << N << "번 시행" << endl;
	//cout << Ns << " " << volume << endl;
	cout << "MonteCarlo방식으로 구한 " << dimension << "차원 구의 부피 : " << MonteCarlo_HyperSphere_Volume << endl;
	cout << "실제 " << dimension << "차원 구의 부피:" << HyperSphere_Volume << endl;
	cout << "실제 " << dimension << "차원 구의 부피에 대한 오차율 : " << MeasuringEfficiency << "%" << endl;

	cout << endl;

	return 0;
}
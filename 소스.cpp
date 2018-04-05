#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define PI	3.14159265359

using namespace std;

int main(void)
{
	int N;	//����Ƚ��
	int dimension;		//����
	double * dimensions;	//������ ���� ���(x��,y��,z�� ...)
	double volume = 1.0;	//n���� ����ü�� ����
	double radius;
	double HyperSphere_Volume;	//n���� ���� ����
	double MonteCarlo_HyperSphere_Volume;	//MonteCarlo ������� ���� n���� ���� ����
	double MeasuringEfficiency;	//������
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
	int Ns = 0;	//���� Ƚ��

	srand((unsigned)time(NULL));

	cout << "�� ��(HyperSphere)�� ����(Volume)���ϱ�" << endl;
	cout << "-----------------------------------------------------------" << endl;
	cout << "���ϰ��� �ϴ� ���� ������ �Է��ϼ��� : ";
	cin >> dimension;
	cout << "����Ƚ���� �Է��ϼ��� : ";
	cin >> N;
	cout << "�� ��(HyperSphere)�� ������ �Է� : ";
	cin >> radius;

	//n���� ������� �����Ҵ�
	dimensions = new double[dimension];

	for (int i = 0; i < dimension; i++)
		volume *= (2 * radius);	//n���� ������ü�� ����

	for (long i = 0; i < N; i++) {

		for (int j = 0; j < dimension; j++) {
			dimensions[j] = 2 * radius * (double)rand() / (double)RAND_MAX; // 0 ~ 2R
			//cout << dimensions[j] << endl;
		}

		//n���� ���� ������
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

	MonteCarlo_HyperSphere_Volume = (double)Ns / (double)N * volume;	//MonteCarlo ��� ����
	HyperSphere_Volume = HyperSphere_constant[dimension] * pow(radius,dimension);	//���� Ÿ��ü ����
	MeasuringEfficiency = abs(HyperSphere_Volume - MonteCarlo_HyperSphere_Volume) / HyperSphere_Volume * 100;	//������

	cout << fixed;
	cout << setprecision(5);

	cout << N << "�� ����" << endl;
	//cout << Ns << " " << volume << endl;
	cout << "MonteCarlo������� ���� " << dimension << "���� ���� ���� : " << MonteCarlo_HyperSphere_Volume << endl;
	cout << "���� " << dimension << "���� ���� ����:" << HyperSphere_Volume << endl;
	cout << "���� " << dimension << "���� ���� ���ǿ� ���� ������ : " << MeasuringEfficiency << "%" << endl;

	cout << endl;

	return 0;
}
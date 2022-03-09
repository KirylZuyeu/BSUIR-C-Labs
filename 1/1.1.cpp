#include <iostream>
using namespace std;
void main()
{
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите alpha " << endl;
	double alpha, z1, z2;
	cin >> alpha;
	z1 = cos(alpha) + cos(2 * alpha) + cos(6 * alpha) + cos(7 * alpha);
	z2 = 4 * cos(alpha / 2) * cos((5. / 2) * alpha) * cos(4 * alpha);
	cout << "z1 = " << z1 << endl;
	cout << "z2 = " << z2 << endl;
	system("pause");
}

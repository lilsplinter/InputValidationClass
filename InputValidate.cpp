#include <iostream>
#include "clsInputValidate.h"

using namespace std;
int main()
{
	int Age = clsInputValidate::ReadIntNumberBetween("Enter your age (18-65): ", 18, 65);
	cout << "Age accepted: " << Age << endl;
	double Amount = clsInputValidate::ReadDblNumberBetween("Enter an amount (0-1000): ", 0, 1000);
	cout << "Amount accepted: " << Amount << endl;
	cout << boolalpha;
	cout << "Is 29/2/2024 a valid date? " << clsInputValidate::IsValidDate(29, 2, 2024) << endl;
	cout << "Is 31/4/2025 a valid date? " << clsInputValidate::IsValidDate(31, 4, 2025) << endl;
	clsDate From(1, 1, 2025);
	clsDate To(31, 12, 2025);
	clsDate Date(15, 6, 2025);
	cout << "Is 15/6/2025 between 1/1/2025 and 31/12/2025? " << clsInputValidate::IsDateBetween(Date, From, To) << endl;
	return 0;
}

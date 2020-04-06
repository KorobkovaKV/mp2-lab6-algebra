#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	string expression;

	double res;

	cout << "Введите арифметическое выражение: ";
	cin >> expression;
	TPostfix postfix(expression);
	cout << "Вы ввели aрифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	res = postfix.Calculate();
	cout << res << endl;

	return 0;
}
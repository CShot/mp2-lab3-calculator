#include <calculator.h>
int main()
{
	int a = 0;
	do {
		int result = 0;
		char str_1[Max_Size_Str];
		char str[Max_Size_Str] = " ";
		int ch;
		int i = 0;
		setlocale(LC_ALL, "RUS");
		system("cls");
		cout << "������� ������: ";
		cin >> str_1;
		ch = foolproof(str_1);
		if (ch == 1)
		{
			cout << "����������� ���������" << endl;
			goto C2;
		}
		polish_notation(str_1, str);
		cout << str << endl;
		result=calculator(str);
		cout << "���������: " << result << endl;
	C2:
		cout << "������ ���������?" << endl;
		cout << "1.��" << endl;
		cout << "2.���" << endl;
		cin >> a;
		cout << endl;
	} while (a != 2);
  return 0;
}
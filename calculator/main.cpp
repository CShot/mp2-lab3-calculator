#include"TStack.h"
#include<iostream>
#include<string.h>
#include<cstring>
#include<ctype.h>
#include<locale.h>

using namespace std;

const int Max_Size_Str = 50;

int priority(char str_s);
int polish_notation(char , char );



int priority(char str_s)
{
	if (str_s == '(')
	{
		return 0;
	}
	if (str_s == ')')
	{
		return 1;
	}
	if (str_s == '+')
	{
		return 2;
	}
	if (str_s == '-')
	{
		return 2;
	}
	if (str_s == '*')
	{
		return 3;
	}
	if (str_s == '(')
	{
		return 3;
	}
	else
	{
		return -1;
	}
}

void polish_notation(char *str, char *result)
{
	TStack Stack;
	int str_i = 0, i = 0;
	while(str[i]!=NULL)
	{
		while ((str[i] <= '9') && (str[i] >= '0'))
		{
			result[str_i++] = str[i++];
			if ((str[i] > '9') || (str[i] < '0'))
			{
				result[str_i] = ' ';
			}
		}
		if ((str[i] == '(') || (str[i] == '*') || (str[i] == '-') || (str[i] == '+') || (str[i] == '/'))
		{
			if ((Stack.IsEmpty()) || (str[i] == '(') || (priority(str[i])>(priority(Stack.Peek()))))
			{
				Stack.Put(str[i]);
			}
			else
			{
				while ((!Stack.IsEmpty()) || (priority(str[i]) <= (priority(Stack.Peek()))))
				{
					result[str_i++] = Stack.Get();
				}
				Stack.Put(str[i]);
			}
			i++;
		}
		if (str[i] == ')')
		{
			while (Stack.Peek() != '(')
			{
				result[str_i++] = Stack.Get();
			}
			Stack.Get();
			i++;
		}
	}
	while (!Stack.IsEmpty())
	{
		result[str_i++] = Stack.Get();
	}
}

int foolproof(char *str)
{
	int ch = 0;
	int i = 0;
	int q = 0, p = 0;
	while (str[i] != NULL) //������������ �������(ASCII)
	{
		if ((str[i]<40) || (str[i]>57) || (str[i] == 44) || (str[i] == 46))
		{
			ch = 1;
		}
		i++;
	}
	i = 0;
	if ((str[0] > 57) || (str[0] < 48) && (str[0] != 45) && (str[0] != 40))//������������ 1-�� �������
	{
		ch = 1;
	}
	if ((str[strlen(str)-1] > 57) || (str[strlen(str) - 1] < 48) && (str[strlen(str) - 1] != 41))//������������ ���������� �������
	{
		ch = 1;
	}
	while (str[i] != NULL) //��������/���������� ������
	{
		if (str[i] == 40)
		{
			q++;
		}
		if (str[i] == 41)
		{
			p++;
		}
		i++;
	}
	if (q != p)
	{
		ch = 1;
	}
	i = 0; q = 0; p = 0;
	while (str[i] != NULL) //���������� ��������
	{
		if ((str[i] >= 42) && (str[i] <= 47) && (str[i + 1] >= 42) && (str[i + 1] <= 47))
		{
			ch = 1;
		}
		i++;
	}
	i = 0;
  return ch;
}

int main()
{
	int a = 0;
	do {
		double result = 0.0;
		char str[Max_Size_Str];
		char str_2[Max_Size_Str] = " ";
		int ch;
		setlocale(LC_ALL, "RUS");
		system("cls");
		cout << "������� ������: ";
		cin >> str;
		ch = foolproof(str);
		if (ch == 1)
		{
			cout << "����������� ���������" << endl;
			goto C1;
			
		}
		polish_notation(str, str_2);
		cout << str_2 << endl;
		C1:
		cout << "������ ���������?" << endl;
		cout << "1.��" << endl;
		cout << "2.���" << endl;
		cin >> a ;
		cout << endl;
	} while (a != 2);
	return 0;
}
#include"TStack.h"
#include<iostream>
#include<string.h>
#include<cstring>
#include<ctype.h>
#include<locale.h>
#include <setjmp.h>

using namespace std;

const int Max_Size_Str = 50;

int priority(char str_s);
void polish_notation(char *str, char *result);
int foolproof(char *str);
char operation(char str, int op1, int op2);
jmp_buf ebuf;

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
	if (str_s == '/')
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

char operation(char str, int op1, int op2)
{
	char res = 0;
	if (str == '+')
	{
		res = op1+op2;
	}
	if (str == '-')
	{
		res = op1 - op2;
	}
	if (str == '*')
	{
		res = op1 * op2;
	}
	if (str == '/')
	{
		if (op2 == 0)
		{
			cout << "Делить на 0 нельзя!" << endl;
			return 0;
		}
		else
		{
			res = op1 / op2;
		}
	}
	return res;
}

void calculator(char * str)
{
	TStack CStack;
	TStack OStack;
	int op1, op2;
	char op;
	float result = 0;
	int val = 0;
	int i = 0; 

	while (str[i] != NULL)
	{
		while ((str[i] != '*') && (str[i] != '/') && (str[i] != '+') && (str[i] != '-') && (str[i] != '(') && (str[i] != ')'))
		{
			val = 0;
			while (isdigit(str[i]))
			{
				val = val * 10 + (str[i++] - 48);
			}
			CStack.Put(val);
			if (str[i] == NULL)
			{
				break;
			}
		}
		if (str[i] == NULL)
		{
			break;
		}
		if (str[i] == '(')
		{
			OStack.Put(str[i]);
			i++;
			continue;
		}
		if (str[i] == ')')
		{
			op = OStack.Get();
			while (op != '(')
			{
				op2 = CStack.Get();
				op1 = CStack.Get();
				result = operation(op, op1, op2);
				CStack.Put(result);
				op = OStack.Get();
			}
			i++;
			continue;
		}
		if (OStack.IsEmpty())
		{
			OStack.Put(str[i]);
		}
		else
		{
			op = OStack.Peek();
			if (priority((char)op) < (priority(str[i])))
			{
				OStack.Put(str[i]);
			}
			else
			{
				op = OStack.Get();
				op2 = CStack.Get();
				op1 = CStack.Get();
				result = operation(op, op1, op2);
				CStack.Put(result);
				OStack.Put(str[i]);
			}
		}
		i++;
	}
	while (!OStack.IsEmpty())
	{
		op = OStack.Get();
		op2 = CStack.Get();
		op1 = CStack.Get();
		result = operation(op, op1, op2);
		CStack.Put(result);
	}
	result = CStack.Get();
	cout << "Результат: " << result << endl;
}


int foolproof(char *str)
{
	int ch = 0;
	int i = 0;
	int q = 0, p = 0;
	TStack skob;
	while (str[i] != NULL) //Неподходящие символы(ASCII)
	{
		if ((str[i]<40) || (str[i]>57) || (str[i] == 44) || (str[i] == 46) || (str[i] == 32))
		{
			ch = 1;
		}
		i++;
	}
	i = 0;
	if ((str[0] > 57) || (str[0] < 48) && (str[0] != 45) && (str[0] != 40))//Корректность 1-го символа
	{
		ch = 1;
	}
	if ((str[strlen(str)-1] > 57) || (str[strlen(str) - 1] < 48) && (str[strlen(str) - 1] != 41))//Корректность последнего символа
	{
		ch = 1;
	}
	while (str[i] != NULL) //Парность/непарность скобок
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
	while (str[i] != NULL) //Порядок скобок
	{
		if (str[i] == '(')
		{
			skob.Put(str[i]);
			i++;
			continue;
		}
		if (str[i] == ')')
		{
			if (skob.IsEmpty())
			{
				ch = 1;
			}
		}
		i++;
	}
	i = 0;
	while (str[i] != NULL) //Повторение символов
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
		float result = 0.0;
		char str_1[Max_Size_Str];
		char str[Max_Size_Str] = " ";
		int ch;
		int i = 0;
		setlocale(LC_ALL, "RUS");
		system("cls");
		cout << "Введите пример: ";
		cin >> str_1;
		ch = foolproof(str_1);
		if (ch == 1)
		{
			cout << "Некоректное выражение" << endl;
			goto C2;
		}
		polish_notation(str_1, str);
		cout << str << endl;
		calculator(str_1);
		C2:
		cout << "Хотите повторить?" << endl;
		cout << "1.Да" << endl;
		cout << "2.Нет" << endl;
		cin >> a ;
		cout << endl;
	} while (a != 2);
	return 0;
}
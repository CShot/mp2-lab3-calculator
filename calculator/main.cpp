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

int main()
{
	double result = 0.0;
	char str[Max_Size_Str];
	char str_2[Max_Size_Str] = " ";
	setlocale(LC_ALL, "RUS");
	cout << "¬ведите пример: ";
	cin >> str;
	polish_notation(str, str_2);
	cout << str_2 << endl;
	return 0;
}
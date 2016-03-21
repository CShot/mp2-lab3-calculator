#include"TStack.h"
#include<iostream>
#include<string.h>
#include<cstring>
#include<ctype.h>
#include<locale.h>

using namespace std;

const int Max_Size_Str = 50;

int priority(char str_s);
void polish_notation(char *str, char *result);
int foolproof(char *str);

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

void polish_notation(char * str, char * result)
{
	TStack Stack;
	int str_i = 0, i = 0;
	while (str[i] != NULL)
	{
		while ((str[i] <= '9') && (str[i] >= '0'))
		{
			result[str_i++] = str[i++];
			if ((str[i] > '9') || (str[i] < '0'))
			{
				result[str_i++] = ' ';
			}
		}
		if ((str[i] == '(') || (str[i] == '*') || (str[i] == '/') || (str[i] == '-') || (str[i] == '+'))
		{
			if ((Stack.IsEmpty()) || (str[i] == '(') || (priority(str[i]) > priority(Stack.Peek())))
			{
				Stack.Put(str[i]);
			}
			else
			{
				while ((!Stack.IsEmpty()) && (priority(str[i]) <= priority(Stack.Peek())))
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

int calculator(char * str)
{
	TStack Stack;
	int result = 0, elem;
	int  a, i = 0;
	while (str[i] != NULL)
	{
		while ((str[i] != '*') && (str[i] != '/') && (str[i] != '-') && (str[i] != '+'))
		{
			elem = 0;
			while (str[i] != ' ')
			{
				elem = elem * 10 + (str[i++] - 48);
			}
			Stack.Put(elem);
			i++;
		}

		if (str[i] == '*')
		{
			a = Stack.Get();
			result = Stack.Get() * a;
			Stack.Put(result);
			i++;
		}
		if (str[i] == '/')
		{
			a = Stack.Get();
			if (a != 0) 
			{
				result = Stack.Get() / a;
				Stack.Put(result);
				i++;
			}
			else
			{
				cout << "На ноль делить нельзя!" << endl;
				result = NULL;
				return result;
			}

		}
		if (str[i] == '+')
		{
			a = Stack.Get();
			result = Stack.Get() + a;
			Stack.Put(result);
			i++;
		}
		if (str[i] == '-')
		{
			a = Stack.Get();
			if (Stack.IsEmpty())
			{
				Stack.Put(0);
			}
			result = Stack.Get() - a;
			Stack.Put(result);
			i++;
		}
	}
	return result;
}


int foolproof(char *str)
{
	int ch = 0;
	int i = 0;
	int q = 0, p = 0,k = 0;
	TStack skob;
	while (str[i] != '\0') //Отсутствие необходимых символов в строке
	{
		if ((str[i] == '*') || (str[i] == '/') || (str[i] == '-') || (str[i] == '+'))
		{
			k++;
		}
		i++;
	}
	if (k == 0)
	{
		ch = 1;
	}
	i = 0;
	while (str[i] != NULL) //Неподходящие символы(ASCII)
	{
		if ((str[i]<40) || (str[i]>57) || (str[i] == 44) || (str[i] == 46) || (str[i] == 32) )
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
	while (str[i] != NULL)
	{
		if ((str[i] == '(' ) && (str[i + 1] == '-' ))
		{
			ch = 1;
		}
		i++;
	}
	i = 0;
  return ch;
}

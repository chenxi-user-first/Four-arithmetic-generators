#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<string>
#include<fstream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

int Number, Type, MaxNum, printType, Bracket, PerNumber;
string suanshi[100];
int NeedFloat;

void UserChoice()
{
	printf("请输入需要生成算式的数量：\n");
	scanf_s("%d", &Number);
	printf("请选择需要生成算式的运算类型：1 加法,2 减法,3 乘法,4 除法,5加减混合，6乘除混合，7加减乘除混合\n");
	scanf_s("%d", &Type);
	printf("请输入算式允许的最大范范围：\n");
	scanf_s("%d", &MaxNum);
	printf("是否包含括号：1 包含，2 不包含\n");
	scanf_s("%d", &Bracket);
	printf("每个算式中最多包含数字的个数：\n");
	scanf_s("%d", &PerNumber);
	printf("是否包含小数：1 是，2否\n");
	scanf_s("%d", &NeedFloat);
	printf("请选择输出方式：1 输出到屏幕,2 输出到文件\n");
	scanf_s("%d", &printType);
}

float RandDigit()
{
	return rand() % MaxNum + 1;
}

float RandFloat()
{
	return (rand() % (MaxNum * 100)) / 100.00;
}

int RandPerNumber()
{
	return rand() % PerNumber + 1;
}

int RandTwo()
{
	return rand() % 2;
}

char RandOperator()
{
	int n = Type;
	if (n == 1)
	{
		return '+';
	}
	if (n == 2)
	{
		return '-';
	}
	if (n == 3)
	{
		return '*';
	}
	if (n == 4)
	{
		return '/';
	}
	if (n == 5)
	{
		if (rand() % 2 == 0)
		{
			return '+';
		}
		else
		{
			return '-';
		}
	}
	if (n == 6)
	{
		if (rand() % 2 == 0)
		{
			return '*';
		}
		else
		{
			return '/';
		}
	}
	if (n == 7)
	{
		int temp = rand() % 4;
		if (temp == 1)
		{
			return '+';
		}
		else if (temp == 3)
		{
			return '-';
		}
		else if (temp == 0)
		{
			return '*';
		}
		else
		{
			return '/';
		}
	}
	if (n == 8)
	{
		return '%';
	}
	else if (n == 9)
	{
		return '~';
	}
	else if (n == 10)
	{
		return '#';
	}
	else
	{
		return '?';
	}
}

string int_string(float number)
{
	float temp = fabs(number);
	char str[200];
	if (NeedFloat == 1)
	{
		_gcvt_s(str, sizeof(str), temp, 7);//将浮点数转换为字符串，并保存正负号和小数点
	}
	else
	{
		_itoa_s(temp, str, 10);//将temp强制转换为整数然后转换为字符串
	}
	string str_ = str;
	return str_;
}

string combination(string str1, string str2, char k)
{
	string equation;
	equation = str1 + k + str2;
	return equation;
}
float Returnfloat()
{
	if (NeedFloat == 1)
	{
		return RandFloat();
	}
	else
	{
		return RandDigit();
	}
}

void Produce()
{
	int itemp = 0;//记录已经产生的算式的个数
	float num1, num2;//随机产生的数
	char symbol;//接受返回的运算符
	string str_num1, str_num2;//随机产生的数的字符串形象式
	while (itemp < Number)
	{
		num1 = Returnfloat();
		num2 = Returnfloat();
		symbol = RandOperator();
		str_num1 = int_string(num1);
		str_num2 = int_string(num2);
		suanshi[itemp] = combination(str_num1, str_num2, symbol);//算式中的数为两个时；
		int count = RandPerNumber();//每个算式中包含数的个数；
		/*
		当算式中的数大于2个时
		*/
		if (count > 2)
		{
			for (count; count > 2; count--)
			{
				symbol = RandOperator();
				str_num1 = suanshi[itemp];
				if (Bracket == 1)//用户决定是否需要括号
				{
					if (RandTwo() == 0)//随机产生括号
					{
						str_num1 = '(' + str_num1 + ')';
					}
				}
				num2 = Returnfloat();
				str_num2 = int_string(num2);
				if (RandTwo() == 0)//随机将新产生的数放置于括号的前面
				{
					suanshi[itemp] = combination(str_num2, str_num1, symbol);
				}
				else
				{
					suanshi[itemp] = combination(str_num1, str_num2, symbol);
				}
			}
		}
		itemp++;
	}
}

void Display()
{
	int i;
	if (printType == 1)
	{
		cout << "生成算式如下" << endl;
		for (i = 0; i < Number; i++)
		{
			cout << suanshi[i] << "=" << endl;
		}
	}
	else
	{
		ofstream fp;
		fp.open("生成算式.txt");
		fp << "生成算式如下：" << endl;
		for (i = 0; i < Number; i++)
		{
			fp << suanshi[i] << "=" << endl;
		}
		fp.close();
	}
}
int main()
{
	srand((int)time(NULL));
	UserChoice();
	Produce();
	Display();
	system("pause");
	return 0;
}


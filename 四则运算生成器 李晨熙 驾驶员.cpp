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
	printf("��������Ҫ������ʽ��������\n");
	scanf_s("%d", &Number);
	printf("��ѡ����Ҫ������ʽ���������ͣ�1 �ӷ�,2 ����,3 �˷�,4 ����,5�Ӽ���ϣ�6�˳���ϣ�7�Ӽ��˳����\n");
	scanf_s("%d", &Type);
	printf("��������ʽ�������󷶷�Χ��\n");
	scanf_s("%d", &MaxNum);
	printf("�Ƿ�������ţ�1 ������2 ������\n");
	scanf_s("%d", &Bracket);
	printf("ÿ����ʽ�����������ֵĸ�����\n");
	scanf_s("%d", &PerNumber);
	printf("�Ƿ����С����1 �ǣ�2��\n");
	scanf_s("%d", &NeedFloat);
	printf("��ѡ�������ʽ��1 �������Ļ,2 ������ļ�\n");
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
		_gcvt_s(str, sizeof(str), temp, 7);//��������ת��Ϊ�ַ����������������ź�С����
	}
	else
	{
		_itoa_s(temp, str, 10);//��tempǿ��ת��Ϊ����Ȼ��ת��Ϊ�ַ���
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
	int itemp = 0;//��¼�Ѿ���������ʽ�ĸ���
	float num1, num2;//�����������
	char symbol;//���ܷ��ص������
	string str_num1, str_num2;//��������������ַ�������ʽ
	while (itemp < Number)
	{
		num1 = Returnfloat();
		num2 = Returnfloat();
		symbol = RandOperator();
		str_num1 = int_string(num1);
		str_num2 = int_string(num2);
		suanshi[itemp] = combination(str_num1, str_num2, symbol);//��ʽ�е���Ϊ����ʱ��
		int count = RandPerNumber();//ÿ����ʽ�а������ĸ�����
		/*
		����ʽ�е�������2��ʱ
		*/
		if (count > 2)
		{
			for (count; count > 2; count--)
			{
				symbol = RandOperator();
				str_num1 = suanshi[itemp];
				if (Bracket == 1)//�û������Ƿ���Ҫ����
				{
					if (RandTwo() == 0)//�����������
					{
						str_num1 = '(' + str_num1 + ')';
					}
				}
				num2 = Returnfloat();
				str_num2 = int_string(num2);
				if (RandTwo() == 0)//������²����������������ŵ�ǰ��
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
		cout << "������ʽ����" << endl;
		for (i = 0; i < Number; i++)
		{
			cout << suanshi[i] << "=" << endl;
		}
	}
	else
	{
		ofstream fp;
		fp.open("������ʽ.txt");
		fp << "������ʽ���£�" << endl;
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


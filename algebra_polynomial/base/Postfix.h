#pragma once
#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	string Operandy = "+-*/";//��������� ��������
	int Prioritet[4] = { 1,1,2,2 };
	bool StringIsRight(string s);//�������� ������������ �����
public:
	TPostfix(string inf = "a+b")
	{
		if (!StringIsRight(inf))
		{
			throw "Errow wint inf";
		}
		for (int i = 0; i < inf.length(); i++)
		{
			//��������� ������� �� ������
			if (inf[i] != ' ')
			{
				infix += inf[i];
			}
		}
		//����, � ����� ���������� ������������ ������
		if (infix.length() < 1)
		{
			throw "Error wint infix's length";
		}
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix();
	double Calculate(); // ���� ����������, ���������� �� ����������� �����
};

#endif
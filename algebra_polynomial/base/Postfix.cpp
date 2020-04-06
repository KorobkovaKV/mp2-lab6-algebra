#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
	TStack<char> opStack(MaxStackSize);
	string operacii = "+-*/()";
	int len = infix.length();
	for (int i = 0; i < len; i++)//���������� �� infix
	{
		if (operacii.find(infix[i]) == string::npos)//���� 1 ������ �� ��������
		{
			postfix += infix[i];
		}
		if ((infix[i] >= '0') && (infix[i] <= '9'))//���� i ������� �����
		{
			if (i != len)
			{
				if ((infix[i + 1] < '0') || (infix[i + 1] > '9'))//� i+1 �� �����
					postfix += ':';
			}
			else
				postfix += ':';
		}
		if (infix[i] == '(')
		{
			opStack.push(infix[i]);
		}
		if (infix[i] == ')')
		{
			char temp = opStack.pop();
			while (temp != '(')
			{
				postfix += temp;
				temp = opStack.pop();
			}
		}
		if (Operandy.find(infix[i]) != string::npos)
		{
			if (opStack.empty() == true)
			{
				opStack.push(infix[i]);
			}
			else
			{
				int index2 = Operandy.find(infix[i]);
				while (opStack.empty() == false)
				{
					char temp = opStack.pop();
					if (temp == '(')
					{
						opStack.push(temp);
						break;
					}
					int index1 = Operandy.find(temp);
					if (Prioritet[index2] <= Prioritet[index1])
						postfix += temp;
					else
					{
						opStack.push(temp);
						break;
					}
				}
				opStack.push(infix[i]);
			}
		}
	}
	while (opStack.empty() == false)
	{
		postfix += opStack.pop();
	}
	return postfix;
}

double TPostfix::Calculate()
{
	if (postfix.length() == 0)
	{
		ToPostfix();//������� ����������� �����
	}
	int length = postfix.length();
	TStack<double> res(MaxStackSize);
	string nameForm;
	double *form = new double[length];
	for (int i = 0; i < length; i++)
	{
		if (Operandy.find(postfix[i]) == string::npos)//������ �� ��������
		{
			double p;//�������� �������������� ����������(�������� ����)
			if ((postfix[i] < '0') || (postfix[i] > '9'))//������ �� �����
			{
				//������ ����������
				if (nameForm.find(postfix[i]) == string::npos)//����������� ������ ���
				{
					nameForm += postfix[i];
					cout << "������� �������� ���������� - " << postfix[i] << endl;
					cin >> p;
					form[nameForm.length() - 1] = p;//�������� � ������ ���������
				}
				else
				{
					p = form[nameForm.find(postfix[i])];//��� �����������
				}
			}
			else//������ �����
			{
				string number;
				while (postfix[i] != ':')//���� ����� �����
				{
					number += postfix[i];
					i++;
				}
				p = stoi(number);//�������������� � ����� ����� ������
			}
			res.push(p);//�������� ���������� ��� ����� � ����
		}
		else//������ ��������
		{
			double zn1, zn2, Res;
			//����� �� ����� 2 ��������� ��������
			zn2 = res.pop();
			zn1 = res.pop();
			switch (postfix[i])//����� ��� ��������??
			{
			case '+': Res = zn1 + zn2; break;
			case '-': Res = zn1 - zn2; break;
			case '*': Res = zn1 * zn2; break;
			case '/': Res = zn1 / zn2; break;
			}
			res.push(Res);//�������� � ���� ��������� ��������
		}
	}
	delete[] form;//������� ������ ��������
	return res.pop();//���������� ��������� ������� ����� = ���������� ����� ���������
}
bool TPostfix::StringIsRight(string s)
{
	string nevozmozhno = "!@#^&.,<>{}[]|=_?";//�������, ������� �� ������ ���� � ���������
	int ckob = 0, k = 0, countOperation = 0;
	int length = s.length();
	if ((Operandy.find(s[0]) != string::npos) || (Operandy.find(s[length - 1]) != string::npos))
	{
		return false;//��������� �������� ��� ����������� � ��������
	}
	for (int i = 0; i < length; i++)//�������� �������� ������� ������
	{
		if (nevozmozhno.find(s[i]) != string::npos)//�������� �������� ������ s �� ����������� �������
		{
			return false;//����� 
		}
		//�������� �� �������� ������
		if (s[i] == '(')
		{
			ckob++;
		}
		if (s[i] == ')')
		{
			ckob--;
		}
		//������� ����������
		if ((s[i] - 'a' >= 0) && (s[i] - 'a' <= 26))
		{
			k++;
		}
		else
		{
			k = 0;
		}
		//������� �������� (��������)
		if (Operandy.find(s[i]) != string::npos)
		{
			countOperation++;
		}
		else
		{
			countOperation = 0;
		}
		if ((k > 1) || (countOperation > 1))//���������� ��� �������� ���� ������, �.�. ab+-
		{
			return false;
		}
	}
	if (ckob != 0)//������ � �������
	{
		return false;
	}
	return true;
}
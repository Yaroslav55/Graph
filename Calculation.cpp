/********************************************
		Algorithm Reverse Polish notation
		
	Yaroslav 03.10.17
********************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include "Calculation.h"

void Calculation::ParsingExam(std::string text)
{
	std::string a;
	for (int i = 0; i < text.length();i++)
	{
		if ((isalnum(text[i])) || (text[i] == '.'))
		{
			a += text[i];
			if (i == text.length() - 1)
			{
				buffer.push_back(a);
			}
		}
		else
		{
			if (!a.empty())
				buffer.push_back(a);
			std::cout << "A:" << a << std::endl;
			a = text[i];
			buffer.push_back(a);
			a.clear();
		}
	}
	a.clear();
	CreateRPN();
	
}
void Calculation::CreateRPN()
{
	//Create RPN
	unsigned int i = 0;
	std::string cache;
	for (;i < buffer.size();i++)
	{
		if (atof(buffer[i].c_str()) != false)//Is number
		{
			OutputSteck.push_back(buffer[i]);
		}
		else if (*buffer[i].c_str() == 'x')
			OutputSteck.push_back("x");
		else if (*buffer[i].c_str() == 's')
		{
			OutputSteck.push_back(buffer[i]);
			for (; i < buffer.size(); i++)
			{
				if( buffer[i][0] == ')')
					std::cout << buffer[i]  << std::endl;
			}
		}
		else if (*buffer[i].c_str() == 'c')
		{
			OutputSteck.push_back(buffer[i]);
		}
		else if (*buffer[i].c_str() == '(')
		{
			Steck.push_back(buffer[i]);
		}
		else if (*buffer[i].c_str() == ')')
		{
			while ( Steck[ Steck.size() - 1][0] != '(')
			{
				OutputSteck.push_back(Steck[Steck.size() - 1]);
				Steck.pop_back();
			}
			Steck.pop_back();
		}
		else
		{
			while (SymbolPriority(*buffer[i].c_str()) <= SymbolPriority())
			{
				if ((!Steck.empty()) )
				{
					OutputSteck.push_back(Steck[Steck.size() - 1]);
					Steck.pop_back();
				}
			}
			Steck.push_back(buffer[i]);	
		}
	}
	//Set for priority
	for (unsigned int i = 1;i < Steck.size();i++)
	{
		if ((atoi(Steck[i-1].c_str()) == false) && (atoi(Steck[i].c_str()) == false) ||(*Steck[i].c_str() != 'x'))//Not number
		{
			while (SymbolPriority(*Steck[i-1].c_str()) < SymbolPriority(*Steck[i].c_str()))
			{
				std::string a = Steck[i - 1];
				Steck[i - 1] = Steck[i];
				Steck[i] = a;
			}
		}
	}
	std::string a;
	for (unsigned int i = 0; i < OutputSteck.size();i++)
	{
		a += OutputSteck[i].c_str();
		a += " ";
	}
	for (unsigned int i = 0; i < Steck.size();i++)
	{
		a += Steck[i].c_str();
		a += " ";
	}
	for (unsigned int i = 0; i < Steck.size();i++)
	{
		OutputSteck.push_back(Steck[i]);
	}
	std::cout <<"RPN "<< a.c_str() << std::endl;
}
float Calculation::CalculationExpression(float X)
{
	std::vector<float> res;
	if (OutputSteck.empty())
		return -10;
	X = X / 10;
	for (unsigned int i = 0;i < OutputSteck.size();i++)
	{
		switch (OutputSteck[i].at(0))
		{
		case '^':
		{
			res[res.size() - 2] = pow(res[res.size() - 2], res[res.size() - 1]);
			res.pop_back();
		}
		break;
		case '*':
		{
			res[res.size() - 2] = res[res.size() - 2] * res[res.size() - 1];
			res.pop_back();
		}
		break;
		case '/':
		{
			res[res.size() - 2] = res[res.size() - 2] / res[res.size() - 1];
			res.pop_back();
		}
		break;
		case '+':
		{
			res[res.size() - 2] = res[res.size() - 2] + res[res.size() - 1];
			res.pop_back();
		}
		break;
		case '-':
		{
			res[res.size() - 2] = res[res.size() - 2] - res[res.size() - 1];
			res.pop_back();
		}
		break;
		case 'x':
		{
			res.push_back(X);
		}
		break;
		case 's':
		{
			std::string a;
			for (unsigned int j = 3; j < OutputSteck[i].length();j++)
			{
				if (OutputSteck[i][j] == 'x')
					a += std::to_string(X);
				else
					a += OutputSteck[i][j];
			}
			res.push_back(sin(atof(a.c_str())));
		}
		break;
		case 'c':
		{
			std::string a;
			for (unsigned int j = 3; j < OutputSteck[i].length();j++)
			{
				a += OutputSteck[i][j];

			}

			if (OutputSteck[i][3] == 'x')
			{
				res.push_back(cos(X));
			}
			else
				res.push_back(cos(atoi(a.c_str())));
		}
		break;
		default:
			res.push_back(atof(OutputSteck[i].c_str()));
			break;

		}
	}
	return res[0] *10;
}
int Calculation::SymbolPriority()
{
	if (Steck.empty()) {
		return -1;
	}
	switch (Steck.back().at(0)) {
		case('^'): {
			return 4;
			break;
		}
		case('*'):
		case('/'): {
			return 3;
			break;
		}
		case('+'):
		case('-'): {
			return 2;
			break;
		}
		case('('): {
			return 1;
			break;
		}
		default: {
			std::cerr << "Invalid character! " << Steck[Steck.size() - 1].c_str() << std::endl;
			return -1;
		}
	}
}
int Calculation::SymbolPriority(char a)
{
	switch (a)
	{
	case '^':
	{
		return 4;
	}
	break;
	case '*':
	case '/':
	{
		return 3;
	}
	break;
	case '+':
	case '-':
	{
		return 2;
	}
	break;
	case '(':
	{
		return 1;
	}
	break;
	default:
		std::cout << "Invalid character! " << a << std::endl;
		return -1;
		break;
	}
}
void Calculation::ClearData()
{
	buffer.clear();
	OutputSteck.clear();
	Steck.clear();
}
#pragma once
class Calculation
{
private:
	std::vector<std::string> buffer;
	std::vector<std::string> OutputSteck;
	std::vector<std::string> Steck;
	float StepX;
	int CellSize;
	void CreateRPN();
	int SymbolPriority(char a);
	int SymbolPriority();
public:

	void ParsingExam(std::string text);
	float CalculationExpression(float X);
	void ClearData();
};


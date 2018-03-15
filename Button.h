#pragma once
#include <iostream>
#include <vector>

class Button
{
public:

	void CreateButton(std::string text,int x, int y, int SizeX, int SizeY, unsigned int colorRGB);
	int OnButtonEnter(int mouseX, int mouseY);
	void RenderButton();
	void RenderText(int x, int y, int z, std::string text, unsigned int color);
private:
	std::vector<std::string> m_ButtonText;
	std::vector<unsigned int> m_ButtonTextColor;
	std::vector<int> m_ButtonPosX;
	std::vector<int> m_ButtonPosY;
	std::vector<int> m_ButtonSizeX;
	std::vector<int> m_ButtonSizeY;
};
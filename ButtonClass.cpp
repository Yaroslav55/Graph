/**********************************************

************************************************/
#include <stdafx.h>
#include <windows.h> 
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <glut.h>
#include "Button.h"
void Button::CreateButton(std::string text, int x, int y, int SizeX, int SizeY, unsigned int colorRGB) {
	m_ButtonPosX.push_back(x);
	m_ButtonPosY.push_back(y);
	m_ButtonSizeX.push_back(SizeX);
	m_ButtonSizeY.push_back(SizeY);
	m_ButtonText.push_back(text);
	m_ButtonTextColor.push_back(colorRGB);
}
int Button::OnButtonEnter(int mouseX, int mouseY) {

	for (int i = 0;i < m_ButtonPosX.size();i++)
	{
		if ((mouseX > m_ButtonPosX[i] && (mouseX < m_ButtonPosX[i] + m_ButtonSizeX[i])) &&
			(500 - mouseY > m_ButtonPosY[i] && (500 - mouseY < m_ButtonPosY[i] + m_ButtonSizeY[i])))
			return i;
	}
	return -1;
}
void Button::RenderButton() {
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < m_ButtonPosX.size(); i++)
	{
		glColor3f(0.6, 0.6, 0.6);
		glBegin(GL_QUADS);
			glVertex2i(m_ButtonPosX[i], m_ButtonPosY[i]);
			glVertex2i(m_ButtonPosX[i] + m_ButtonSizeX[i], m_ButtonPosY[i]);
			glVertex2i(m_ButtonPosX[i] + m_ButtonSizeX[i], m_ButtonPosY[i] + m_ButtonSizeY[i]);
			glVertex2i(m_ButtonPosX[i], m_ButtonPosY[i] + m_ButtonSizeY[i]);
		glEnd();
		RenderText(m_ButtonPosX[i]+2, m_ButtonPosY[i]+8, 0, m_ButtonText[i], m_ButtonTextColor[i]);
	}
}
void Button::RenderText(int x, int y, int z, std::string text, unsigned int color)
{
	glDisable(GL_TEXTURE_2D);
	switch (color)
	{
		case 0:
		{
			glColor3f(0, 0, 0);
		}
		break;

		case 1:
		{
			glColor3f(1, 0, 0);
		}
		break;

		case 2:
		{
			glColor3f(0, 1, 0);
		}
		break;
		case 3:
		{
			glColor3f(0, 0, 1);
		}
		break;
		default:
			break;
	}
	glRasterPos3f(x, y, z);
	for (int i = 0; i < text.length(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}

}
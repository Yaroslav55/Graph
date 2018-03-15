/**********************************************
		GRAPH 
			Dev. by Yaroslav
************************************************/
#include <stdafx.h>
#include <windows.h> 
#include <glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Button.h"
#include "Calculation.h"
using namespace std;
#define DispSizeX int(550)
#define DispSizeY int(500)

int StepX = 1;
void ButtonPresed(int buttonID);

int CellNum = 50;

Button g_button;
Calculation g_calc[2];
string buffer[2];
unsigned int CurLabel = 0;
int MouseCoordX, MouseCoordY;
void Timer(int value)
{
	switch (value)
	{
		case 0:
		{
			glutTimerFunc(300, Timer, 0);
			glutPostRedisplay();
		}
		break;
		default:
			break;
	}
}
void RenderGrid()
{
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);//Graph 
		glVertex2f(1, 51);
		glVertex2f(501, 51);
		glVertex2f(501, 501);
		glVertex2f(1, 501);
	glEnd();

	glColor3f(0, 0, 0);
	glLineWidth(1);
	glBegin(GL_LINES);
		for (int x = 0; x <= 500;x += (500 / CellNum))
		{
			glVertex2f(x +1, 49);
			glVertex2f(x + 1, 499);

			glVertex2f(1, x +49);
			glVertex2f(501,x +49 );
		}
		glColor3f(0, 1, 0);
		glVertex2f(250, 50);
		glVertex2f(250, 500);
		glVertex2f(0, 250);
		glVertex2f(500, 250);
	glEnd();

}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	RenderGrid();
	glLineWidth(2);
	glPointSize(5);
	/******Rend Graph*******/
	for (unsigned int j = 0; j < 2;j++)
	{
		glColor3f(1 -j, 0, j);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < 250;i += StepX)
		{
			glVertex2f(i + 250, g_calc[j].CalculationExpression(i) + 250);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (float i = -250; i <= 0;i += StepX)
		{
			glVertex2f(i + 250, g_calc[j].CalculationExpression(i) + 250);
		}
		glEnd();
	}
	glBegin(GL_QUADS);//Label
		glColor3f(0.8, 0.8, 0.8);
		glVertex2f(0, 0);
		glVertex2f(0, 49);
		glVertex2f(550, 49);
		glVertex2f(550, 0);
	glEnd();
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_QUADS);//Label 
		glVertex2f(70, 1);
		glVertex2f(230, 1);
		glVertex2f(230, 40);
		glVertex2f(70, 40);
	glEnd();
	g_button.RenderText(80, 2, 0, buffer[CurLabel], 0);

	g_button.RenderText(405, 2, 0, "(", 0);
	g_button.RenderText(410, 2, 0, std::to_string((MouseCoordX-250)/10), 0);
	g_button.RenderText(445, 2, 0, ":", 0);
	g_button.RenderText(450, 2, 0, std::to_string(int(DispSizeY-MouseCoordY-240) / 10), 0);
	g_button.RenderText(495, 2, 0, ")", 0);
	g_button.RenderButton();
	glFlush();
}
void MouseButton(int button, int state, int x, int y)
{
	if( state == 0 )
	{
		switch (button)
		{

			case GLUT_LEFT_BUTTON:
			{
				ButtonPresed( g_button.OnButtonEnter(x, y) );
			}
			break;
		}
		MouseCoordX = x;
		MouseCoordY = y;
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
	{
		exit(0);
	}
	break;
	case 8:
	{
		if( !buffer[CurLabel].empty() )
			buffer[CurLabel].resize(buffer[CurLabel].length()-1);
	}
	break;
	default:
		if (buffer[CurLabel].length() < 20)
			buffer[CurLabel] += key;
		break;
	}
}
void ButtonPresed(int buttonID)
{
	switch (buttonID)
	{
		case 0:
		{
			g_calc[CurLabel].ClearData();
			g_calc[CurLabel].ParsingExam(buffer[CurLabel]);
			glutPostRedisplay();
		}
		break;

		case 1:
		{
			CurLabel = 0;
			glutPostRedisplay();
		}
		break;
		case 2:
		{
			CurLabel = 1;
			glutPostRedisplay();
		}
		break;
		case 3:
		{
			if (StepX > 1)
				StepX -= 10;
			else
				StepX = 1;
			glutPostRedisplay();
		}
		break;
		case 4:
		{
			if (StepX < 30)
				StepX += 10;
			glutPostRedisplay();
		}
		break;
		default:
			break;
	}
}
void Initialize() {
	glClearColor(0.8, 0.8, 0.8, 0.8);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, DispSizeX, 0.0, DispSizeY, -1.0, 1.0);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseButton);
	glutTimerFunc(300, Timer, 0);
	g_button.CreateButton("Go",250, 0, 40, 40, 0);
	g_button.CreateButton(" 1", 505, 400, 30, 30, 1);
	g_button.CreateButton(" 2", 505, 360, 30, 30, 2);
	g_button.CreateButton(" +", 505, 300, 30, 30, 3);
	g_button.CreateButton(" -", 505, 260, 30, 30, 3);
//	std::getline(std::cin, buffer);
}
int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(550, 500);
	glutInitWindowPosition(400, 250);
	glutCreateWindow("Graph v0.1");
	glutDisplayFunc(Display);
	Initialize();	// Main cycle 
	glutMainLoop();

	return 0;
}
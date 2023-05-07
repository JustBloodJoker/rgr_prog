#include "RenderScenes.h"
#include "Utilits.h"

void RenderScenes::MenuScene()
{
	//малювання головного меню
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawFont("Matches", 350, 700, GLUT_BITMAP_TIMES_ROMAN_24);

	glColor3f(1.0f, 0.5f, 0.3f);
	this->rectangles.at(0).Draw();

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawFont("Rules", 370, 575, GLUT_BITMAP_TIMES_ROMAN_24);

	glColor3f(1.0f, 0.5f, 0.3f);
	this->rectangles.at(1).Draw();

	glColor3f(1.0f, 1.0f, 1.0f);
	DrawFont("Play", 375, 335, GLUT_BITMAP_TIMES_ROMAN_24);

	DrawFont("Created by Samoilenko Denys KV-21", 10, 10, GLUT_BITMAP_TIMES_ROMAN_10);
}

void RenderScenes::GameScene()
{
	//малювання ігрової сцени
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawFont("Enter the number of matches you want to remove", 180, 500, GLUT_BITMAP_TIMES_ROMAN_24);

	//змінюється текст при зміні гравця
	switch (this->player)
	{
	case 1:
		DrawFont("Player1. Time to take some matches", 240, 550, GLUT_BITMAP_TIMES_ROMAN_24);
		break;
	case 0:
		DrawFont("Player2. Time to take some matches", 240, 550, GLUT_BITMAP_TIMES_ROMAN_24);
		break;
	}

	//перевірка на коректність введених даних
	if (this->userNum < 1 || this->userNum > 10) 
	{
		DrawFont("Invalid number", 330, 400, GLUT_BITMAP_TIMES_ROMAN_24);
		glutPostRedisplay();
	}
	
	DrawFont(this->userInputText, 400, 450, GLUT_BITMAP_TIMES_ROMAN_24);
}

void RenderScenes::RulesScene()
{
	//малювання сцени з правилами
	DrawFont("\"Matches.\"", 375, 700, GLUT_BITMAP_TIMES_ROMAN_24);

	DrawFont("There is a pile of 100 matches.",	0, 560, GLUT_BITMAP_TIMES_ROMAN_24);
	DrawFont("Two players take turns taking a few matches from the pile: ", 0, 520, GLUT_BITMAP_TIMES_ROMAN_24);
	DrawFont("at least one and no more than ten. ",	0, 480, GLUT_BITMAP_TIMES_ROMAN_24);
	DrawFont("The loser is the one who took the last match.", 0, 440, GLUT_BITMAP_TIMES_ROMAN_24);

	DrawFont("PRESS F1 TO RETURN TO MAIN MENU",	200, 250, GLUT_BITMAP_TIMES_ROMAN_24);
}

void RenderScenes::EndGameScene()
{
	//малювання кінцевої сцени
	if (this->player == 1)
	{
		DrawFont("Player 1 is win!", 300, 400, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else 
	{
		DrawFont("Player 2 is win!", 300, 400, GLUT_BITMAP_TIMES_ROMAN_24);
	}

	DrawFont("PRESS F1 TO RETURN TO MAIN MENU", 200, 250, GLUT_BITMAP_TIMES_ROMAN_24);
}

void RenderScenes::RestartGame()
{
	//перезапуск гри (зміна полей класу на початкові)
	this->player = 1;
	this->matchesCount = 100;
	this->userInputText = "0";
	this->userNum = 1;
}

void RenderScenes::CreateMouseCallbackMessageGameScene()
{
	//метод класу який викликається під час гри при натисканні enter після вводу данних

	//зміна кількості сірників у коробку
	this->userNum = std::stoi(this->userInputText);
	
	if (this->userNum >= 1 && this->userNum <= 10) 
	{
		SwitchPlayers();
		this->matchesCount -= this->userNum;
	}
}

void RenderScenes::SwitchPlayers()
{	
	//зміна гравця
	this->player = (this->player+1) % 2;
}

void RenderScenes::DrawFont(std::string text, GLint x, GLint y, void* font)
{
	//малювання тексту на екрані
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);

	for (auto el : text)
	{
		char c = el;
		glutBitmapCharacter(font, c);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glEnable(GL_TEXTURE_2D);
}
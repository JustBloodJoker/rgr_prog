#pragma once

#include "stdafx.h"

// клас із сценами 
class RenderScenes
{
private:
	//структура прямокутника
	typedef struct Rectangle {
		Rectangle(float x, float y, float dx, float dy) 
		{
			this->x = x;
			this->y = y;
			this->dx = dx;
			this->dy = dy;
		}

		//функція для малювання прямокутника
		void Draw() 
		{
			glBegin(GL_QUADS);
			glVertex2f(this->x, this->y);
			glVertex2f(this->x + this->dx, this->y);
			glVertex2f(this->x + this->dx, this->y + this->dy);
			glVertex2f(this->x, this->y + this->dy);
			glEnd();
		}

		float x, y, dx, dy;
	};

public:
	
	RenderScenes() 
	{
		//заповнення полей класу даними
		this->rectangles.push_back({ -0.3f, 0.3f, 0.6f, 0.3f });
		this->rectangles.push_back({ -0.3f, -0.3f, 0.6f, 0.3f });
		this->matchesCount = 100;
		this->player = 1;
		this->userNum = 1;
	};

	~RenderScenes() 
	{ 
		this->rectangles.clear(); 
		this->userInputText.clear(); 
	}

	void MenuScene();
	void GameScene();
	void RulesScene();
	void EndGameScene();

	void RestartGame();

	void CreateMouseCallbackMessageGameScene();

	
	std::vector<Rectangle> GetRectangles() { return this->rectangles; }
	int GetMatchesCount() { return this->matchesCount; }

	std::string userInputText = "0";
private:
	void SwitchPlayers();
	void DrawFont(std::string text, GLint x, GLint y, void* font);

	std::vector<Rectangle> rectangles;
	int matchesCount;
	int player;
	int userNum;
};


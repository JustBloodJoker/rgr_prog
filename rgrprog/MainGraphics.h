#pragma once
#include "stdafx.h"
#include "RenderScenes.h"

//���� � ��������� ����������� �� ���� ���������� GLUT OpenGL
class MainGraphics
{
public:

	MainGraphics(int argc, char** argv);
	~MainGraphics();

private:
	void MenuInit();

	static int scene;
	static RenderScenes rs;

	static void RenderScene();

	static void KeyMessagesCallback(int key, int x, int y);
	static void MouseMessagesCallback(int button, int state, int x, int y);
	static void hangleInputCallback(unsigned char key, int x, int y);

	static bool Check(int x, int y, float X, float Y, float dx, float dy);
	static void ChangeScene(int scene) { MainGraphics::scene = scene; };

	static void MenuCallbackMessage(int choice);
};



#include "MainGraphics.h"
#include "Utilits.h"

int MainGraphics::scene = 0;
RenderScenes MainGraphics::rs = RenderScenes();

MainGraphics::MainGraphics(int argc, char** argv)
{
	//����������� 
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(HEIGHT, WIDTH);
	glutCreateWindow("RGR_SAMOILENKO_MATCHES");

	//���� ���� (����� ������ =) )
	glClearColor(0.0f, 0.125f, 0.3f, 1.0f);

	///�����������  ����
	MenuInit();

	//������� ������� ��� ������� ����� �� ������� ����������
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(KeyMessagesCallback);
	glutMouseFunc(MouseMessagesCallback);
	glutKeyboardFunc(hangleInputCallback);

	glutMainLoop();
}

MainGraphics::~MainGraphics()
{
	MainGraphics::rs.~RenderScenes();
}

void MainGraphics::MenuInit()
{
	//����������� ���� � ����� ��������
	glutCreateMenu(MenuCallbackMessage);
	glutAddMenuEntry("Restart game", 1);
	glutAddMenuEntry("Exit", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MainGraphics::MenuCallbackMessage(int choice)
{
	//��� 1 ����� ��������������� ���, ��� ����� 2 �������� �� ��������
	switch (choice) {
	case 1:
		MainGraphics::rs.RestartGame();
		break;
	case 2:
		exit(0);
		break;
	}
}

void MainGraphics::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//���� ����� _GAME ���, _RULES �������, _MAINMENU ������� ����, _ENDGAME ���� ��������� �� �����
	switch (MainGraphics::scene) {
	case _GAME:
		MainGraphics::rs.GameScene();
		glutPostRedisplay();
		break;
	case _RULES:
		MainGraphics::rs.RulesScene();
		glutPostRedisplay();
		break;
	case _MAINMENU:
		MainGraphics::rs.MenuScene();
		glutPostRedisplay();
		break;
	case _ENDGAME:
		MainGraphics::rs.EndGameScene();
		glutPostRedisplay();
		break;
	}

	glutSwapBuffers();
}

void MainGraphics::KeyMessagesCallback(int key, int x, int y)
{
	//����� �� ���� �-�� ��������� ������ F1 (������ ���� �� ��� ������� ���� ��� �� ������)
	switch (key)
	{
	case GLUT_KEY_F1:
		if (MainGraphics::scene == _ENDGAME || MainGraphics::scene == _RULES)
			ChangeScene(_MAINMENU);
		break;
	}
}

void MainGraphics::MouseMessagesCallback(int button, int state, int x, int y)
{
	//���������� �� ������
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (Check(x, y, MainGraphics::rs.GetRectangles().at(0).x,
						MainGraphics::rs.GetRectangles().at(0).y,
						MainGraphics::rs.GetRectangles().at(0).dx, 
						MainGraphics::rs.GetRectangles().at(0).dy) && 
						          (MainGraphics::scene == _MAINMENU))
		{	
			ChangeScene(_RULES);
		}
		else if (Check(x, y, MainGraphics::rs.GetRectangles().at(1).x,
							 MainGraphics::rs.GetRectangles().at(1).y,
							 MainGraphics::rs.GetRectangles().at(1).dx, 
							 MainGraphics::rs.GetRectangles().at(1).dy) &&
									   (MainGraphics::scene == _MAINMENU))
		{
			MainGraphics::rs.RestartGame();
			ChangeScene(_GAME);
		}
	}
}

void MainGraphics::hangleInputCallback(unsigned char key, int x, int y)
{
	//����� � ��� �� ESC (����������� WinApi)
	if (key == 27) {
		if(MessageBox(NULL, L"Are you sure you want to exit?", L"Exit State", MB_YESNO | MB_ICONQUESTION) == IDYES )
			exit(0);
	}
	//��� � ��������� ���� ����!
	if (MainGraphics::scene == _GAME) {
		if (key == '\r')
		{
			MainGraphics::rs.CreateMouseCallbackMessageGameScene();
			if (MainGraphics::rs.GetMatchesCount() <= 0)
				MainGraphics::scene = _ENDGAME;
		}
		else if (key == '\b' && MainGraphics::rs.userInputText.length()>0)
		{
			MainGraphics::rs.userInputText.erase(MainGraphics::rs.userInputText.length() - 1);
		}
		else if (key >= 48 && key <= 57 )
		{
			MainGraphics::rs.userInputText += key;
		}
	}
	glutPostRedisplay();
}

//�������� �� ����������� � �� � � ���������� ������, �� � �� � - ���������� � ������� (������ ���� �� ���� ����� ������ ������� �������)
bool MainGraphics::Check(int x, int y, float X, float Y, float dx, float dy)
{
	return ((static_cast<float>((WIDTH - x) - WIDTH / 2) / (WIDTH / 2)) > X) &&
		   ((static_cast<float>((WIDTH - x) - WIDTH / 2) / (WIDTH / 2)) < X + dx) &&
		   ((static_cast<float>((HEIGHT - y) - HEIGHT / 2) / (HEIGHT / 2)) > Y) &&
		   (((static_cast<float>((HEIGHT - y) - HEIGHT / 2)) / (HEIGHT / 2)) < Y + dy);
}
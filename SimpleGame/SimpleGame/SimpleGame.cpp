#include "stdafx.h"
#include "GameMgr.h"

GameMgr* gameMgr{};

void Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(wndSizeX, wndSizeY);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0")) { std::cout << " GLEW Version is 3.0\n "; }
	else { std::cout << "GLEW 3.0 not supported\n "; }
}

void RenderScene(int temp)
{
	gameMgr->update(static_cast<float>(gameMgr->getElapsedTime()) / 1000);
	gameMgr->render();

	glutSwapBuffers();	// double buffering
	glutTimerFunc(frame, RenderScene, NULL);
}

void Display()
{
}

void Idle()
{
}

void MouseInput(int button, int state, int x, int y)
{
}

void KeyDownInput(unsigned char key, int x, int y)
{
	gameMgr->keyDownInput(key, x, y);
}

void KeyUpInput(unsigned char key, int x, int y)
{
	gameMgr->keyUpInput(key, x, y);
}

void SpecialKeyDownInput(int key, int x, int y)
{
	gameMgr->specialKeyDownInput(key, x, y);
}

void SpecialKeyUpInput(int key, int x, int y)
{
	gameMgr->specialKeyUpInput(key, x, y);
}

int main(int argc, char **argv)
{
	Init(argc, argv);

	gameMgr = GameMgr::getInstance();

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);
	glutMouseFunc(MouseInput);
	glutTimerFunc(frame, RenderScene, NULL);

	glutMainLoop();

    return 0;
}
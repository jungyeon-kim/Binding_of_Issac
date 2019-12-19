#include "stdafx.h"
#include "ScnMgr.h"

void Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(wndSizeX, wndSizeY);
	glutCreateWindow("Binding OF Isaac");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0")) { std::cout << " GLEW Version is 3.0\n "; }
	else { std::cout << "GLEW 3.0 not supported\n "; }
}

void RenderScene(int temp)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	scnMgr->update(static_cast<float>(scnMgr->getElapsedTime()) / 1000);
	scnMgr->render();

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
	scnMgr->keyDownInput(key, x, y);
}

void KeyUpInput(unsigned char key, int x, int y)
{
	scnMgr->keyUpInput(key, x, y);
}

void SpecialKeyDownInput(int key, int x, int y)
{
	scnMgr->specialKeyDownInput(key, x, y);
}

void SpecialKeyUpInput(int key, int x, int y)
{
	scnMgr->specialKeyUpInput(key, x, y);
}

int main(int argc, char **argv)
{
	Init(argc, argv);

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
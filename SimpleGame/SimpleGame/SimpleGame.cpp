/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "GameMgr.h"
#include "GameController.h"

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
	gameMgr->update(static_cast<float>(GameMgr::getInstance()->getElapsedTime()) / 1000);
	gameMgr->render();

	glutSwapBuffers();	// double buffering
	glutTimerFunc(16, RenderScene, NULL);
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
	gameCon->keyDownInput(key, x, y);
}

void KeyUpInput(unsigned char key, int x, int y)
{
	gameCon->keyUpInput(key, x, y);
}


void SpecialKeyInput(int key, int x, int y)
{
}

int main(int argc, char **argv)
{
	Init(argc, argv);

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutTimerFunc(16, RenderScene, NULL);

	glutMainLoop();

    return 0;
}
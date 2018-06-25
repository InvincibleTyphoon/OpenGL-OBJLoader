#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <gl/glew.h>
#include <gl/glut.h>
#include "OBJLoader.h"
#pragma comment(lib, "glew32.lib")

using namespace std;

// Vertex Shader script
const char*  vsSource = "#version 120 \n\
attribute vec4 aPos; \n\
attribute vec4 aColor; \n\
varying vec4 vColor; \n\
void main(){ \n\
	gl_Position = aPos; \n\
	vColor = aColor; \n\
}";

// Fragment Shader script
const char* fsSource = "#version 120 \n\
varying vec4 vColor; \n\
void main(){ \n\
	gl_FragColor = vColor; \n\
}";

GLuint vs = 0;		//vertex shader indicator
GLuint fs = 0;		//fragment shader indicator
GLuint prog = 0;	//program

char buf[1024];

OBJLoader* objloader;

GLfloat red[] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f
};

void mydisplay(void) {
	GLuint posLoc, colorLoc;
	glClearColor(0.f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	posLoc = glGetAttribLocation(prog, "aPos");
	colorLoc = glGetAttribLocation(prog, "aColor");

	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(colorLoc);

	objloader->SetColor(colorLoc, red);
	objloader->Draw(posLoc);

	glFlush();
	glutSwapBuffers();
}

void myinit() {
	GLint status;

	glEnable(GL_DEPTH_TEST);
	//vs : vertex shader
	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
	printf("vs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(vs, sizeof(buf), NULL, buf);
	printf("vs log = [%s]\n", buf);

	//fs : fragment shader
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);	//compile to get .OBJ

	// Error checking
	glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
	printf("fs compile status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetShaderInfoLog(fs, sizeof(buf), NULL, buf);
	printf("fs log = [%s]\n", buf);

	//prog : program
	prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);

	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	printf("program link status = %s\n", (status == GL_TRUE) ? "true" : "false");
	glGetProgramInfoLog(prog, sizeof(buf), NULL, buf);
	printf("validate log = [%s]\n", buf);

	glUseProgram(prog);
}

int main(int argc, char* argv[]) {
	char fname[] = "elepham.obj";
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("OpenGL/GLUT OBJ Loader.");
	glutDisplayFunc(mydisplay);
	glewInit();
	myinit();

	objloader = new OBJLoader(fname);

	//showDoubleVector(v);
	glutMainLoop();
}
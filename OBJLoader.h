#pragma once
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

#pragma comment(lib, "glew32.lib")

using namespace std;

class OBJLoader {
public:
	OBJLoader() {
		strcpy(objName, "DefaultName");
		size[0] = 0.00125;
		size[1] = size[0];
		size[2] = size[0];
		rotation[0] = 0.0;
		rotation[1] = rotation[0];
		rotation[2] = rotation[0];
		pos[0] = 0.0;
		pos[1] = pos[0];
		pos[2] = pos[1];
	}
	OBJLoader(const char fname[]) : OBJLoader((char*) fname){
		
	}

	OBJLoader(char * fname) : OBJLoader() {
		FILE * fptr = fopen(fname, "r");
		char line[1000];
		int i = 0;

		strcpy(objName, fname);

		while (!feof(fptr)) {
			memset(line, 0, sizeof(line));
			fgets(line, 1000, fptr);
			//printf("%d: %s", i + 1,line);
			if (line[0] == 'v' && line[1] == 'n') {
				line[0] = ' ';
				line[1] = ' ';
				float x, y, z;
				vector<float> input;
				sscanf(line, "%f %f %f", &x, &y, &z);
				input.push_back(x);
				input.push_back(y);
				input.push_back(z);
				vn.push_back(input);
			}
			else if (line[0] == 'v') {
				line[0] = ' ';
				float x, y, z;
				vector<float> input;
				sscanf(line, "%f %f %f", &x, &y, &z);
				input.push_back(x);
				input.push_back(y);
				input.push_back(z);
				v.push_back(input);
			}
			else if (line[0] == 'f') {
				line[0] = ' ';
				vector<int> tfv;
				vector<int> tfn;
				char * newstr = &line[1];
				while ((newstr = strtok(newstr, " ")) != NULL) {
					int tv, tn;
					if (sscanf(newstr, "%d//%d", &tv, &tn) == EOF) {
						newstr += strlen(newstr) + 1;
						continue;
					}
					tfv.push_back(tv);
					tfn.push_back(tn);
					newstr += strlen(newstr) + 1;
				}
				fv.push_back(tfv);
				fn.push_back(tfn);
				tfv.clear();
				tfn.clear();
			}
			i++;
		}

		for (unsigned int i = 0; i < fv.size() - 1; i++) {
			vector<int>& tfv = fv[i];
			vector<int>& tfn = fn[i];

			for (int inte : tfv) {
				originalVerticesPos.push_back(v[inte - 1][0]);
				originalVerticesPos.push_back(v[inte - 1][1]);
				originalVerticesPos.push_back(v[inte - 1][2]);
			}
		}
		currentVerticesPos.resize((int)(originalVerticesPos.size()));
		std::copy(originalVerticesPos.begin(), originalVerticesPos.end(), currentVerticesPos.begin());
		Scale(size[0]);
	}

	OBJLoader(string fname) : OBJLoader(fname.c_str()) {}

	OBJLoader(char * fname, float size[], float pos[], float rot[])  : OBJLoader(fname) {
		for (int i = 0; i < 3; i++) {
			this->size[i] = size[i];
			this->pos[i] = pos[i];
			this->rotation[i] = rot[i];
		}
		Scale(size);
		Move(pos);
		Rotate(rot);
	}
	OBJLoader(const char fname[], float size[], float pos[], float rot[]) : OBJLoader((char*)(&fname[0]), size, pos, rot) {}

	void Move(vector<float>& movement);
	void Move(float* movement);
	void Rotate(vector<float>& newRotation);
	void Rotate(float* newRotation);
	void Scale(vector<float>& newSize) {
		Scale(&newSize[0]);
	}
	void Scale(float newSize[]) {
		for (int i = 0; i < 3; i++) {
			size[i] = newSize[i];
		}

		for (unsigned int i = 0; i < currentVerticesPos.size() / 3 - 1; i++) {
			currentVerticesPos[i] *= size[0];
			currentVerticesPos[i + 1] *= size[1];
			currentVerticesPos[i + 2] *= size[2];
		}
	}
	void Scale(float newSize) {
		size[0] = newSize;
		size[1] = newSize;
		size[2] = newSize;
		for (float& f : currentVerticesPos)
			f *= newSize;
	}

	void Draw(GLuint posLoc) {
		for (unsigned int i = 0; i < currentVerticesPos.size()/9 - 1; i++) {
			glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, &currentVerticesPos[i * 9]);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 3);		// Draw the triangles
		}		
	}

	char * ToString() {
		return objName;
	}
	void SetColor(vector<float>& fragment);
	//���⼭�� ũ�� 4¥�� �迭�� ����Ͽ�, ��� ��ǥ�� ���ؼ� �����ϰ� ������� �ش�.
	void SetColor(GLint colorLoc, float* color) {
		glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, 0, color);	
	}

	//static methods
	static void MoveAll(vector<float> movement); 
	static void MoveAll(float* movement);
	static void RotateAll(vector<float> rotAngle);
	static void RotateAll(float* rotAngle);
	static void ScaleAll(vector<float> newSize);
	static void ScaleAll(float* newSize);
	static void ForEvery(void *func(OBJLoader& object));		//�����ϴ� ��� obj�鿡�� func�Լ��� ������
	static void AddNewObj(OBJLoader* newLoader) {
		OBJLoader::objs.push_back(newLoader);
	}

private:
	char objName[100];
	float size[3];
	float rotation[3];
	float pos[3];
	/////////////////////////
	vector<vector<float>> v;
	vector<vector<float>> vn;
	vector<vector<int>> fv;
	vector<vector<int>> fn;
	//�޸𸮸� ����ؼ� �� �༮���� ���� �о �� �Ľ��� �� �������ѹ�����.
	//�׳� readfile()�� ���κ����θ� ���� �ϴ� �͵� ���.
	////////////////////////
	vector<float> fragmentVec;
	vector<float> originalVerticesPos;	//readFile() �̿ܿ����� �ǵ���� �ȵ� ���Ͽ� ����� ���� �Ľ��Ͽ�, �������� ���� �⺻ ��ǥ��.
	vector<float> currentVerticesPos;

	//static field
	static vector<OBJLoader*> objs;
};
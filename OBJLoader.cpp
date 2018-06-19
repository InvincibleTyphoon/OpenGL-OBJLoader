//#pragma once
//#include "OBJLoader.h"
//
//OBJLoader::OBJLoader(char * fname) {
//	FILE * fptr = fopen(fname, "r");
//	char line[1000];
//	int i = 0;
//	while (!feof(fptr)) {
//		memset(line, 0, sizeof(line));
//		fgets(line, 1000, fptr);
//		//printf("%d: %s", i + 1,line);
//		if (line[0] == 'v' && line[1] == 'n') {
//			line[0] = ' ';
//			line[1] = ' ';
//			float x, y, z;
//			vector<float> input;
//			sscanf(line, "%f %f %f", &x, &y, &z);
//			input.push_back(x);
//			input.push_back(y);
//			input.push_back(z);
//			vn.push_back(input);
//		}
//		else if (line[0] == 'v') {
//			line[0] = ' ';
//			float x, y, z;
//			vector<float> input;
//			sscanf(line, "%f %f %f", &x, &y, &z);
//			input.push_back(x);
//			input.push_back(y);
//			input.push_back(z);
//			v.push_back(input);
//		}
//		else if (line[0] == 'f') {
//			line[0] = ' ';
//			vector<int> tfv;
//			vector<int> tfn;
//			char * newstr = &line[1];
//			while ((newstr = strtok(newstr, " ")) != NULL) {
//				int tv, tn;
//				if (sscanf(newstr, "%d//%d", &tv, &tn) == EOF) {
//					newstr += strlen(newstr) + 1;
//					continue;
//				}
//				tfv.push_back(tv);
//				tfn.push_back(tn);
//				newstr += strlen(newstr) + 1;
//			}
//			fv.push_back(tfv);
//			fn.push_back(tfn);
//			tfv.clear();
//			tfn.clear();
//		}
//		i++;
//	}
//	arrange();
//
//}
//OBJLoader::OBJLoader(const char fname[]) {
//
//}
//OBJLoader::OBJLoader(string fname) {
//
//}
//OBJLoader::OBJLoader(char * fname, float size[], float pos[], float rot[]) {
//
//}
//OBJLoader::OBJLoader(char fname[], float size[], float pos[], float rot[]) {
//
//}
//
//void OBJLoader::Move(vector<float>& movement) {
//
//}
//void OBJLoader::move(float* movement) {
//
//}
//void OBJLoader::Rotate(vector<float>& newRotation) {
//
//}
//void OBJLoader::rotate(float* newRotation) {
//
//}
//void OBJLoader::Scale(vector<float>& newSize) {
//
//}
//void OBJLoader::scale(float* newSize) {
//
//}
//void OBJLoader::Draw(GLuint posLoc) {
//
//}
//char * OBJLoader::ToString() {
//
//}
//void OBJLoader::SetColor(vector<float>& fragment) {
//
//}
//void OBJLoader::SetColor(float* fragment) {
//
//}
//
//								//static field
//void OBJLoader::MoveAll(vector<float> movement) {
//
//}
//void OBJLoader::MoveAll(float* movement) {
//
//}
//void OBJLoader::RotateAll(vector<float> rotAngle) {
//
//}
//void OBJLoader::MotateAll(float* rotAngle) {
//
//}
//void OBJLoader::ScaleAll(vector<float> newSize) {
//
//}
//void OBJLoader::scaleAll(float* newSize) {
//
//}
//void OBJLoader::ForEvery(void *func(OBJLoader& object)) {
//
//}
//void OBJLoader::AddNewObj() {
//
//}

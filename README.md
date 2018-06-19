# OpenGL- OBJLoader Class

Developed with visual studio 2017


How to use
```
1. Create object of OBJLoader class.
(You may need to give filename to constructer in this step)

2. Call OBJLoader::Draw() method in OpenGL display function
```



# OBJLoader.h

Class that used for load .OBJ format files.

API
```
// Constructors
// Object is loaded when class is created.
OBJLoader() //File name : DefaultName.OBJ. Set size, rotation, position as default.
OBJLoader(const char fname[]) : File name : fname , Set size, rotation, position as default.
OBJLoader(char * fname) : File name : fname, Set size, rotation, position as default.
OBJLoader(string fname) : File name : fname, Set size, rotation, position as default.
OBJLoader(char * fname, float size[], float pos[], float rot[]) : File name : fname, set size, position, rotation
OBJLoader(const char fname[], float size[], float pos[], float rot[]) : File name : fname, set size, position, rotation

//Move object
// Thes codes do not worl yet
void Move(vector<float>& movement)
void Move(float* movement)

//Rotate the object
// Thes codes do not worl yet
void Rotate(vector<float>& newRotation)
void Rotate(float* newRotation)

//Set size of object
// Thes codes do not worl yet
void Scale(vector<float>& newSize)
void Scale(float newSize[])
void Scale(float newSize)

// Draw the object.
// You may call this method in display function(the function set with glutDisplayFunc())
void Draw(GLuint posLoc)

// Returns object name
// Use for debug
char * ToString()

// Set color of the object
// This method will simply set color with one color
void SetColor(GLint colorLoc, float* color)

// Static methods
// Thes codes do not worl yet
static void MoveAll(vector<float> movement); 
static void MoveAll(float* movement);
static void RotateAll(vector<float> rotAngle);
static void RotateAll(float* rotAngle);
static void ScaleAll(vector<float> newSize);
static void ScaleAll(float* newSize);
static void ForEvery(void *func(OBJLoader& object));
static void AddNewObj(OBJLoader* newLoader);

```

# OBJLoaderClassExample.cpp

Example program

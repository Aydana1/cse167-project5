#pragma once
#include "Vector3.h"
#include "Color.h"
#include <vector>
using namespace std;

class ObjReader {

public:
	ObjReader();
	virtual ~ObjReader();
	static void readXYZ(char* fileName, vector<Vector3>& pos, vector<Vector3>& norm);
	static void readOBJ(char* fileName, int& numVerts, vector<Vector3>& vertices, vector<Color>& colors, vector<Vector3>& normals, int &numFaces, vector<int>& faces);
	static void readOBJ(char* fileName, int& numVerts, vector<Vector3>& vertices, vector<Vector3>& normals, int &numFaces, vector<int>& faces);

};


#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#pragma warning (disable : 4700)

#include "ObjReader.h"
#include <iostream>

ObjReader::ObjReader() {
}


ObjReader::~ObjReader() {
}


void ObjReader::readXYZ(char* fileName, vector<Vector3>& position, vector<Vector3>& normal) {

	// position coordinates
	float posX = 0.0, posY = 0.0, posZ = 0.0;
	// normal coordinates
	float normX = 0.0, normY = 0.0, normZ = 0.0;

	FILE* fp;

	// open file for reading
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error reading from file \"%s\". Please ensure it exists and try again.\n", fileName);
		cin.get();
		exit(1);
	} else {
		while (fscanf(fp, "%f %f %f %f %f %f", &posX, &posY, &posZ, &normX, &normY, &normZ) != EOF) {
			position.push_back(Vector3((double)posX, (double)posY, (double)posZ));
			normal.push_back(Vector3((double)normX, (double)normY, (double)normZ));
		}

		// close file
		fclose(fp);
	}
}

/* Reads an OBJ file that has colors specified*/
void ObjReader::readOBJ(char* fileName, int& numVerts, vector<Vector3>& vertices, vector<Color>& colors, vector<Vector3>& normals, int &numFaces, vector<int>& faces) {
	FILE *fp;		// file pointer
	float x, y, z;	// vertex coordinates
	float r, g, b;	// vertex color

	// open file for reading
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error reading from file \"%s\". Please ensure it exists and try again.\n", fileName);
		cin.get();
		exit(1);
	}

	int nv = 0;	// number of vertices
	int nn = 0; // number of normals
	int nf = 0; // number of faces

	char line[100];

	float l;

	// count vertices, normals, faces
	while (fgets(line, 99, fp) != NULL) {
		switch (line[0]) {
		case 'v':
			switch (line[1]) {
			case ' ': // vertex and color
				sscanf(&line[2], "%f %f %f %f %f %f\n", &x, &y, &z, &r, &g, &b);
				vertices.push_back(Vector3(x, y, z)); // add vertex
				colors.push_back(Color(r, g, b)); // add color
				nv++;
				break;
			case 'n': // normal
				sscanf(&line[2], " %f %f %f\n", &x, &y, &z);
				l = sqrt(x*x + y*y + z*z);
				normals.push_back(Vector3(x / l, y / l, z / l)); // add normal
				nn++;
				break;
			default: break;
			}
			break;
		case 'f': // face
			//char *c1, *c2, *c3;
			int v1, n1, v2, n2, v3, n3;
			sscanf(&line[1], " %d//%d %d//%d %d//%d\n", &v1, &n1, &v2, &n2, &v3, &n3);
			faces.push_back(v1); // add vertex & normal indices
			faces.push_back(n1);
			faces.push_back(v2);
			faces.push_back(n2);
			faces.push_back(v3);
			faces.push_back(n3);
			nf++;
			break;
		default: break;
		}
	}

	numVerts = nv;
	numFaces = nf;

	// close file
	fclose(fp);
}

/* Reads an OBJ file that doesn't have colors */
void ObjReader::readOBJ(char* fileName, int& numVerts, vector<Vector3>& vertices, vector<Vector3>& normals, int &numFaces, vector<int>& faces) {
	FILE *fp;		// file pointer
	float x, y, z;	// vertex coordinates

	// open file for reading
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error reading from file \"%s\". Please ensure it exists and try again.\n", fileName);
		cin.get();
		exit(1);
	}

	int nv = 0;	// number of vertices
	int nn = 0; // number of normals
	int nf = 0; // number of faces

	char line[100];
	float l;
	int i = 0;
	// count vertices, normals, faces
	while (fgets(line, 99, fp) != NULL) {
		//i++;
		//printf("%d\n", i);
		switch (line[0]) {
		case 'v':
			switch (line[1]) {
			case ' ': // vertex and color
				sscanf(&line[2], "%f %f %f\n", &x, &y, &z);
				vertices.push_back(Vector3(x, y, z)); // add vertex
				nv++;
				break;
			case 'n': // normal
				sscanf(&line[2], " %f %f %f\n", &x, &y, &z);
				l = sqrt(x*x + y*y + z*z);
				normals.push_back(Vector3(x / l, y / l, z / l)); // add normal
				nn++;
				break;
			default: break;
			}
			break;
		case 'f': // face
			//char *c1, *c2, *c3;
			int v1, n1, v2, n2, v3, n3;
			sscanf(&line[2], "%d//%d %d//%d %d//%d\n", &v1, &n1, &v2, &n2, &v3, &n3);
			faces.push_back(v1); // add vertex & normal indices
			faces.push_back(n1);
			faces.push_back(v2);
			faces.push_back(n2);
			faces.push_back(v3);
			faces.push_back(n3);
			nf++;
			break;
		default: break;
		}
	}

	numVerts = nv;
	numFaces = nf;

	// close file
	fclose(fp);
}
#pragma once
#include "Matrix4.h"
#include "Color.h"
#include "Material.h"
#include <vector>

using namespace std;

class ObjModel {
private:
	char *fileName; // path to file containing data for model

	int numVerts, numFaces;

	vector<Vector3> vertices;
	vector<Color> colors;
	vector<Vector3> normals;

	vector<int> faces;

	Matrix4 model2world;

	double minX, minY, minZ;
	double maxX, maxY, maxZ;
	double width, height;
	Vector3 center;

	bool visible;

	bool hasColors;

	void calcMinMax();
	void calcCenter();

	double radius;
	
	Material material;

public:
	ObjModel();
	ObjModel(char *name, bool hasColors);
	~ObjModel();

	void createFromFile(char *name, bool hasColors);

	void setVisible(bool v) { visible = v; }
	bool isVisible() { return visible; }

	int length();

	Vector3 getNorm(unsigned int index);
	Vector3 getVertex(unsigned int index);

	void makeScale(double s) { model2world.makeScale(s, s, s); }
	void makeScaleToFitWindow();

	Vector3& getCenter() { return center; }
	void setCenter(double x, double y, double z) { center.set(x, y, z); }

	Matrix4& getMatrix() { return model2world; }
	void setMatrix(Matrix4& m) { model2world = Matrix4(m); }

	void reset() { model2world.identity(); translateToOrigin(); makeScaleToFitWindow(); }
	void translateToOrigin();
	void render();

	void normalize();

	void setMaterial(Material& mat) { material = mat; }
};


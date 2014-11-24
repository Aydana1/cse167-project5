#include "ObjModel.h"
#include "ObjReader.h"
#include "Window.h"
#include "GL\glut.h"
#include <algorithm>

ObjModel::ObjModel() {
	
}

ObjModel::ObjModel(char *name, bool c) : fileName(name), hasColors(c) {
	createFromFile(name, c);
}


ObjModel::~ObjModel() {
}

void ObjModel::createFromFile(char *name, bool c) {
	printf("Loading %s ... ", name);
	fileName = name;
	hasColors = c;

	visible = false;
	numVerts = 0;
	numFaces = 0;
	vertices = vector<Vector3>();
	colors = vector<Color>();
	normals = vector<Vector3>();
	faces = vector<int>();
	if (hasColors) {
		ObjReader::readOBJ(fileName, numVerts, vertices, colors, normals, numFaces, faces);
	} else {
		ObjReader::readOBJ(fileName, numVerts, vertices, normals, numFaces, faces);
	}

	model2world = Matrix4();
	model2world.identity();

	normalize();
	makeScaleToFitWindow();
	printf("Done!\n");
}

Vector3 ObjModel::getNorm(unsigned int index) {
	if (index < 0 || index > normals.size()) return NULL;
	return normals.at(index);
}

Vector3 ObjModel::getVertex(unsigned int index) {
	if (index < 0 || index > vertices.size()) return NULL;
	return vertices.at(index);
}

void ObjModel::calcMinMax() {
	// Minimums
	minX = minY = minZ = 1024;
	// Maximums
	maxX = maxY = maxZ = -1024;

	for (vector<Vector3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		// X
		if (it->getX() < minX) minX = it->getX();
		if (it->getX() > maxX) maxX = it->getX();

		// Y
		if (it->getY() < minY) minY = it->getY();
		if (it->getY() > maxY) maxY = it->getY();

		// Z
		if (it->getZ() < minZ) minZ = it->getZ();
		if (it->getZ() > maxZ) maxZ = it->getZ();
	}
}

void ObjModel::calcCenter() {
	/*center = Vector3(((maxX - minX) / 2.0) + minX,
		((maxY - minY) / 2.0) + minY,
		((maxZ - minZ) / 2.0) + minZ);*/
	center = Vector3((maxX + minX) / 2.0, (maxY + minY) / 2.0, (maxZ + minZ) / 2.0);
}

void ObjModel::translateToOrigin() {
	Matrix4 tm = Matrix4(1.0, 0.0, 0.0, center.getX(),
		0.0, 1.0, 0.0, center.getY(),
		0.0, 0.0, 1.0, center.getZ(),
		0.0, 0.0, 0.0, 1.0);

	//tm.print("\nTranslation matrix:");

	model2world *= tm;

	for (vector<Vector3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		*it = tm * *it;
		//*it = *it - center;
	}
}

void ObjModel::makeScaleToFitWindow() {

	double theta = 30.0;
	theta = (theta / 180.0) * M_PI;
	double adj = 20.0;

	double op = adj * tan(theta);
	double windowWidth = op * 2.0;

	double scaleFactor = windowWidth / (maxX - minX);


	model2world.makeScale(scaleFactor,scaleFactor, 1.0);
	//model2world.makeTranslate(-center.getX(), -center.getY(), -center.getZ());
}

void ObjModel::render() {
	material.apply();
	int j;
	Matrix4 glMatrix = model2world;
	glMatrix.transpose();
	//glPushMatrix();
	glLoadMatrixd(glMatrix.getPointer());
	//glPopMatrix();
	glBegin(GL_TRIANGLES);
		
		for (int i = 0; i < numFaces * 6; i += 6) {
			j = i + 1;

			// color
			if (hasColors)
				glColor3f(colors[faces[i] - 1].getR(), colors[faces[i + 2] - 1].getG(), colors[faces[i + 4] - 1].getB());
			else
				glColor3f(0.6, 0.6, 0.6);
				//glColor3f(fabs(normals[faces[j]-1].getX()) * 0.8, fabs(normals[faces[j + 2]-1].getY()) * 0.8, fabs(normals[faces[j + 4]-1].getZ()) * 0.8);
			
			// Vertex 1
			glNormal3f(normals[faces[j]-1].getX(), normals[faces[j]-1].getY(), normals[faces[j]-1].getZ());
			glVertex3f(vertices[faces[i]-1].getX(), vertices[faces[i]-1].getY(), vertices[faces[i]-1].getZ());

			// Vertex 2
			glNormal3f(normals[faces[j + 2]-1].getX(), normals[faces[j + 2]-1].getY(), normals[faces[j + 2]-1].getZ());
			glVertex3f(vertices[faces[i + 2]-1].getX(), vertices[faces[i + 2]-1].getY(), vertices[faces[i + 2]-1].getZ());

			// Vertex 3
			glNormal3f(normals[faces[j + 4]-1].getX(), normals[faces[j + 4]-1].getY(), normals[faces[j + 4]-1].getZ());
			glVertex3f(vertices[faces[i + 4]-1].getX(), vertices[faces[i + 4]-1].getY(), vertices[faces[i + 4]-1].getZ());
		}
	glEnd();
}

void ObjModel::normalize() {
	
	// get old minimums and maximums
	calcMinMax();

	// get old midpoint
	double midx = (maxX - minX) / 2.0 + minX;
	double midy = (maxY - minY) / 2.0 + minY;
	double midz = (maxZ - minZ) / 2.0 + minZ;
	this->center = Vector3(midx, midy, midz);

	


	double scaleFactor = 1.0 / max(maxX - minX, max(maxY - minY, maxZ - minZ));

	minX = minY = minZ = 1024;
	maxX = maxY = maxZ = -1024;
	this->radius = 0.0;
	for (vector<Vector3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
		// scale
		it->set((it->getX() - midx)*scaleFactor, (it->getY() - midy)*scaleFactor, (it->getZ() - midz)*scaleFactor);
		// calc radius
		double d = sqrt(it->getX()*it->getX() + it->getY()*it->getY() + it->getZ()*it->getZ());
		if (d > this->radius) {
			this->radius = d;
		}

		// calc new minimums and maximums
		// X
		if (it->getX() < minX) minX = it->getX();
		if (it->getX() > maxX) maxX = it->getX();

		// Y
		if (it->getY() < minY) minY = it->getY();
		if (it->getY() > maxY) maxY = it->getY();

		// Z
		if (it->getZ() < minZ) minZ = it->getZ();
		if (it->getZ() > maxZ) maxZ = it->getZ();
	}
}

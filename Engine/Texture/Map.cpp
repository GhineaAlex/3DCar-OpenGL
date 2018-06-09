#define _CRT_SECURE_NO_DEPRECATE
#include "Map.h"

Map::Map() {
	color = Vector3D(0.15, 0.15, 0.15);
	lastHitX = 0;
	lastHitY = 0;

	readLevelData();
	buildLevel();
}

// Free up some memory
Map::~Map() {
	for (int i = 0; i < levelSize; i++)
		free(levelData[i]);
	free(levelData);
}

void Map::Draw() {

	glPushMatrix();

	glColor3f(color.x, color.y, color.z);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (Vector4D(color.x, color.y, color.z, 1)).Array());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (Vector4D(0.1, 0.1, 0.1, 1)).Array());
	// Render level map
	glCallList(level);

	glPopMatrix();

}

bool Map::checkCollision(Car *car) {

	return false;
}

// Read level configuration from file
void Map::readLevelData() {

}

void Map::buildLevel() {
	level = glGenLists(1);
	glNewList(level, GL_COMPILE);
	

	glPushMatrix();
	glTranslatef(-17, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-15, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-11, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-9, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-7, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-5, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2, 0.1, 3);
	glRotatef(90, 1, 0, 0);
	glutSolidTorus(0.15, 0.35, 10, 10);
	glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(5, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(7, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(9, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(11, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(13, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(15, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(17, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(19, 0.1, 3);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();


	
	glEndList();
	
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
}
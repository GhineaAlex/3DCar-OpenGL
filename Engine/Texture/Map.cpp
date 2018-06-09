// "Map" class loads level data from a file
// and renders it on the screen.
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

float distance(float x, float y, float cx, float cy) {
	return sqrt(pow(cx - x, 2) + pow(cy - y, 2));
}

// Overly simplistic (and expensive) collision detection
// First checks if it's close enough to an object and then
// it checks if any of the car parts (front, center, back)
// collides with the object.
bool Map::checkCollision(Car *car) {

	return false;
}

// Read level configuration from file
void Map::readLevelData() {

}

// Generate level display list
void Map::buildLevel() {
	level = glGenLists(1);
	glNewList(level, GL_COMPILE);

	// Represent level object as solid torus (like a tire)
		glPushMatrix();
		//glTranslatef(levelData[i][0], 0.1, levelData[i][1]);
		glRotatef(90, 1, 0, 0);
		glutSolidTorus(0.15, 0.35, 10, 10);
		glPopMatrix();
	
	glEndList();
}
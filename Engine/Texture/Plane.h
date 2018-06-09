#ifndef PLANE_H
#define PLANE_H

#include <gl/freeglut.h>
#include "../Mate/Object3D.h"


class Plane : public Object3D
{

private:
	float size;
	GLuint planeList;
	//GLuint skybox[1];

public:
	Plane(float _size);
public:
	void customDraw();
};

#endif

#ifndef CAMERA_H
#define CAMERA_H

#include <gl/freeglut.h>
#include "../Car/Car.h"
#include "../Mate/Object3D.h"
#include "../Mate/Vector3D.h"

class Camera
{

private:
	Vector3D ForwardVector;
	Vector3D RightVector;
	Vector3D UpVector;
	Vector3D Position;

public:

	Vector3D rotation; // get setter
	Camera();
	void Render(void);

	// rotatia relativa pe axe
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);

	//rotatie relativa la un pct
	void RotateXCenter(GLfloat Angle, float distance);
	void RotateYCenter(GLfloat Angle, float distance);
	void RotateZCenter(GLfloat Angle, float distance);

	//miscare basic
	void MoveForward(GLfloat Distance);
	void MoveBackward(GLfloat Distance);
	void MoveUpward(GLfloat Distance);
	void MoveDownward(GLfloat Distance);
	void MoveRight(GLfloat Distance);
	void MoveLeft(GLfloat Distance);


	void SetPosition(Vector3D *value);
	void SetForwardVector(Vector3D *value);
	void SetRightVector(Vector3D *value);
	void SetUpVector(Vector3D *value);

	Vector3D GetPosition();
};

#endif

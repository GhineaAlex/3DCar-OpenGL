
#ifndef MAIN_H_
#define MAIN_H_

#include "../Masina/Engine/Car/Car.h"
#include "../Masina/Engine/Camera/CameraSet.h"
#include "../Masina/Engine/Spatiu/World.h"
#include "../Masina/Engine/Mate/Vector3D.h"
#include "../Masina/Engine/Mate/Vector4D.h"


#define ESC	27
#define PI 3.14159265

float *Vector3D::arr;
float *Vector4D::arr;

// Camera control

#define NOSECAMERA 2
#define CAMSPEED 1.5 * PI / 180
int oldX, oldY;

// Car control
int steering = 0;
int leftPressed = 0, rightPressed = 0, upPressed = 0, downPressed = 0; // Keyboard presses

bool onStart = false;
int startTime, prevTime;




#endif /* MAIN_H_ */

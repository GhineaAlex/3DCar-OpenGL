#ifndef CAMERASET_H_
#define CAMERASET_H_

#include "Camera.h"
#include "../Mate/Object3D.h"
#include "../Car/Car.h"

#define NORMAL 1
#define FREE 0
class CameraSet {

private:
	int activeCamera;
	Camera *cameras[2];
	Car *car;

public:
	CameraSet(Car *);
	virtual ~CameraSet();
	void nextCamera();
	bool isFreeCamActive();
	int getCameraType();
	void update();
	void updateFreeCam(int);
	void render();
	Camera* getFreeCam();
	Vector3D getPosition();

};

#endif /* CAMERASET_H_ */

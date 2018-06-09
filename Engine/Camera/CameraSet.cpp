// "CameraSet" handles 4 different "Camera" objects

#include "Camera.h"
#include "CameraSet.h"
CameraSet::CameraSet(Car *bindedCar) {
	car = bindedCar; // Camera system follows a car

					
	cameras[NORMAL] = new Camera();
	cameras[NORMAL]->SetPosition(new Vector3D(car->GetPosition().x, car->GetPosition().y, car->GetPosition().z));
	cameras[NORMAL]->MoveBackward(4.5);
	cameras[NORMAL]->MoveUpward(5);
	cameras[NORMAL]->RotateX(-35 * 3.1415 / 180);


	activeCamera = NORMAL;
}

CameraSet::~CameraSet() {
	delete[] & cameras;
}

void CameraSet::render() {
	cameras[activeCamera]->Render();
}

void CameraSet::update() {
	
		// un mic delay
		float newRot = (car->GetRotation().y * 3.1415 / 180 + cameras[NORMAL]->rotation.y) / 8;
		cameras[NORMAL]->RotateX(35 * 3.1415 / 180);
		cameras[NORMAL]->SetPosition(new Vector3D(car->GetPosition().x, car->GetPosition().y, car->GetPosition().z)); //preia pozitia masinii
		cameras[NORMAL]->RotateY(-newRot);
		cameras[NORMAL]->MoveBackward(4);
		cameras[NORMAL]->MoveUpward(5);
		cameras[NORMAL]->RotateX(-35 * 3.1415 / 180);
		cameras[NORMAL]->rotation.y -= newRot;
}

// We move the free camera.
void CameraSet::updateFreeCam(int key) {

}
void CameraSet::nextCamera() {
	if (++activeCamera > 3)
		activeCamera = 0;
}

bool CameraSet::isFreeCamActive() {
	return (activeCamera == FREE);
}

int CameraSet::getCameraType() {
	return activeCamera;
}

Camera* CameraSet::getFreeCam() {
	return cameras[FREE];
}

Vector3D CameraSet::getPosition() {
	return cameras[activeCamera]->GetPosition();
}
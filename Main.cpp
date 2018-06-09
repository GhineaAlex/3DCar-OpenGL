#include <stdlib.h>
#include <gl/freeglut.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>

#include "Main.h"

CameraSet *cameraSet;
Car *car;
World *world;
#define	checkImageWidth 16
#define	checkImageHeight 16
GLubyte image[3 * checkImageWidth*checkImageHeight];
GLfloat ctrlpoints[4][4][3] = {
	{ { -2.5, -2.5, 5.0 },
{ -0.5, -2.5, 2.0 },
{ 0.5, -2.5, -1.0 },
{ 1.5, -2.5, 2.0 } },
{ { -2.5, -0.5, 1.0 },
{ -0.5, -0.5, 3.0 },
{ 0.5, -0.5, 0.0 },
{ 1.5, -0.5, -1.0 } },
{ { -1.5, 5.5, 5.0 },
{ -0.5, 2.5, 0.0 },
{ 0.5, 2.5, 3.0 },
{ 1.5, 2.5, 4.0 } },
{ { -1.5, 7.5, -2.0 },
{ -0.5, 4.5, -2.0 },
{ 0.5, 4.5, 0.0 },
{ 1.5, 4.5, -1.0 } }
};
GLfloat texpts[2][2][2] = { { { 0.0, 0.0 },{ 0.0, 1.0 } },
{ { 1.0, 0.0 },{ 1.0, 1.0 } } };
// Generate level display list

void makeBezier(void) {
	for (int row = 0; row < checkImageWidth; row++) {
		for (int col = 0; col < checkImageHeight; col++) {

			image[3 * (checkImageHeight*row + col)] = 255;
			image[3 * (checkImageHeight*row + col) + 1] = 255;
			image[3 * (checkImageHeight*row + col) + 2] = 255;
		}
	}
}
void loadBezier() {

	glClearColor(0.99, 0.9, 1.0, 0.0);
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
		0, 1, 12, 4, &ctrlpoints[0][0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2,
		0, 1, 4, 2, &texpts[0][0][0]);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glEnable(GL_MAP2_VERTEX_3);
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	makeBezier();
	glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth, checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);  // Create texture from image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_TEXTURE_2D);  // Enable 2D texture 
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
void init(void) {
	Vector3D::arr = new float[3];
	Vector4D::arr = new float[4];

	car = new Car();
	cameraSet = new CameraSet(car); // Bind the camera system to our car
	world = new World();

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	loadBezier();

}
enum {
	SPHERE = 1, CONE, LIGHT, LEFTWALL, FLOOR
};
void drawScene() {
	world->draw();
	// If NOSECAMERA is active don't render car model
	car->Draw(1);
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
}
void cone(void)
{
	glPushMatrix();
	glTranslatef(-40.f, -40.f, -400.f);
	glCallList(CONE);
	glPopMatrix();

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cameraSet->render(); // Places the observer
	world->renderLight(); // Global light

	world->setSkyboxPosition(&(car->GetPosition())); // Skybox follows the car 

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1);
	drawScene(); // opac

	GLfloat floorshadow[4][4];
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(0.f, 0.f, 0.f);  /* shadow color */

	glPushMatrix();
	glMultMatrixf((GLfloat *)floorshadow);
	cone();
	glPopMatrix();



	glAlphaFunc(GL_LESS, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	drawScene(); //transparent
	glDisable(GL_BLEND);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


	glStencilFunc(GL_EQUAL, 1, 1);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(0.f, 0.f, 0.f);  /* shadow color */
	glDisable(GL_DEPTH_TEST);
	glPushMatrix();
	//glMultMatrixf((GLfloat *)leftwallshadow);
	cone();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);



	glutSwapBuffers();
	glutPostRedisplay();
}

void update(int value) {

	glutTimerFunc(5, update, 0);

	// Measure the elapsed time
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	int timeSincePrevFrame = currTime - prevTime;


	steering = 0;
	// Do we need to steer?
	if (rightPressed) steering = 1;
	if (leftPressed) steering = -1;

	// Car speed/position update
	car->update(steering, upPressed, downPressed);

	// Camera update
	cameraSet->update();

	
	prevTime = currTime;

	glutPostRedisplay();
}

// When the window is resized we update the projection
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, aspect, 1.0, 60);
}

// Special keyboard presses
void keyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		rightPressed = 1;
		break;
	case GLUT_KEY_LEFT:
		leftPressed = 1;
		break;
	case GLUT_KEY_DOWN:
		downPressed = 1;
		break;
	case GLUT_KEY_UP:
		upPressed = 1;
		break;
	}
}

// Special keyboard releases
void keyboardUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		rightPressed = 0;
		break;
	case GLUT_KEY_LEFT:
		leftPressed = 0;
		break;
	case GLUT_KEY_DOWN:
		downPressed = 0;
		break;
	case GLUT_KEY_UP:
		upPressed = 0;
		break;
	}
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB| GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Masina");
	init();
	glutTimerFunc(5, update, 0);
	startTime = glutGet(GLUT_ELAPSED_TIME);
	prevTime = startTime;
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//utKeyboardFunc(keyboard);
	glutSpecialFunc(keyboard);
	glutSpecialUpFunc(keyboardUp);
	//utMotionFunc(freecam);
	glutMainLoop();
	return 0;
}

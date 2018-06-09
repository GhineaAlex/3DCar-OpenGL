#include "Car.h"

// far
float leftHeadlightPos[] = { -2, 0.1, -5, 1.0 };
float rightHeadlightPos[] = { 2, 0.1, -5, 1.0 };
float headlightAmbient[] = { 0, 0, 0, 0 };
float headlightDiffuse[] = { 3.5, 3.5, 3.5, 1.0 };
float headlightSpecular[] = { 1, 1, 1, 1.0 };
float headlightDirection[] = { 0, -1.05, -1 }; // Usor incliant

Car::Car() {
	SetColor(new Vector3D(0.3, 0.3, 0.5));
	SetPosition(new Vector3D(-5, 0, 7.5));
	SetRotation(new Vector3D(0, -90, 0));
	scale = Vector3D(1.0, 1.0, 1.0);
	velocity = 0;

	buildCar();
}

void Car::Draw(int showCar) {

	glPushMatrix();

	glTranslatef(translation.x,translation.y, translation.z);

	glRotatef(rotation.x, 1.0, 0.0, 0.0);
	glRotatef(rotation.y, 0.0, 1.0, 0.0);
	glRotatef(rotation.z, 0.0, 0.0, 1.0);

	glScalef(scale.x, scale.y, scale.z);

	glTranslatef(0, 0.45, 0);

	glScalef(0.35, 0.35, 0.35);
	glScalef(0.7, 0.7, 0.7);

	if (showCar != 0) {
		glCallList(carList + 3);
		// far
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (Vector4D(4, 4, 4, 0.5)).Array());
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (Vector4D(3, 3, 3, 0.5)).Array());
		glCallList(carList + 4);
		// geam
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (Vector4D(0.6, 0.6, 1, 0.5)).Array());
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (Vector4D(0.1, 0.1, 0.1, 0.5)).Array());
		glCallList(carList + 1);
		// roti
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (Vector4D(0.1, 0.1, 0.1, 1)).Array());
		glCallList(carList + 2);
		// struct
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (Vector4D(0.1, 0.1, 0.1, 1)).Array());
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (Vector4D(0.5, 0.5, 0.5, 1)).Array());
		glCallList(carList);
	}

	// Headlight spotlights
	glLightfv(GL_LIGHT1, GL_DIFFUSE, headlightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, leftHeadlightPos);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, headlightDirection);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 55);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 4.0);
	glEnable(GL_LIGHT1);

	glPopMatrix();
}

// car viteza si poz
void Car::update(int steeringInput, int acc, int brk) {
	float step = 0;

	

	// fara miscare
	if (!acc && !brk && velocity < 3 && velocity > -3)
		velocity = 0;

	if (velocity < 0)
		steeringInput *= -1; //spate

							 
	if (velocity != 0) {
		if (steeringInput == -1) {
			rotation.y += STEERANGLE; // stg
		}
		else if (steeringInput == 1) {
			rotation.y -= STEERANGLE; // dr
		}
		else {
			//fara
		}
	}

	if (acc) // acc
	{
		velocity += FORWARDACC;
		// limit viteza
		if (velocity > MAXVEL)
			velocity = MAXVEL;
	}
	if (brk)
	{
		//oprit
		if (velocity > 0) {
			velocity -= BRKPOWER;
			
			
		}
		else {
			velocity -= REVERSEACC;
			
		}
		//limit viteza
		if (velocity < MAXNVEL)
			velocity = MAXNVEL;

	}
	//directia vectorului bazat pe rotatia data de la tastatura
	direction.x = sin(rotation.y * PI / 180);
	direction.z = cos(rotation.y * PI / 180);

	step = -velocity / 100;
	// miscare
	SetPosition(&(GetPosition() + Vector3D(step* direction.x, 0, step*direction.z)));

	
	velocity *= DRAG;
}
void Car::hasCollided() {
	translation.x = lastSafePos.x;
	translation.z = lastSafePos.z;
	translation.y = lastSafePos.y;
}

// mai incet
void Car::slow() {
	velocity *= 0.5;
}

void Car::buildCar() {
	carList = glGenLists(5);

	glNewList(carList, GL_COMPILE);
	// Roof
	glTranslatef(0, 1, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 0, -1);
	glVertex3f(1, 0, -1);
	glEnd();
	glTranslatef(0, -1, 0);

	// Floor
	glTranslatef(0, -1, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 0, 3);
	glVertex3f(-1, 0, 3);
	glVertex3f(-1, 0, -3);
	glVertex3f(1, 0, -3);
	glEnd();
	glTranslatef(0, 1, 0);

	// Hood
	glTranslatef(0, 0, -2);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 0, 0.2);
	glVertex3f(-1, 0, 0.2);
	glVertex3f(-1, 0, -1);
	glVertex3f(1, 0, -1);
	glEnd();
	glTranslatef(0, 0, 2);

	// Trunk
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 0, -2);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glVertex3f(1, 0, 0.2);
	glVertex3f(-1, 0, 0.2);
	glVertex3f(-1, 0, -1);
	glVertex3f(1, 0, -1);
	glEnd();
	glTranslatef(0, 0, 2);
	glRotatef(180, 0, 1, 0);

	// Middle right side
	glTranslatef(1, -0.5, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, 0.5, 0);

	// Front right side
	glTranslatef(1, -0.5, -2);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, 0.5, 2);

	// Back right side
	glTranslatef(1, -0.5, 2);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, 0.5, -2);

	glRotatef(180, 0, 1, 0);

	// Middle left side
	glTranslatef(1, -0.5, 2);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, 0.5, -2);

	// Front left side
	glTranslatef(1, -0.5, -2);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, 0.5, 2);

	// Back left side
	glTranslatef(1, -0.5, 2);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, 0.5, -2);

	glRotatef(-180, 0, 1, 0);

	// Front piece
	glTranslatef(0, -0.5, -3);
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(0, 0.5, 3);

	// Back piece


	glEndList();

	// WINDOWS
	glNewList(carList + 1, GL_COMPILE);

	// Left
	glTranslatef(-1, 0.5, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(1, -0.5, 0);

	// Right
	glTranslatef(1, 0.5, 0);
	glRotatef(90, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0, 1);
	glVertex3f(-0.5, 0, 1);
	glVertex3f(-0.5, 0, -1);
	glVertex3f(0.5, 0, -1);
	glEnd();
	glRotatef(-90, 0, 0, 1);
	glTranslatef(-1, -0.5, 0);

	// Windscreen
	glTranslatef(0, 1, -1);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, -1);

	glVertex3f(1, 0, 0);
	glVertex3f(-1, 0, 0);
	glVertex3f(-1, -1, -0.8);
	glVertex3f(1, -1, -0.8);
	glEnd();
	glTranslatef(0, -1, 1);

	// Rear window
		glEndList();

	// WHEELS

	glNewList(carList + 2, GL_COMPILE);

	glTranslatef(-1.2, -0.75, -2);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.8, 1.5, 15, 15);

	glRotatef(-90, 0, 1, 0);
	glScalef(1 / 0.25, 1 / 0.25, 1 / 0.25);
	glTranslatef(1.2, 0.75, 2);

	glTranslatef(1.2, -0.75, -2);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.8, 1.5, 15, 15);
	glRotatef(-90, 0, 1, 0);
	glScalef(1 / 0.25, 1 / 0.25, 1 / 0.25);
	glTranslatef(-1.2, 0.75, 2);

	glTranslatef(-1.2, -0.75, 2);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.8, 1.5, 15, 15);
	glRotatef(-90, 0, 1, 0);
	glScalef(1 / 0.25, 1 / 0.25, 1 / 0.25);
	glTranslatef(1.2, 0.75, -2);

	glTranslatef(1.2, -0.75, 2);
	glScalef(0.25, 0.25, 0.25);
	glRotatef(90, 0, 1, 0);
	glutSolidTorus(0.8, 1.5, 15, 15);
	glRotatef(-90, 0, 1, 0);
	glScalef(1 / 0.25, 1 / 0.25, 1 / 0.25);
	glTranslatef(-1.2, 0.75, -2);

	glEndList();

	GLuint startList;
	GLUquadricObj *qobj;
	// HEADLIGHTS
	glNewList(carList + 4, GL_COMPILE);

	glRotatef(180, 0, 1, 0);
	glTranslatef(0.5, -0.5, 3);
	glScalef(1, 0.5, 0.25);
	glutSolidCube(0.5);
	glScalef(1, 2, 1 / 0.25);
	glTranslatef(-0.5, 0.5, -3);
	glRotatef(180, 0, 1, 0);

	glRotatef(180, 0, 1, 0);
	glTranslatef(-0.5, -0.5, 3);
	glScalef(1, 0.5, 0.25);
	glutSolidCube(0.5);
	glScalef(1, 2, 4);
	glTranslatef(0.5, 0.5, -3);
	glRotatef(180, 0, 1, 0);
	startList = glGenLists(5);
	qobj = gluNewQuadric();
	// gluQuadricCallback(qobj, GLU_ERROR, errorCallback);

	gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(startList, GL_COMPILE);
	gluSphere(qobj, 1.75, 15, 10);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_FILL); /* flat shaded */
	gluQuadricNormals(qobj, GLU_FLAT);
	glNewList(startList + 1, GL_COMPILE);
	gluCylinder(qobj, 1.5, 0.3, 1.0, 15, 5);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
										 // gluQuadricOrientation (qobj, GLU_INSIDE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(startList + 4, GL_COMPILE);
	gluCylinder(qobj, 0.5, 0.3, 1.0, 15, 5);
	glEndList();


	gluQuadricDrawStyle(qobj, GLU_LINE); /* all polygons wireframe */
	gluQuadricNormals(qobj, GLU_NONE);
	glNewList(startList + 2, GL_COMPILE);
	gluDisk(qobj, 0.25, 1.0, 20, 4);
	glEndList();

	gluQuadricDrawStyle(qobj, GLU_SILHOUETTE); /* boundary only  */
	gluQuadricNormals(qobj, GLU_NONE);
	glNewList(startList + 3, GL_COMPILE);
	gluPartialDisk(qobj, 0.0, 1.0, 20, 4, 0.0, 225.0);
	glEndList();
	glEndList();
}


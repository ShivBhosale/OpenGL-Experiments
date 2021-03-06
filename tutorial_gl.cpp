#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
#include <math.h>

// my globals go here

// movement parameters
float rad = 0.2828f, theta = M_PI;
float time_sys = 0.0f, inital_velocity = 0.1f, step = 2.0f;
float cylinder_top =0.0;

bool inJump = false;

float angle = 0.0f;
float height = 0.0f, summ = 0.0f;

GLUquadric* qobj;
//--------------------------------------------

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void draw_ground(){
	//y
	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 1.0, 0.0);

	for(float tile = -1.0; tile <= 1.0; tile += 0.1){
		//z
		glColor3d(0.0, 1.0, 0.0);
		glVertex3d(tile, 0.0, -1.0);
		glVertex3d(tile, 0.0, 1.0);

		//x
		glVertex3d(-1.0, 0.0, tile);
		glVertex3d(1.0, 0.0, tile);

	}

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.001f,10,10);

}

void draw_ball(float height){

	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(-rad*cos(theta), height , rad*sin(theta));
	glutSolidSphere(0.05f,10,10);

	
}

void draw_pillar(float top){

	//draw cylinder
	glColor3d(1.0, 0.0, 0.0);
	glRotatef(-90.0, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.0, 0.0 , top);
	gluCylinder(qobj, 0.2, 0.2, 1.4, 32, 32);


	glTranslatef(0.0, 0.0 , -top);

	//reset the co ordinate system
	glRotatef(90.0, 1.0f, 0.0f, 0.0f);

}

void processSpecialKeys(int key, int x, int y) {

    switch(key) {
        // case GLUT_KEY_LEFT :
        //         theta += 0.07;break;
        // case GLUT_KEY_RIGHT :
        //         theta -= 0.07; break;
        case GLUT_KEY_UP :
        	inJump = true;
        		// height
                break;
    }
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	double dist = sqrt(1 / 3.0);

	gluLookAt(dist, dist-0.3, dist,  /* position of camera */
          0.0,  0.0,  0.0,   /* where camera is pointing at */
          0.0,  1.0,  0.0);  /* which direction is up */
	
	glRotatef(angle, 0.0f, 1.0f, 0.0f);

	glBegin(GL_LINES);

	draw_ground();

	draw_pillar(cylinder_top);


	// un comment this one if you wann see the ball not move
	glRotatef(-angle, 0.0f, 1.0f, 0.0f);
	draw_ball(height);

	// theta += 0.005;
	if(inJump){
		// increment time
		time_sys += 1.0f;
		if(inital_velocity > 0.0 && time_sys <12.0){
			if ((int)time_sys % 2 == 1){
				height = height + inital_velocity;
				inital_velocity/=step;
			}
        }
        else if(inital_velocity <= 0.1 && time_sys <=24.0){
			if ((int)time_sys % 2 == 1){
				height = height - inital_velocity;
				inital_velocity*=step;
			}
        }
        else{
        	if (time_sys >= 25.0){
        		height = 0.0f;
        		time_sys = 0.0f;
        		inJump = false;
        		inital_velocity = 0.1f;
        	}
        }
	}


	glEnd();

	angle +=0.2f;
	// cylinder top
	cylinder_top -= 0.004f;
	// change speed later
	// height += 0.001f;

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	 qobj = gluNewQuadric();
  gluQuadricNormals(qobj, GLU_SMOOTH);

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(720,520);
	glutCreateWindow("Shiv ka game");
	// c un comment this to make it full screen
	//glutFullScreen();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//key events handles here
	glutSpecialFunc(processSpecialKeys);

	// enter GLUT event processing cycle
	glutMainLoop();
	gluDeleteQuadric(qobj);

	return 1;
}
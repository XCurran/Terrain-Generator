/*
This is the main file of Assignment 3 
for COMP SCI 3GC3
coded and created by Curran Tam (1231038) & Joseph Nguyen (1229287)
*/

//Imports/Includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>  
#include <cmath>
#include <ctime>
#include <time.h>


//Global variables
float camPos[] = {90, 60, 60}; //Initial camera viewpoint values
int mx = 50; //Initial terrain size
float terrain[300][300]; //Initial terrain 2D height-value array with max 300x300 size
int render = 1; //Integer boolean value for using fault algorithm to render
int framemode = 0; //Initial wireframe mode
int iterations = 0; //Initial number of iterations for fault algorithm
int togglelight = 1; //Initial lighting on


//Reset function 'R'
void reset() 
{

	camPos[0] = 90;
    camPos[1] = 60;
    camPos[2] = 60;
    mx = 50;
    render = 1;
    iterations = 0;

    for(int counter = 0; counter < mx; counter++)
    {
    	for(int counter2 = 0; counter2 < mx; counter2++)
    	{
    		terrain[counter2][counter] = 0;
    	}
    }

}

//Timer
void timer(int id)
{
    glutPostRedisplay();

}


//Keyboard controls
void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{

		case 'q': //Q - quit

		case 27:
			exit (0);
			break;

		case 'r':   
            reset();
            break;

        case 'w': //W - changing from frame mode to quad mode
        	if(framemode < 2)
        	{
        		framemode += 1;
        	}else{
        		framemode = 0;
        	}
        	break;

        case 'l': //L - turns light ON and OFF
        	if(togglelight == 1)
        	{

        		glDisable(GL_LIGHTING);
				glDisable(GL_LIGHT0);
				togglelight = 0;

        	}else if(togglelight == 0)
        	{

        		glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
				togglelight = 1;

        	}
        	break;

        //Z, C - improved camera controls
        case 'z':

        	float yrotrad;
			yrotrad = (360 / 180 * 3.141592654f);
			camPos[0] -= float(cos(yrotrad)) * 0.2;
			camPos[2] -= float(sin(yrotrad)) * 0.2;
        	break;

        case 's':
        	break;

        case 'x':
        	break;

        case 'c':

        	float yrotrad2;
			yrotrad = (360 / 180 * 3.141592654f);
			camPos[0] += float(cos(yrotrad2)) * 0.2;
			camPos[2] += float(sin(yrotrad2)) * 0.2;
        	break;

        default:
            break;

	}

}

//Initialization
void init(void)
{

	glClearColor(0, 0, 0, 0); //Sets backgorund to black
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65, 1.5, 1, 800);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat lightpos[] = {0, 50, 0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

}


//fault algorithm
void fault()
{

	float v = rand();
	float a = sin(v);
	float b = cos(v);
	float d = sqrt(25*25+25*25);
	float c = ((rand() / RAND_MAX)* d) - (d/2);
	int tx;
	int tz;
	float dispi = 0;
	float disp0 = 0.4;
	float dispn = 0.01;

	if(iterations < 400)
	{

		dispi = disp0 + (iterations / 400) * (dispn - disp0);

	}else
	{

		dispi = dispn;

	}

	for(int counter = 0; counter < mx; counter++)
	{
	   for(int counter2 = 0; counter2 < mx; counter2++)
	    {
	    	
	    	tx = counter + 25;
	    	tz = 25 + counter2;

	    	if((a * tx + b * tz - c) > 0)
	    	{

	    		terrain[counter2][counter] += dispi;

	    	}else
	    	{

	    		if(terrain[counter2][counter] != 0)
	    		{

	    			terrain[counter2][counter] -= dispi;

	    		}
	    	}
	    }
	}
}


//Shortcut for doing topographic coloring
void hypsometric (int xvalue, int zvalue)
{

	if(terrain[zvalue][xvalue] < 10)
	{
		glColor3f(0,1,0);
	}else if(terrain[zvalue][xvalue] < 20)
	{
		glColor3f(0.2,0.8,0);
	}else if(terrain[zvalue][xvalue] < 30)
	{
		glColor3f(0.4,0.6,0);
	}else if(terrain[zvalue][xvalue] < 40)
	{
		glColor3f(0.6,0.4,0);
	}else if(terrain[zvalue][xvalue] < 45)
	{
		glColor3f(0.8,0.2,0);
	}else
	{
		glColor3f(0.5,0.5,0.5);
	}

}


//Shortcut for drawing the grid
void grid(int counter2, int counter)
{

	if(counter2+1 >= 50 && counter +1 >= 50)
	{
		glNormal3d(0, 0, 1);	
		glVertex3f(1, terrain[counter2][counter], -1);
  		glVertex3f(1, terrain[counter2][counter], 1);
  		glVertex3f(-1, terrain[counter2][counter], 1);
 		glVertex3f(-1, terrain[counter2][counter],-1);

	}else if(counter + 1 >= 50)
	{
		glNormal3d(0, 0, 1);	
		glVertex3f(1, terrain[counter2+1][counter], -1);
	  	glVertex3f(1, terrain[counter2+1][counter], 1);
	  	glVertex3f(-1, terrain[counter2][counter], 1);
	 	glVertex3f(-1, terrain[counter2][counter],-1);
			
	}else if(counter2 + 1 >= 50)
	{
		glNormal3d(0, 0, 1);	
		glVertex3f(1, terrain[counter2][counter], -1);
  		glVertex3f(1, terrain[counter2][counter+1], 1);
  		glVertex3f(-1, terrain[counter2][counter+1], 1);
 		glVertex3f(-1, terrain[counter2][counter],-1);

	}else{
		glNormal3d(0, 0, 1);	
		glVertex3f(1, terrain[counter2+1][counter], -1);
	 	glVertex3f(1, terrain[counter2+1][counter+1], 1);
	  	glVertex3f(-1, terrain[counter2][counter+1], 1);
	 	glVertex3f(-1, terrain[counter2][counter],-1);
	}

}

//Display Function
//Drawing all the vertices and heightpoints
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_FLAT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0); //Sets camera viewpoint

	glutKeyboardFunc(keyboard); //Registers "keyboard" as the keyboard callback function

	if(render == 1)
	{
		while(iterations < 400) //Number of iterations
		{
			fault();
			iterations += 1;
		}
		
		render = 0;

	}


	for(int counter = 0; counter < mx; counter++)
	{

		glPushMatrix();
		glTranslatef(0, 0, counter);

		for(int counter2 = 0; counter2 < mx; counter2++)
		{

			if(framemode==0)
			{

				glBegin(GL_LINE_LOOP);
				hypsometric(counter2, counter);

			}else if(framemode==1)
			{

				glBegin(GL_QUADS);
				hypsometric(counter2, counter);

			}else
			{

				glBegin(GL_LINE_LOOP);
				glColor3f(0,0,1);

			}

			grid(counter2, counter);
			
	 		glEnd();
	 		glTranslatef(1,0,0);
		}

		glPopMatrix();

	}
	
	if(framemode == 2)
	{

		for(int counter = 0; counter < mx; counter++)
		{

			glPushMatrix();
			glTranslatef(0, 0, counter);

			for(int counter2 = 0; counter2 < mx; counter2++)
			{

				glBegin(GL_QUADS);

				hypsometric(counter2, counter);
				grid(counter2, counter);

		 		glEnd();
		 		glTranslatef(1,0,0);
			}

			glPopMatrix();

		}
	}

	glutSwapBuffers();
    glutTimerFunc(5,timer,0);

}



void idle()
{

}


void special(int key, int x, int y)
{

	//Camera movements controlled by arrow keys with set limitations
	switch(key)
	{

		case GLUT_KEY_LEFT:

			if(camPos[0]==160)
			{
				break;
			}else
			{
			camPos[0] += 10;
			camPos[2] -= 10;
			break;
			}
            
		case GLUT_KEY_RIGHT:

			if(camPos[2]==160)
			{
				break;
			}else
			{
			camPos[0] -= 10;
			camPos[2] += 10;
			break;
			}
            
		case GLUT_KEY_UP:
			if(camPos[1]==80)
			{
				break;
			}else
			{
			camPos[1] += 10;
			break;
			}
            
		case GLUT_KEY_DOWN:
			if(camPos[1]==0)
			{
				break;
			}else
			{
			camPos[1] -= 10;
			break;
			}
            
	}
	
}


void msgforTA()
{

	printf("\n-------------------------------\nTerrain Modeling by Curran Tam and Joseph Nguyen\n [1231038] and [1229287] \n-------------------------------\n [[HOTKEYS]]\n\nARROW KEYS = Viewpoint/Camera control\n\n[EXTRA FEATURE 1: Z / C = Cutscene-esque camera control]\n ^ Can be used with original arrow keys camera for better viewing. \n\nW = Wireframe mode toggle \n\n[EXTRA FEATURE 2: The third wireframe mode contains 'Hypsometric Tints' (Improved map coloring)]\n\nL = Lighting toggle\n\nR = Reset\n-------------------------------\n");

}

//Main Function
int main(int argc, char** argv)
{

	srand(time(0));

	glutInit(&argc, argv); //Starts up the GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(900, 600);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Terrain Modeling by Curran Tam and Joseph Nguyen");	//Creates the window

	glutSpecialFunc(special);	//Registers "specal" as the special keys callback function
	glutDisplayFunc(display);	//Registers "display" as the display callback function
	glutIdleFunc(idle);			//Regsters "idle" as the idle callback function
	init();

	glEnable(GL_DEPTH_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    msgforTA();

	glutMainLoop();				//Starts the event loop
    

	return(0);

}




#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include<windows.h>
#include <string>

//keyboard controls in game
void Key(int key, int x, int y);
//keyboard controls for starting/exiting the game
void processKeys(unsigned char key, int x, int y);
//drawing rectangle, giving it the starting point that is the left-down vertex, then giving it the width and height
void drawRect(int x, int y, int w, int h);
//draws the cat based on x an y and the radius
void drawCat(int x, int y, float r);
//draws a triangle to look like a salmon
void drawSalmon(int x, int h);
//printing function that takes the position of x and y and the string needed to be printed
void print(int x, int y, char* string);
//printing functions that takes position of x and y and the type of font and the string needed to be printed
void renderBitmapString(float x, float y, void* font, const char* string);
//three types of obstacles to dash between
void obstacle1(double x, double h);
void  obstacle3(double x, double h);
void obstacle2(double x, double h);
//timer function
void Timer(int value);

//fonts used
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

//powerup (salmon)
bool power = false;
//end of game
bool gameover = false;
//start of the game
bool start = false;
//whenever you take the salmon, the walls change color, according to the value of powercolor
float powercolor = 0;
int score = 0;
int scoref = 0;
//space where the cat starts
int startField = 50;
//number of hearts the cat gets
int hearts = 3;
//initial level
int level = 1;
//y-axis of the cat
double  cat = 300;

//printing functions that takes position of x and y and the type of font and the string needed to be printed
void renderBitmapString(float x, float y, void* font, const char* string) 
{
	const char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}
}
//drawing the obstacle1 with specified x position and height, since y will be a changing value
void  obstacle1(double x, double h)
{ 

	glColor3f(0.88, 0.82, 0.97);
	//bottom first obstacle
	drawRect(100 + x + startField, 0, 50, 150 + h);

	glColor3f(0.88, 0.82, 0.97);
	//top first obstacle
	drawRect(100 + x + startField, 300 + h, 50, 600);

	glColor3f(0.88, 0.82, 0.97);
	//bottom second obstacle
	drawRect(300 + x + startField, 0, 50, 200 + h);

	glColor3f(0.88, 0.82, 0.97);
	//top second obstacle
	drawRect(300 + x + startField, 350 + h, 50, 600);

	glColor3f(0.88, 0.82, 0.97);
	//bottom third obstacle
	drawRect(500 + x + startField, 0, 50, 250 + h);

	glColor3f(0.88, 0.82, 0.97);
	//top third obstacle
	drawRect(500 + x + startField, 400 + h, 50, 600);


	// the cat exceeded the window size, game over
	if (cat >= 580 || cat <= 20) 
	{
		hearts = 0;
	}
	//checking if the cat is in the first barrier's x position
	if (100 + x + startField <= 115 && 100 + x + startField >= 50)
	{
		//checking if the cat is in the first barrier's y position
		if (cat <= 160 || cat >= 280) 
		{
			//that means the cat got hit, decrease hearts and reposition the cat to be in between the barriers
			hearts--;
			cat = 220;
		}
	}
	//checking if the cat touched the second barrier's x position
	if (300 + x + startField <= 115 && 300 + x + startField >= 50) 
	{
		//checking if the cat is in the second barrier's y position
		if (cat <= 210 || cat >= 330) 
		{
			//that means the cat got hit, decrease hearts and reposition the cat to be in between the barriers
			hearts--;
			cat = 270;
		}
	}
	//checking if the cat touched the third barrier's x position
	if ((500 + x + startField <= 115 && 500 + x + startField >= 50)) 
	{
		//checking if the cat is in the third barrier's y position
		if (cat <= 260 || cat >= 380) 
		{  
			//that means the cat got hit, decrease hearts and reposition the cat to be in between the barriers
			hearts--;
			cat = 320;
		}
	}
}
void  obstacle2(double x, double h) 
{
	//the powercolor is used here to change the color of the obstacle based on whether the power is true or not
	//otherwise, everything is the same as obstacle1
	glColor3f(0.88 - powercolor, 0.82 - powercolor, 0.97 + powercolor);
	drawRect(100 + x + startField, 0, 50, 150 + h); //r11

	glColor3f(0.88 - powercolor, 0.82 - powercolor, 0.97 + powercolor);
	drawRect(100 + x + startField, 300 + h, 50, 600);//r12

	glColor3f(0.88 - powercolor, 0.82 - powercolor, 0.97 + powercolor);
	drawRect(300 + x + startField, 0, 50, 200 + h);//r21

	glColor3f(0.88 - powercolor, 0.82 - powercolor, 0.97 + powercolor);
	drawRect(300 + x + startField, 350 + h, 50, 600);//r22

	glColor3f(0.88 - powercolor, 0.82 - powercolor, 0.97 + powercolor);
	drawRect(500 + x + startField, 0, 50, 250 + h);//r31

	glColor3f(0.88 - powercolor, 0.82 - powercolor, 0.97 + powercolor);
	drawRect(500 + x + startField, 400 + h, 50, 600);//r32

	//if the cat touched the power
	if (120 + x + startField == 115) 
	{
		if (cat >= 115 && cat <= 180) 
		{
			power = true;
			powercolor = 0.5;
		}
	}
	//power is added here since if power is true, the walls disappear
	if (100 + x + startField <= 115 && 100 + x + startField >= 50 && power == false)
	{
		if (cat <= 120 || cat >= (240)) {
			hearts--;
			cat = 180;
		}
	}
	if (300 + x + startField <= 115 && 300 + x + startField >= 50 && power == false) 
	{
		if (cat <= 170 || cat >= (290)) 
		{
			hearts--;
			cat = 230;
		}
	}
	if (500 + x + startField <= 115 && 500 + x + startField >= 50 && power == false) 
	{
		if (cat <= 220 || cat >= (340)) 
		{
			hearts--;
			cat = 280;
		}
	}
	//once you exit, return the power to false
	if (600 + x + startField == 115 && power == true) 
	{
		power = false;
		powercolor = -0.5;
	}
}
void  obstacle3(double x, double h) 
{ 
	glColor3f(0.88, 0.82, 0.97);
	drawRect(100 + x + startField, 0, 50, 150 + h); 

	glColor3f(0.88, 0.82, 0.97);
	drawRect(100 + x + startField, 300 + h, 50, 600);

	glColor3f(0.88, 0.82, 0.97);
	drawRect(300 + x + startField, 0, 50, 200 + h);

	glColor3f(0.88, 0.82, 0.97);
	drawRect(300 + x + startField, 350 + h, 50, 600);

	glColor3f(0.88, 0.82, 0.97);
	drawRect(500 + x + startField, 0, 50, 250 + h);

	glColor3f(0.88, 0.82, 0.97);
	drawRect(500 + x + startField, 400 + h, 50, 600);

	if (100 + x + startField <= 115 && 100 + x + startField >= 50) 
	{
		if (cat <= 200 || cat >= (320)) 
		{
			hearts--;
			startField--;
			cat = 260;
		}
	}
	if (300 + x + startField <= 115 && 300 + x + startField >= 50) 
	{
		if (cat <= 250 || cat >= 370) 
		{
			hearts--;
			cat = 310;
		}
	}
	if (500 + x + startField <= 115 && 500 + x + startField >= 50) 
	{
		if (cat <= 300 || cat >= 420) 
		{
			hearts--;
			cat = 360;
		}
	}
	//once the cat reaches the end of the game, end the game
	//once the cat reaches 0 hearts, end the game
	if (score == 6000 || hearts < 1) 
	{
		gameover = true;
	}
}
void Key(int key, int x, int y)
{
	switch (key) 
	{
		//dash downwards
	case GLUT_KEY_DOWN:
		cat -= 15;
		break;
		//dash upwards
	case GLUT_KEY_UP:
		cat+=30;
		break;
	default:
		break;
	}
}
void processKeys(unsigned char key, int x, int y) {

	switch (key)
	{
		//if space if pressed and the start is false, change it to true
	case ' ':
		if (start == false) 
		{
			start = true;
		}
		break;
		//if esc is pressed, exit without errors
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}
void Menu() 
{
	//background
	drawCat(450, 300, 200);
	glColor3f(1.0, 0.25, 0.0);
	drawRect(250, 185, 400, 230);

	if (gameover == true) 
	{
		glColor3f(0.000, 0.000, 0.000);
		renderBitmapString(340, 390, (void*)font3, "GAME OVER");
		glColor3f(0.000, 0.000, 0.000);
		char buffer2[50];
		sprintf(buffer2, "Your Score is : %d", scoref);
		renderBitmapString(340, 380, (void*)font3, buffer2);
		level = scoref / 1000;
		sprintf(buffer2, "Your Level is : %d", level);
		renderBitmapString(340, 370, (void*)font3, buffer2);
	}
	//menu text
	glColor3f(0.5, 0.0, 1.0);
	renderBitmapString(340, 420, (void*)font1, "Dashing Cat Game");

	glColor3f(1.0, 1.0, 1.0);
	renderBitmapString(265, 350, (void*)font1, "Help the cat reach the end of its");
	renderBitmapString(265, 330, (void*)font1, "journey by successfully avoiding");
	renderBitmapString(265, 310, (void*)font1, "all obstacles, and collecting the fish!");

	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(265, 290, (void*)font2, "Press SPACE to START");
	renderBitmapString(265, 270, (void*)font2, "Press ESC to Exit");

	glColor3f(0.0, 0.0, 0.0);
	renderBitmapString(265, 250, (void*)font2, "Press UP to dash upwards");
	renderBitmapString(265, 230, (void*)font2, "Press DOWN to dash downwards");

	glColor3f(0.5, 0.0, 1.0);
	renderBitmapString(270, 210, (void*)font3, "Project By:");
	renderBitmapString(270, 200, (void*)font3, "Sara Ashraf");
}
//The Game
void startGame()
{
	if (hearts > 0 && gameover == false)
	{
		glPushMatrix();
		glColor3f(0.19, 0.46, 0.45);
		drawRect(0 + startField, 0, 800, 600);//background 1
		obstacle1(200, 0);//obstacle 1

		glColor3f(0.19, 0.46, 0.45);
		drawRect(750 + startField, 0, 800, 600);//background 2
		obstacle2(800, -40);//obstacle 2

		glColor3f(0.19, 0.46, 0.45);
		drawRect(1500 + startField, 0, 800, 600);//background 3
		if (power == false) {
			drawSalmon(905 + startField, 160);
		}
		obstacle3(1400, 40);//obstacle 3

		glColor3f(0.19, 0.46, 0.45);
		drawRect(2250 + startField, 0, 800, 600);//background 4
		obstacle1(2000, 40);//obstacle 4

		glColor3f(0.19, 0.46, 0.45);
		drawRect(3000 + startField, 0, 800, 600);//background 5
		obstacle2(2600, -40);//obstacle 5 

		glColor3f(0.19, 0.46, 0.45);
		drawRect(3200 + startField, 0, 800, 600);//background 6
		if (power == false) {
			drawSalmon(2705 + startField, 130);
		}
		obstacle3(3400, 40);//obstacle 6

		glColor3f(0.19, 0.46, 0.45);
		drawRect(3950 + startField, 0, 800, 600);//background 7
		obstacle1(4000, 40);//obstacle 7

		glColor3f(0.19, 0.46, 0.45);
		drawRect(4700 + startField, 0, 800, 600);//background 8
		obstacle2(4600, -40);//obstacle 8 

		glColor3f(0.19, 0.46, 0.45);
		drawRect(5450 + startField, 0, 800, 600);//background 9
		if (power == false) {
			drawSalmon(4505 + startField, 130);
		}
		obstacle3(5400, 40);//obstacle 9

		drawCat(100, cat, 15);
		glColor3f(0.5, 0.0, 1.0);

		//printing the score as you play
		char* p0s[20];
		sprintf((char*)p0s, "Score: %d", score);
		print(500, 500, (char*)p0s);
		if (score % 1000 == 0)
		{
			int last = score / 1000;
			if (last != level)
			{
				level = score / 1000;
			}
			glColor3f(0.5, 0.0, 1.0);
		}
		//printing the level as you keep finishing 1000 points of the score
		sprintf((char*)p0s, "Level: %d", level);
		print(650, 500, (char*)p0s);
		glColor3f(0.5, 0.0, 1.0);
		//prints hearts available
		sprintf((char*)p0s, "hearts: %d", hearts);
		print(800, 500, (char*)p0s);
		glPopMatrix();
	}
	else
	{
		scoref = score;
		gameover = true;
		start = false;
	}
}
void Display()
{
		glClear(GL_COLOR_BUFFER_BIT);

		if (start == true)
		{
			glClearColor(0.529, 0.8, 0.921, 1);
			startGame();
		}
		else if(start==false)
		{
			glClearColor(0.529, 0.8, 0.921, 1);
			Menu();
		}
		glFlush();
		glutSwapBuffers();
}
void drawRect(int x, int y, int w, int h)
{
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}
void drawSalmon(int x, int h) {

	glBegin(GL_TRIANGLES);
	glColor3f(0.98f, 0.5f, 0.44f);
	glVertex3f(10.0f + x, 5.0f + h, 0.0f);
	glColor3f(0.89f, 0.71f, 0.66f);
	glVertex3f(20.0f + x, 20.0f + h, 0.0f);
	glColor3f(0.98f, 0.5f, 0.44f);
	glVertex3f(30.0f + x, 5.0f + h, 0.0f);
	glEnd();
}
void drawCat(int x, int y, float r) 
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	float i;
	glColor3f(1.0, 0.75, 0.0);
	//face
	glBegin(GL_TRIANGLE_FAN);
	for (i = 0; i <= 360; i += 6)
	{
		glVertex2f(1.25*r * cos(i), r * sin(i));
	}
	glEnd();
	glBegin(GL_TRIANGLES);

	//Right ear
	glVertex2f(0*r, r);
	glColor3f(1.0, 0.75, 0.0);
	glVertex2f(r, -r*0.3);
	glColor3f(1.0, 0.25, 0.0);
	glVertex2f(r, 1.5*r);
	glColor3f(1.0, 0.75, 0.0);

	//Left ear
	glVertex2f(0 * r, r);
	glColor3f(1.0, 0.75, 0.0);
	glVertex2f(-r, r*0.3);
	glColor3f(1.0, 0.25, 0.0);
	glVertex2f(-r, 1.5*r);
	glColor3f(1.0, 0.75, 0.0);

	glEnd();
	glPopMatrix();
}
void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}
void Timer(int value)
{
	startField -= 1;
	score += 1;
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, Timer, 0);
}
int main(int argc, char** argr) 
{
	srand(time(NULL));
	glutInit(&argc, argr);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(900, 600);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Dashing Cat");
	glutDisplayFunc(Display);
	glutSpecialFunc(Key);
	glutKeyboardFunc(processKeys);

	gluOrtho2D(0.0, 900, 0.0, 600);
	glClearColor(0.184, 0.310, 0.310, 1); 
	glutTimerFunc(1000 / 60, Timer, 0);
	glutMainLoop();
	return 0;
}

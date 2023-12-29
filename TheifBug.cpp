//#include <GL/gl.h>
#include <stdlib.h>
#include <glut.h>
#include <ctime>
#include <iostream>
#include <windows.h>


#define Rows 21
#define Columns 21
#define Up 0
#define Down 1
#define Left 2
#define Right 3
#define Still 4

void display_callback();
void reshape_callback(int,int);
void timer_callback(int);
void gridinit(int, int);
void gridsquare(int, int);
void keyboard(int, int, int);
void player();
void collectables();
void obstacles();
void timepower();
void obstaclepower();
int generaterandom();

int gridx, gridy;
int playerx = 9, playery = 10;
short playerd = Still;
bool win = false;
bool gameover = false;
int collx, colly, collx2, colly2, collx3, colly3, collx4, colly4, collx5, colly5;
int obsx, obsx2, obsx3, obsx4, obsx5, obsy, obsy2, obsy3, obsy4, obsy5;
bool startcoll = true;
bool coll1 = false, coll2 = false, coll3 = false, coll4 = false, coll5 = false;
bool colll1 = false, colll2 = false, colll3 = false, colll4 = false, colll5 = false;

int score = 0;
int health = 5;
int seconds = 60;
bool timepower1 = false, obspower = false;
int tp1, tp2;
int op1, op2;
int demo = 0;
bool healthgameover = false;
short demoplayerd = Down;

void gridinit(int x, int y)
{
	gridx = x;
	gridy = y;
}

void gridsquare(int x, int y)
{
	if (x == 0 || y == 0 || y == gridy - 1 || x==gridx-1) {
		glLineWidth(2.0);
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x + 1, y);
		glVertex2f(x + 1, y + 1);
		glVertex2f(x, y + 1);
		glVertex2f(x + 1, y);
		glEnd();
	}
	else if (x == 1 && y == 1) {
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(4.0);
		
		glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 1.0);
		glLineWidth(1.0);
		glVertex2f(1.0, 1.0);
		glVertex2f(1.0, 2.0);
		glVertex2f(2.0, 2.0);
		glVertex2f(2.0, 1.0);
		glVertex2f(1.0, 1.0);
		glEnd();
		
		glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 1.0);
		glLineWidth(1.0);
		glVertex2f(1.3, 1.0);
		glVertex2f(1.3, 1.6);
		glVertex2f(1.8, 1.6);
		glVertex2f(1.8, 1.0);
		glVertex2f(1.3, 1.0);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.4, 0.6, 1.0);
		glVertex2f(1.0, 2.0);
		glVertex2f(1.5, 2.5);
		glVertex2f(2.0, 2.0);
		glEnd();

		if (seconds % 2 == 0)
		{
			glBegin(GL_LINE_LOOP);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2f(1.3, 1.0);
			glVertex2f(1.3, 2);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glColor3f(0.0, 0.0, 0.0);
			glVertex2f(1.7, 1.0);
			glVertex2f(1.7, 2);
			glEnd();
		}
		

	}
	//else {
		//glLineWidth(1.0);
		//glColor3f(1.0, 1.0, 1.0);
	//}
	
	

}

void generategrid()
{
	for (int i = 0; i < gridx; i++)
	{
		for (int j = 0; j < gridy; j++)
			gridsquare(i, j);
	}
}


void init()
{
	glClearColor(1.0, 1.0, 0.0, 1.0);
	gridinit(Columns, Rows);
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

void timer(int v) {
	if (!(gameover))
	{
		seconds--;
		if (seconds == 0) {
			gameover = true;
			std::cout << "Game Over" << std::endl;
		}
		glutTimerFunc(1000, timer, 0);
  }
}


void drawHealthBar() {
	// Draw the health bar background
	glColor3f(0.5, 0.5, 0.5); // Gray color
	glBegin(GL_QUADS);
	glVertex2f(0, 21); // Top-left corner
	glVertex2f(health, 21); // Top-right corner
	glVertex2f(health, 20); // Bottom-right corner
	glVertex2f(0, 20);
	glVertex2f(0, 21);// Bottom-left corner
	glEnd();

	
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(700, 500);
	glutCreateWindow("theifBug Game");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutTimerFunc(1000, timer, 0);
	glutSpecialFunc(keyboard);
	init();
	glutMainLoop();
	return 0;

}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	generategrid();
	char* p0s[20];
	sprintf((char*)p0s, "Score: %d", score);
	print(9, 20, (char*)p0s);
	sprintf((char*)p0s, "Health: %d", health);
	print(0, 20, (char*)p0s);
	sprintf((char*)p0s, "Timer: %d", seconds);
	print(18, 20, (char*)p0s);
	drawHealthBar();
	player();
	collectables();
	obstacles();
	timepower();
	obstaclepower();
	startcoll = false;
	if (win)
	{
		glColor3f(0.0, 1.0, 0.0);
		glRasterPos2i(150, 200);
		for (char c : "Timeout!")
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		if (demo == 0) {
			sprintf((char*)p0s, "You Win!, Score: %d", score);
			print(8, 10, (char*)p0s);
			
			glutSwapBuffers();
			
			
			demo++;
		}
	}
	else if (gameover)
	{
		glColor3f(1.0, 0.0, 0.0);
		glRasterPos2i(150, 200);
		for (char c : "Timeout!")
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
		if (demo == 0) {
			sprintf((char*)p0s, "Timeout!, Score: %d", score);
			print(8, 10, (char*)p0s);

			glutSwapBuffers();


			demo++;
		}
	}
	else if (healthgameover) {
		if (demo == 0) {
			glutSwapBuffers();
			glColor3f(1.0, 0.0, 0.0);
			sprintf((char*)p0s, "Health: %d", health);
			print(0, 20, (char*)p0s);
			glutSwapBuffers();
			demo++;
		}
	}
	else
       glutSwapBuffers();
	
}

void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, Columns, 0.0, Rows, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int x)
{
	glutPostRedisplay();
	glutTimerFunc(85, timer_callback, 0);
}

void keyboard(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		playerd = Up;
		break;
	case GLUT_KEY_DOWN:
		playerd = Down;
		break;
	case GLUT_KEY_LEFT:
		playerd = Left;
		break;
	case GLUT_KEY_RIGHT:
		playerd = Right;
		break;
	}
}


void scoredec(int v2) {
	score -= 10;
}
void player()
{
	if(playerd!=Still)
		demoplayerd = playerd;
	if (playerd == Up && playery != gridy - 2)
		playery++;
	else if (playerd == Down && playery != 1)
		playery--;
	else if (playerd == Left && playerx != 1)
		playerx--;
	else if (playerd == Right && playerx != gridx - 2)
		playerx++;
	
	if (playerd == Up && playery == gridy - 2)
		health--;
	else if (playerd == Down && playery == 1)
		health--;
	else if (playerd == Left && playerx == 1)
		health--;
	else if (playerd == Right && playerx == gridx - 2)
		health--;
	playerd = Still;
	
	
	if (playerx == 1 && playery == 1)
		win = true;
	
	
	if (playerx == collx && playery == colly && !(coll1)) {
		coll1 = true;
		score++;
	}
	else if (playerx == collx2 && playery == colly2 && !(coll2)) {
		coll2 = true;
		score++;
	}
	else if (playerx == collx3 && playery == colly3 && !(coll3)) {
		coll3 = true;
		score++;
	}
	else if (playerx == collx4 && playery == colly4 && !(coll4)) {
		coll4 = true;
		score++;
	}
	else if (playerx == collx5 && playery == colly5 && !(coll5)) {
		coll5 = true;
		score++;
	}
	
	if (playerx == obsx && playery == obsy && health > 0 && !(colll1)) {
		health--;
		colll1 = true;
	}
	else if (playerx == obsx2 && playery == obsy2 && health > 0 && !(colll2)) {
		health--;
		colll2 = true;
	}
	else if (playerx == obsx3 && playery == obsy3 && health > 0 && !(colll3)) {
		health--;
		colll3 = true;
	}
	else if (playerx == obsx4 && playery == obsy4 && health > 0 && !(colll4)) {
		health--;
		colll4 = true;
	}
	else if (playerx == obsx5 && playery == obsy5 && health > 0 && !(colll5)) {
		health--;
		colll5 = true;
	}
	if (health == 0)
		healthgameover = true;

	if (playerx == tp1 && playery == tp2 && !(timepower1))
	{
		seconds += 15;
		timepower1 = true;
	}

	if (playerx == op1 && playery == op2 && !(obspower))
	{
		score += 10;
		obspower = true;
		glutTimerFunc(3000, scoredec, 0);
	}
	glColor3f(0.0, 0.0, 0.0);
	glRectd(playerx, playery, playerx + 1, playery + 1);
	if (demoplayerd == Down)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(playerx + 0.5, playery);
		glVertex2f(playerx + 0.5, playery - 0.75);
		//glLineWidth(2.0);
		glEnd();
		glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
		glColor3f(1.0f, 1.0f, 1.0f); // Blue
		glVertex2f(playerx, playery);
		glVertex2f(playerx + 0.5, playery);
		glVertex2f(playerx + 0.25, playery + 0.3);

		glVertex2f(playerx + 0.5, playery);
		glVertex2f(playerx + 1, playery);
		glVertex2f(playerx + 0.75, playery + 0.3);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(playerx + 0.5, playery + 1);
		glVertex2f(playerx + 0.8, playery + 1.6);
		glVertex2f(playerx + 0.65, playery + 1.7);

		glVertex2f(playerx + 0.5, playery + 1.5);
		glVertex2f(playerx + 0.3, playery + 1.6);
		glVertex2f(playerx, playery + 1.3);
		glEnd();
	}

	else if (demoplayerd == Up)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(playerx + 0.5, playery+1);
		glVertex2f(playerx + 0.5, playery + 1.75);
		//glLineWidth(2.0);
		glEnd();
		glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
		glColor3f(1.0f, 1.0f, 1.0f); // Blue
		glVertex2f(playerx, playery+1);
		glVertex2f(playerx + 0.5, playery+1);
		glVertex2f(playerx + 0.25, playery + 0.7);

		glVertex2f(playerx + 0.5, playery+1);
		glVertex2f(playerx + 1, playery+1);
		glVertex2f(playerx + 0.75, playery + 0.7);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(playerx + 0.5, playery);
		glVertex2f(playerx + 0.8, playery - 0.6);
		glVertex2f(playerx + 0.65, playery - 0.7);

		glVertex2f(playerx + 0.5, playery - 0.5);
		glVertex2f(playerx + 0.3, playery - 0.6);
		glVertex2f(playerx, playery - 0.3);
		glEnd();
	}
	else if (demoplayerd == Left)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(playerx , playery+0.5);
		glVertex2f(playerx - 0.75, playery + 0.5);
		//glLineWidth(2.0);
		glEnd();
		glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
		glColor3f(1.0f, 1.0f, 1.0f); // Blue
		glVertex2f(playerx, playery);
		glVertex2f(playerx + 0.3, playery+0.25);
		glVertex2f(playerx, playery + 0.5);

		glVertex2f(playerx , playery+0.5);
		glVertex2f(playerx , playery+1);
		glVertex2f(playerx + 0.3, playery + 0.75);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(playerx + 1, playery + 0.5);
		glVertex2f(playerx + 1.6, playery + 0.8);
		glVertex2f(playerx + 1.7, playery + 0.65);

		glVertex2f(playerx + 1.5, playery + 0.5);
		glVertex2f(playerx + 1.6, playery + 0.3);
		glVertex2f(playerx+1.3, playery);
		glEnd();
	}
	else if (demoplayerd == Right)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(playerx+1, playery + 0.5);
		glVertex2f(playerx + 1.75, playery + 0.5);
		//glLineWidth(2.0);
		glEnd();
		glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
		glColor3f(1.0f, 1.0f, 1.0f); // Blue
		glVertex2f(playerx+1, playery);
		glVertex2f(playerx + 0.7, playery + 0.25);
		glVertex2f(playerx+1, playery + 0.5);

		glVertex2f(playerx+1, playery + 0.5);
		glVertex2f(playerx+1, playery + 1);
		glVertex2f(playerx + 0.7, playery + 0.75);
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(playerx , playery + 0.5);
		glVertex2f(playerx + 0.6, playery + 0.8);
		glVertex2f(playerx - 0.7, playery + 0.65);

		glVertex2f(playerx - 0.5, playery + 0.5);
		glVertex2f(playerx - 0.6, playery + 0.3);
		glVertex2f(playerx - 0.3, playery);
		glEnd();
	}
	
}

int generaterandom()
{
	return (rand() % 19) + 1;
	
}

void collectables()
{
	float no2;
	if (seconds % 2 == 0)
		no2 = 0;
	else
		no2 = 0.3;
	if (startcoll)
	{
		collx = generaterandom();
		colly = generaterandom();

		collx2 = generaterandom();
		colly2 = generaterandom();

		collx3 = generaterandom();
		colly3 = generaterandom();

		collx4 = generaterandom();
		colly4 = generaterandom();

		collx5 = generaterandom();
		colly5 = generaterandom();
			
	}
	glColor3f(0.0, 1.0, 0.0);
	if (!coll1) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx+0.5, colly);
		glVertex2f(collx+0.5, colly+0.7);
		glEnd();

		glBegin(GL_QUADS);
		//glLineWidth(3.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(collx, colly+0.7);
		glVertex2f(collx, colly + 1);
		glVertex2f(collx+1, colly + 1);
		glVertex2f(collx+1, colly + 0.7);
		glVertex2f(collx, colly + 0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx + 0.8+no2, colly+0.5);
		glVertex2f(collx + 0.5+no2, colly + 0.3);
		glVertex2f(collx + 0.2+no2, colly + 0.3);
		glEnd();
	}
	if (!coll2) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx2 + 0.5, colly2);
		glVertex2f(collx2 + 0.5, colly2 + 0.7);
		glEnd();

		glBegin(GL_QUADS);
		//glLineWidth(3.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(collx2, colly2 + 0.7);
		glVertex2f(collx2, colly2 + 1);
		glVertex2f(collx2 + 1, colly2 + 1);
		glVertex2f(collx2 + 1, colly2 + 0.7);
		glVertex2f(collx2, colly2 + 0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx2 + 0.8+no2, colly2 + 0.5);
		glVertex2f(collx2 + 0.5+no2, colly2 + 0.3);
		glVertex2f(collx2 + 0.2+no2, colly2 + 0.3);
		glEnd();
	}
	if (!coll3) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx3 + 0.5, colly3);
		glVertex2f(collx3 + 0.5, colly3 + 0.7);
		glEnd();

		glBegin(GL_QUADS);
		//glLineWidth(3.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(collx3, colly3 + 0.7);
		glVertex2f(collx3, colly3 + 1);
		glVertex2f(collx3 + 1, colly3 + 1);
		glVertex2f(collx3 + 1, colly3 + 0.7);
		glVertex2f(collx3, colly3 + 0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx3 + 0.8+no2, colly3 + 0.5);
		glVertex2f(collx3 + 0.5+no2, colly3 + 0.3);
		glVertex2f(collx3 + 0.2+no2, colly3 + 0.3);
		glEnd();
	}
	if (!coll4) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx4 + 0.5, colly4);
		glVertex2f(collx4 + 0.5, colly4 + 0.7);
		glEnd();

		glBegin(GL_QUADS);
		//glLineWidth(3.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(collx4, colly4 + 0.7);
		glVertex2f(collx4, colly4 + 1);
		glVertex2f(collx4 + 1, colly4 + 1);
		glVertex2f(collx4 + 1, colly4 + 0.7);
		glVertex2f(collx4, colly4 + 0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx4 + 0.8+no2, colly4 + 0.5);
		glVertex2f(collx4 + 0.5+no2, colly4 + 0.3);
		glVertex2f(collx4 + 0.2+no2, colly4 + 0.3);
		glEnd();
	}
	if (!coll5) {
		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx5 + 0.5, colly5);
		glVertex2f(collx5 + 0.5, colly5 + 0.7);
		glEnd();

		glBegin(GL_QUADS);
		//glLineWidth(3.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(collx5, colly5 + 0.7);
		glVertex2f(collx5, colly5 + 1);
		glVertex2f(collx5 + 1, colly5 + 1);
		glVertex2f(collx5 + 1, colly5 + 0.7);
		glVertex2f(collx5, colly5 + 0.7);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.65, 0.16, 0.17);
		glLineWidth(3.0);
		glVertex2f(collx5 + 0.8+no2, colly5 + 0.5);
		glVertex2f(collx5 + 0.5+no2, colly5 + 0.3);
		glVertex2f(collx5 + 0.2+no2, colly5 + 0.3);
		glEnd();
	}
	
}

void obstacles()
{
	if (startcoll)
	{
		obsx = generaterandom();
		obsy = generaterandom();

		obsx2 = generaterandom();
		obsy2 = generaterandom();

		obsx3 = generaterandom();
		obsy3 = generaterandom();

		obsx4 = generaterandom();
		obsy4 = generaterandom();

		obsx5 = generaterandom();
		obsy5 = generaterandom();

	}
	glColor3f(1.0, 0.0, 0.0);
	if (!colll1) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(obsx, obsy);
		glVertex2f(obsx + 1, obsy + 1);
		glEnd();
		if (seconds % 2 == 1)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(obsx + 1, obsy);
			glVertex2f(obsx, obsy + 1);
			glEnd();
		}
		
	}
	if (!colll2) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(obsx2, obsy2);
		glVertex2f(obsx2 + 1, obsy2 + 1);
		glEnd();
		if (seconds % 2 == 1)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(obsx2 + 1, obsy2);
			glVertex2f(obsx2, obsy2 + 1);
			glEnd();
		}
		
	}
	if (!colll3) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(obsx3, obsy3);
		glVertex2f(obsx3 + 1, obsy3 + 1);
		glEnd();
		if (seconds % 2 == 1)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(obsx3 + 1, obsy3);
			glVertex2f(obsx3, obsy3 + 1);
			glEnd();
		}
		
	}
	if (!colll4) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(obsx4, obsy4);
		glVertex2f(obsx4 + 1, obsy4 + 1);
		glEnd();
		if (seconds % 2 == 1)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(obsx4 + 1, obsy4);
			glVertex2f(obsx4, obsy4 + 1);
			glEnd();
		}
		
	}
	if (!colll5) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(obsx5, obsy5);
		glVertex2f(obsx5 + 1, obsy5 + 1);
		glEnd();
		if (seconds % 2 == 1)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(obsx5 + 1, obsy5);
			glVertex2f(obsx5, obsy5 + 1);
			glEnd();
		}
		
	}

}

void timepower()
{
	if (startcoll) {
		tp1 = generaterandom();
		tp2 = generaterandom();
	}
	
	glColor3f(0.0, 0.0, 1.0);
	if (!timepower1)
	{
		glRectd(tp1, tp2, tp1 + 1, tp2 + 1);
		if (seconds % 2 == 0)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(tp1 + 0.5, tp2 + 0.8);
			glVertex2f(tp1 + 0.5, tp2 + 0.5);
			glVertex2f(tp1 + 0.2, tp2 + 0.3);
			glEnd();
		}
		else if (seconds % 2 == 1)
		{
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(tp1 + 0.8, tp2 + 0.5);
			glVertex2f(tp1 + 0.5, tp2 + 0.5);
			glVertex2f(tp1 + 0.2, tp2 + 0.3);
			glEnd();
		}
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(tp1 + 0.8, tp2);
		glVertex2f(tp1 + 1, tp2 + 0.3);
		glVertex2f(tp1 + 0.8, tp2 + 0.5);
		glEnd();
	}
		
}

void obstaclepower()
{
	float no;
	if (seconds % 2 == 0)
		no = 0;
	else
		no = 0.3;
	if (startcoll) {
		op1 = generaterandom();
		op2 = generaterandom();
	}

	glColor3f(0.0, 1.0, 1.0);
	if (!obspower)
	{
		glBegin(GL_POLYGON);
		glVertex2f(op1 + 0.4, op2);
		glVertex2f(op1 + 0.7, op2);
		glVertex2f(op1 + 1, op2+0.5);
		glVertex2f(op1 + 0.7, op2+1);
		glVertex2f(op1 + 0.4, op2+1);
		glVertex2f(op1 , op2+0.5);
		glVertex2f(op1 + 0.4, op2);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.16, 0.4, 0.24);
		glVertex2f(op1, op2+no);
		glVertex2f(op1 + 0.5, op2+no + 0.2);
		glVertex2f(op1 + 1, op2+no);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.16, 0.4, 0.24);
		glVertex2f(op1, op2 + 0.5+no);
		glVertex2f(op1 + 0.5, op2 + 1+no);
		glVertex2f(op1 + 1, op2 + 0.5+no);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glColor3f(0.16, 0.4, 0.24);
		glVertex2f(op1 , op2 + 1+no);
		glVertex2f(op1 + 0.5, op2 + 1.5+no);
		glVertex2f(op1 + 1, op2 + 1+no);
		glEnd();
	}
		
}
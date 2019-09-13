#include <stdio.h>
#include <Windows.h>
#include <GL/glut.h>

int x1, y1, x2, y2;

void myInit() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 20, 0, 50);
}

void draw_pixel(int x, int y) {
	glPointSize(4);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_line(int x1, int x2, int y1, int y2) {
	int dx, dy, i, p;
	int incx, incy, inc1, inc2;
	int x, y;

	dx = x2 - x1; //change in x
	dy = y2 - y1; //change in y

	//negative values for when change in x and y are less than zero
	if (dx < 0) dx = -dx; 
	if (dy < 0) dy = -dy;

	incx = 1;
	if (x2 < x1) incx = -1; // x increments by negative 

	incy = 1;
	if (y2 < y1) incy = -1; //y increments by negative

	x = x1; y = y1; //initializes the values of x and y in draw_pixel

	//bresenham formula
	if (dx > dy) {
		draw_pixel(x, y);
		p = 2 * dy - dx; //starting value for the decision parameter
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++) {
			if (p >= 0) {
				y += incy;
				x +=incx;
				p += inc1;
			}
			else
				p += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	}
	else {
		draw_pixel(x, y);
		p = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++) {
			if (p >= 0) {
				x += incx;
				y += incy;
				p += inc1;
			}
			else
				p += inc2;
				y += incy;
			draw_pixel(x, y);
		}
	}
}

void myDisplay() {
	draw_line(x1, x2, y1, y2);
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	printf("Enter (x1, x2, y1, y2)\n");
	scanf_s("%i %i %i %i", &x1, &x2, &y1, &y2); //reads data and stores the values
	
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bresenham's Line Drawing");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}
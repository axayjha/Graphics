/** 
	Implementation of Midpoint circle algorithm

	Using OpenGL Utility Toolkit (freeglut).

	Akshay Anand
	25/03/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <GL/glut.h>

#define MAXPOINTS 2000

#define Min(a,b) ((a<b) ? a : b)
#define Max(a,b) ((a>b) ? a : b)

int x0, x1, Y0, Y1, xlo, xhi, ylo, yhi;
int xdim, ydim;
int npoints;
int xvals[MAXPOINTS], yvals[MAXPOINTS];

void setPixel(int x, int y)
{
	xvals[npoints] = x;
	yvals[npoints] = y;
	npoints++;
}

void circleMidpoint(int xCenter, int yCenter, int radius)
{
	int x = 0;
	int y = radius;
	int p = 1 - radius;
	npoints=0;
	void circlePlotPoints(int, int, int, int);

	/* Plot first set of points */
	circlePlotPoints(xCenter, yCenter, x, y);

	while(x < y) {
		x++;
		if (p < 0)
			p += 2 * x + 1;
		else {
			y--;
			p += 2 * (x - y) + 1;
		}	  
		circlePlotPoints(xCenter, yCenter, x, y);
	}
}

void circlePlotPoints(int xCenter, int yCenter, int x, int y)
{
	setPixel( xCenter+x, yCenter+y );
	setPixel( xCenter-x, yCenter+y );
	setPixel( xCenter+x, yCenter-y );
	setPixel( xCenter-x, yCenter-y );
	setPixel( xCenter+y, yCenter+x );
	setPixel( xCenter-y, yCenter+x );
	setPixel( xCenter+y, yCenter-x );
	setPixel( xCenter-y, yCenter-x );
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(xlo, xhi, ylo, yhi);
}

void showpoints(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);

    for (i=0;i<npoints;i++) glVertex2i(xvals[i],yvals[i]);
		
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    int r, xc, yc;
    printf("Enter radius: ");
    scanf("%d", &r);
    printf("Ending circle center: ");
    scanf("%d%d",&xc,&yc);
    xlo = xc-r; xhi = xc+r;
    ylo = yc-r; yhi = yc+r;   

    xdim = 2*r + 1;
    ydim = 2*r + 1;

    circleMidpoint(xc, yc, r);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(xdim,ydim);
    
    glutCreateWindow("Midpoint Circle Algorithm Illustration");
    init();
    glutDisplayFunc(showpoints);
    glutMainLoop();
    return 0;
}
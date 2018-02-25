/** 
	Implementation of Bresenham's line drawing algorithm
	for all slopes. 

	Using OpenGL Utility Toolkit (freeglut).

	Akshay Anand
	25/02/2018
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

void lineBres(int xa, int ya, int xb, int yb)
{
	int dx = abs(xa - xb), 
		dy = abs(ya - yb);	

	int p = 2*dy - dx;

	int twoDy = 2*dy, 
	    twoDx = 2*dx, 
	    twoDyMinusDx = 2*(dy - dx);

	bool NEGSLOPE = ((xb < xa) ^ (yb < ya));
	bool SLOPEGT1 = dy >= dx;	

	int x = xa, y = ya;

	npoints = 1;
    xvals[0] = xa; yvals[0] = ya;

    int incr = 1;
	if(NEGSLOPE) incr = -1;  // if negative slope, y_increment = -1

	while (x!=xb && y!=yb) { // while either endpoint is not reached	
		
		if ( !(SLOPEGT1) ) { // if slope < 1
			x++;
			if (p < 0)
				p += twoDy;
			else {
				y += incr;
				p += twoDyMinusDx;
			}
		}
		else {				// if slope > 1
			y += incr;
			if (p < 0)
				p += twoDx;
			else{
				x++;
				p -= twoDyMinusDx;
			}
		}
		assert(npoints < MAXPOINTS);
		xvals[npoints] = x; yvals[npoints] = y;		
		npoints++;		
	}
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

    printf("Starting point (x,y): ");
    scanf("%d%d",&x0,&Y0);
    printf("Ending point (x,y): ");
    scanf("%d%d",&x1,&Y1);
    xlo = Min(x0,x1); xhi = Max(x0,x1);
    ylo = Min(Y0,Y1); yhi = Max(Y0,Y1);   

    xdim = abs(x0 - x1) + 1;
    ydim = abs(Y0 - Y1) + 1;

    lineBres(x0,Y0,x1,Y1);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(xdim,ydim);
    
    glutCreateWindow("Bresenham's Algorithm Illustration");
    init();
    glutDisplayFunc(showpoints);
    glutMainLoop();
    return 0;
}
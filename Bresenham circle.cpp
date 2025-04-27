#include <GL/glut.h> 
#include <iostream> 
void bresenhamCircle(int xc, int yc, int radius) { 
 int x = 0; 
 int y = radius; 
 int p = 3 - 2 * radius; 
 
 auto plotCirclePoints = [&](int x, int y) { 
 glVertex2i(xc + x, yc + y); 
 glVertex2i(xc - x, yc + y); 
 glVertex2i(xc + x, yc - y); 
 glVertex2i(xc - x, yc - y); 
 glVertex2i(xc + y, yc + x); 
 glVertex2i(xc - y, yc + x); 
 glVertex2i(xc + y, yc - x); 
 glVertex2i(xc - y, yc - x); 
 }; 
 glPointSize(5.0f); 
 glBegin(GL_POINTS); 
 plotCirclePoints(x, y); 
 while (x <y) { 
 x++; 
 if (p <= 0) { 
 p = p + 4 * x + 6; 
 } else { 
 y--; 
 p = p + 4 * (x - y) + 10; 
 } 
 plotCirclePoints(x, y); 
 } 
 glEnd(); 
 glFlush(); 
} 
void display() { 
 glClear(GL_COLOR_BUFFER_BIT); 
 bresenhamCircle(200, 200, 75); 
 glFlush(); 
} 
void init() { 
 glClearColor(0.0, 0.0, 0.0, 1.0); 
 glColor3f(1.0,1.0,1.0); 
 glPointSize(2.0); 
 glOrtho(0.0, 500.0, 500.0, 0.0,-1.0,-1.0); 
} 
int main(int argc, char **argv) { 
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 glutInitWindowSize(500, 500); 
 glutCreateWindow("Bresenham Circle Algorithm"); 
 init(); 
 glutDisplayFunc(display); 
 glutMainLoop(); 
 return 0; 
}
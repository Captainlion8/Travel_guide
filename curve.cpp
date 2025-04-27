Koch Curve

#include <GL/glut.h> 
#include <cmath> 
int level = 4; // Depth of recursion 
void drawKochCurve(float x1, float y1, float x2, float y2, int iter) { 
 if (iter == 0) { 
 glVertex2f(x1, y1); 
 glVertex2f(x2, y2); 
 } else { 
 float dx = (x2 - x1) / 3.0; 
 float dy = (y2 - y1) / 3.0; 
 float x3 = x1 + dx; 
 float y3 = y1 + dy; 
 float x5 = x1 + 2 * dx; 
 float y5 = y1 + 2 * dy; 
 float x4 = 0.5 * (x1 + x2) - sqrt(3.0) * (y1 - y2) / 6.0; 
 float y4 = 0.5 * (y1 + y2) - sqrt(3.0) * (x2 - x1) / 6.0; 
 drawKochCurve(x1, y1, x3, y3, iter - 1); 
 drawKochCurve(x3, y3, x4, y4, iter - 1); 
 drawKochCurve(x4, y4, x5, y5, iter - 1); 
 drawKochCurve(x5, y5, x2, y2, iter - 1); 
 } 
} 
void display() { 
 glClear(GL_COLOR_BUFFER_BIT); 
 glBegin(GL_LINES); 
 // Coordinates of an equilateral triangle 
 float x1 = 150, y1 = 300; 
 float x2 = 450, y2 = 300; 
 float x3 = 300, y3 = 300 + (sqrt(3.0) * 150); 
 drawKochCurve(x1, y1, x2, y2, level); 
 drawKochCurve(x2, y2, x3, y3, level); 
 drawKochCurve(x3, y3, x1, y1, level); 
 glEnd(); 
 glFlush(); 
} 
void init() { 
 glClearColor(1.0, 1.0, 1.0, 1.0); // White background 
 glColor3f(0.0, 0.0, 0.0); // Black lines 
 gluOrtho2D(0, 600, 0, 600); 
} 
int main(int argc, char** argv) { 
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 glutInitWindowSize(600, 600); 
 glutInitWindowPosiƟ on(100, 100);
 glutCreateWindow("Koch Snowflake"); 
 init(); 
 glutDisplayFunc(display); 
 glutMainLoop(); 
 return 0; 
}


Bezier curve

#include <GL/glut.h> 
#include <math.h> 
// Centered Control Points 
float ctrlpoints[4][2] = { 
 {150.0, 200.0}, // b0 
 {200.0, 400.0}, // b1 
 {300.0, 100.0}, // b2 
 {350.0, 200.0} // b3 
}; 
void init() { 
 glClearColor(0.0, 0.0, 0.0, 0.0); // Black background 
 glMatrixMode(GL_PROJECTION); 
 gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Wider view area 
} 
void drawControlPolygon() { 
 glColor3f(1.0, 1.0, 0.0); // Yellow lines 
 glBegin(GL_LINE_STRIP); 
 for (int i = 0; i < 4; i++) { 
 glVertex2fv(ctrlpoints[i]); 
 } 
 glEnd(); 
 glPointSize(6.0); 
 glColor3f(1.0, 0.0, 0.0); // Red control points 
 glBegin(GL_POINTS); 
 for (int i = 0; i < 4; i++) { 
 glVertex2fv(ctrlpoints[i]); 
 } 
 glEnd(); 
} 
void drawBezierCurve() { 
 glColor3f(0.0, 1.0, 1.0); // Cyan curve 
 glBegin(GL_LINE_STRIP); 
 for (float t = 0.0; t <= 1.0; t += 0.001) { 
 float x = pow(1 - t, 3) * ctrlpoints[0][0] + 
 3 * t * pow(1 - t, 2) * ctrlpoints[1][0] + 
 3 * pow(t, 2) * (1 - t) * ctrlpoints[2][0] + 
 pow(t, 3) * ctrlpoints[3][0]; 
 float y = pow(1 - t, 3) * ctrlpoints[0][1] + 
 3 * t * pow(1 - t, 2) * ctrlpoints[1][1] + 
 3 * pow(t, 2) * (1 - t) * ctrlpoints[2][1] + 
 pow(t, 3) * ctrlpoints[3][1]; 
 glVertex2f(x, y); 
 } 
 glEnd(); 
} 
void display() { 
 glClear(GL_COLOR_BUFFER_BIT); 
 drawControlPolygon(); 
 drawBezierCurve(); 
 glFlush(); 
} 
int main(int argc, char** argv) { 
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 glutInitWindowSize(500, 500); 
 glutCreateWindow("Centered Bezier Curve"); 
 init(); 
 glutDisplayFunc(display); 
 glutMainLoop(); 
 return 0; 
}
#include <GL/glut.h> 
#include <iostream> 
#define zero 0.0 
#define one 1.0 
using namespace std;
int a, b, c, d, type;
void bresenham(int x1, int y1, int x2, int y2, int type) { 
 cout << "IN" << endl;
 int dx = abs(x2 - x1);
 int dy = abs(y2 - y1);
 int s1 = (x2 - x1) >= 0 ? 1 : -1;
 int s2 = (y2 - y1) >= 0 ? 1 : -1;
 bool interchange = false;
 if (dy > dx) { 
 swap(dx, dy);
 interchange = true;
 } 
 int e = 2 * dy - dx;
 int x = x1;
 int y = y1;
 int j = 0;
 glPointSize(1.0f);
 if (type == 4) { 
 glPointSize(10.0f);
 } 
 glBegin(GL_POINTS);
 for (int i = 0; i <= dx; i++) {
 if (type == 4 || type == 1) { 
 glVertex2i(x, y);
 } 
 if (j % 4 == 0 && type == 2) { 
 glVertex2i(x, y);
 } 
 if (j < 5 && type == 3) { 
 glVertex2i(x, y);
 } 
 j = (j + 1) % 10;
 while (e >= 0) { 
 if (interchange) 
 x = x + s1;
 else 
 y = y + s2;
 e = e - 2 * dx;
 } 
 if (interchange) 
 y = y + s2;
 else 
 x = x + s1;
 e = e + 2 * dy;
 } 
 glEnd();
} 
void display() { 
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(one, zero, zero);
 bresenham(-350, 0, 350, 0, 1);
 bresenham(0, 350, 0, -350, 1);
 glFlush();
} 
void init() { 
 glClearColor(0.0, 0.6, 0.6, 0.6);
 glClear(GL_COLOR_BUFFER_BIT);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D(-700 / 2, 700 / 2, -700 / 2, 700 / 2);
} 
int cnt = 0;
int oldx, oldy;
int newx, newy;
/* 
void mouse(int button, int state, int x, int y) { 
 if (state == GLUT_DOWN) { 
 if (button == GLUT_LEFT_BUTTON) { 
 int viewport[4];
 glGetIntegerv(GL_VIEWPORT, viewport);
 int winWidth = viewport[2];
 int winHeight = viewport[3];
 int xi = x - winWidth / 2;
 int yi = winHeight / 2 - y;
 cnt = (cnt + 1) % 2;
 if (cnt == 1) { 
 oldx = xi;
 oldy = yi;
 } 
 if (cnt == 0) { 
 newx = xi;
 newy = yi;
 } 
 glPointSize(5.0f);
 glColor3f(0.0, 0.0, 1.0); // Blue color for dots
 glBegin(GL_POINTS);
 glVertex2i(xi, yi);
 glEnd();
 glFlush();
 } 
 } 
} 
*/ 
void mouse(int button, int state, int x, int y) { 
 if (state == GLUT_DOWN) { 
 if (button == GLUT_LEFT_BUTTON) { 
 int viewport[4];
 glGetIntegerv(GL_VIEWPORT, viewport);
 int winWidth = viewport[2];
 int winHeight = viewport[3];
 int xi = x - winWidth / 2;
 int yi = winHeight / 2 - y;
 cout << xi << "\t" << yi << "\n";
 cnt = (cnt + 1) % 2;
 if (cnt == 1) { 
 oldx = xi;
 oldy = yi;
 cout << "a" << endl;
 } 
 if (cnt == 0) { 
 newx = xi;
 newy = yi;
 cout << "b" << endl;
 } 
 glPointSize(5.0f);
 glColor3f(0.0, 0.0, 1.0);
 glBegin(GL_POINTS);
 glVertex2i(xi, yi);
 glEnd();
 glFlush();
 } 
 } 
} 
void menu(int a) { 
 cout << "whatever\n";
 bresenham(oldx, oldy, newx, newy, a);
} 
int main(int argc, char** argv) { 
 a = 200, b = -200, c = -200, d = 200;
 type = 1;
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 glutInitWindowSize(700, 700);
 glutInitWindowPosition(50, 50);
 glutCreateWindow("Breshnem Algorithm for simple line :");
 init();
 glutDisplayFunc(display);
 glutMouseFunc(mouse);
 glutCreateMenu(menu);
 glutAddMenuEntry("BRESENHAM_SIMPLE", 1);
 glutAddMenuEntry("BRESENHAM_DOTTED", 2);
 glutAddMenuEntry("BRESENHAM_DASHED", 3);
 glutAddMenuEntry("BRESENHAM_SOLID", 4);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 glutMainLoop();
 return 0;
}
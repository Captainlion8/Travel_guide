Flood Fill

#include<GL/gl.h> 
#include<GL/glut.h> 
#include<stdio.h> 

int ww = 600, wh = 500;   // Corrected the typo
float bgCol[3] = {0.0, 0.0, 0.0};     // Background color (Black)
float intCol[3] = {1.0, 1.0, 0.0};    // Initial color (Yellow)
float fillCol[3] = {1.0, 0.0, 1.0};   // Fill color (Magenta)

void SetPixel(int pointx, int pointy, float f[3]) {
    glBegin(GL_POINTS);
    glColor3fv(f);
    glVertex2i(pointx, pointy);
    glEnd();
    glFlush();
}

void getPixel(int x, int y, float pixels[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels);
}

void drawPolygon(int x1, int y1, int x2, int y2) {
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x1, y2);
    glVertex2i(x2, y2);
    glVertex2i(x2, y1);
    glEnd();
    glFlush();
}

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Black background
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon(200, 200, 300, 300); // Draw initial yellow box
    glFlush();
}

void floodFill4(int x, int y, float oldColor[3], float newColor[3]) {
    float color[3];
    getPixel(x, y, color);
    
    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        SetPixel(x, y, newColor);
        floodFill4(x + 1, y, oldColor, newColor);
        floodFill4(x - 1, y, oldColor, newColor);
        floodFill4(x, y + 1, oldColor, newColor);
        floodFill4(x, y - 1, oldColor, newColor);
        floodFill4(x + 1, y + 1, oldColor, newColor);
        floodFill4(x - 1, y + 1, oldColor, newColor);
        floodFill4(x - 1, y - 1, oldColor, newColor);
        floodFill4(x + 1, y - 1, oldColor, newColor);
    }
}

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int xi = x;
        int yi = (wh - y); // Convert to OpenGL coordinate system
        floodFill4(xi, yi, intCol, fillCol);
    }
}

void myInit() {
    glViewport(0, 0, ww, wh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)ww, 0.0, (GLdouble)wh);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(ww, wh);
    glutCreateWindow("Flood Fill Recursive");
    glutDisplayFunc(display);
    myInit();
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}




Boundary Fill 

#include<iostream> 
#include<math.h> 
#include<time.h> 
#include<GL/glut.h> 
using namespace std;
void delay(float ms) 
{ 
clock_t goal=ms+clock();
while(goal>clock());
} 
void init() 
{ 
glClearColor(1.0,1.0,1.0,1.0);
glMatrixMode(GL_PROJECTION);
gluOrtho2D(0,640,0,480);
} 
void bound_it(int x,int y,float* fillColor,float* bc) 
{ 
float color[3];
glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
 if((color[0]!=bc[0]|| color[1]!=bc[1]|| 
color[2]!=bc[2])&&(color[0]!=fillColor[0] || color[1]!=fillColor[1] || 
color[2]!=fillColor[2] )) 
 { 
 glColor3f(fillColor[0],fillColor[1],fillColor[2]);
 glBegin(GL_POINTS);
 glVertex2i(x,y);
 glEnd();
 glFlush();
 bound_it(x+1,y,fillColor,bc);
 bound_it(x-2,y,fillColor,bc);
 bound_it(x,y+1,fillColor,bc);
 bound_it(x,y-2,fillColor,bc);
 
 bound_it(x+1,y+1,fillColor,bc);
 bound_it(x-2,y-2,fillColor,bc);
 bound_it(x-1,y+1,fillColor,bc);
 bound_it(x+2,y-2,fillColor,bc);
 } 
} 
void mouse(int btn,int state,int x,int y) 
{ 
 y=480-y;
 if(btn==GLUT_LEFT_BUTTON) 
 { 
 if(state==GLUT_DOWN) 
 { 
 float bCol[]={1,0,0};
 float color[]={0,0,1};
 bound_it(x,y,color,bCol);
 } 
 } 
} 
void world() 
{ 
glLineWidth(3);
glPointSize(2);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1,0,0);
glBegin(GL_LINE_LOOP);
glVertex2i(150,100);
glVertex2i(300,300);
glVertex2i(450,100);
glEnd();
glFlush();
} 
int main(int argc,char**argv) 
{ 
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(640,480);
glutInitWindowPosition(200,200);
glutCreateWindow("Boundary Fill Algorithm 57 ");
glutDisplayFunc(world);
glutMouseFunc(mouse);
init();
glutMainLoop();
return 0;
}


Line clipping

#include <iostream> 
#include <GL/glut.h> // Include OpenGL and GLUT headers 
using namespace std; 
// Define the region codes for the 9 regions 
#define LEFT 1 // 0001 
#define RIGHT 2 // 0010 
#define BOTTOM 4 // 0100 
#define TOP 8 // 1000 
// Define a structure for represenƟ ng a point
struct Point { 
 float x, y; 
}; 
// FuncƟ on to compute the region code for a point
int computeRegionCode(Point p, float wx1, float wy1, float wx2, float wy2) { 
 int code = 0; 
 if (p.x < wx1) { // to the leŌ of the window
 code |= LEFT; 
 } else if (p.x > wx2) { // to the right of the window 
 code |= RIGHT; 
 } 
 if (p.y < wy1) { // below the window 
 code |= BOTTOM; 
 } else if (p.y > wy2) { // above the window 
 code |= TOP; 
 } 
 return code; 
} 
// FuncƟ on to implement the Cohen-Sutherland line clipping algorithm 
void cohenSutherlandLineClipping(Point &p1, Point &p2, float wx1, float wy1, float wx2, float wy2) { 
 int code1 = computeRegionCode(p1, wx1, wy1, wx2, wy2); 
 int code2 = computeRegionCode(p2, wx1, wy1, wx2, wy2); 
 bool accept = false; 
 while (true) { 
 // Case 1: Both points are inside the clipping window 
 if ((code1 == 0) && (code2 == 0)) { 
 accept = true; 
 break; 
 } 
 // Case 2: Both points are outside the clipping window (in the same region) 
 else if ((code1 & code2) != 0) { 
 break; 
 } 
 // Case 3: One point is inside the window and the other is outside 
 else { 
 int codeOut; 
 float x, y; 
 // Choose one of the points that is outside the clipping window 
 if (code1 != 0) { 
 codeOut = code1; 
 } else { 
 codeOut = code2; 
 } 
 // Find the intersecƟ on point using the region code
 if (codeOut & TOP) { // point is above the window 
 x = p1.x + (p2.x - p1.x) * (wy2 - p1.y) / (p2.y - p1.y); 
 y = wy2; 
 } else if (codeOut & BOTTOM) { // point is below the window 
 x = p1.x + (p2.x - p1.x) * (wy1 - p1.y) / (p2.y - p1.y); 
 y = wy1; 
 } else if (codeOut & RIGHT) { // point is to the right of the window 
 y = p1.y + (p2.y - p1.y) * (wx2 - p1.x) / (p2.x - p1.x); 
 x = wx2; 
 } else if (codeOut & LEFT) { // point is to the leŌ of the window
 y = p1.y + (p2.y - p1.y) * (wx1 - p1.x) / (p2.x - p1.x); 
 x = wx1; 
 } 
 // Update the outside point to the intersecƟ on point
 if (codeOut == code1) { 
 p1.x = x; 
 p1.y = y; 
 code1 = computeRegionCode(p1, wx1, wy1, wx2, wy2); 
 } else { 
 p2.x = x; 
 p2.y = y; 
 code2 = computeRegionCode(p2, wx1, wy1, wx2, wy2); 
 } 
 } 
 } 
 // If the line is accepted, print the clipped line 
 if (accept) { 
 cout << "Line accepted from (" << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ")\n"; 
 } else { 
 cout << "Line rejected\n"; 
 } 
} 
// Global variables for the line and window coordinates 
Point p1, p2; 
float wx1, wy1, wx2, wy2; 
// FuncƟ on to iniƟ alize OpenGL seƫ ngs
void initOpenGL() { 
 glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white 
 glMatrixMode(GL_PROJECTION); 
 glLoadIdenƟ ty();
 gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Set the coordinate system 
} 
// FuncƟ on to display the graphics
void display() { 
 glClear(GL_COLOR_BUFFER_BIT); 
 
 // Draw the clipping window (red) 
 glColor3f(1.0, 0.0, 0.0); 
 glBegin(GL_LINE_LOOP); 
 glVertex2f(wx1, wy1); 
 glVertex2f(wx2, wy1); 
 glVertex2f(wx2, wy2); 
 glVertex2f(wx1, wy2); 
 glEnd(); 
 
 // Draw the original line (blue) 
 glColor3f(0.0, 0.0, 1.0); 
 glBegin(GL_LINES); 
 glVertex2f(p1.x, p1.y); 
 glVertex2f(p2.x, p2.y); 
 glEnd(); 
 
 // Perform line clipping 
 cohenSutherlandLineClipping(p1, p2, wx1, wy1, wx2, wy2); 
 
 // Draw the clipped line (green) 
 glColor3f(0.0, 1.0, 0.0); 
 glBegin(GL_LINES); 
 glVertex2f(p1.x, p1.y); 
 glVertex2f(p2.x, p2.y); 
 glEnd(); 
 
 glFlush(); 
} 
// Main funcƟ on to set up GLUT and OpenGL
int main(int argc, char** argv) { 
 int numLines; 
 
 // Input the clipping window coordinates 
 cout << "Enter clipping window coordinates (wx1, wy1) and (wx2, wy2): "; 
 cin >> wx1 >> wy1 >> wx2 >> wy2; 
 
 // Get the number of lines to clip 
 cout << "Enter the number of lines to clip: "; 
 cin >> numLines; 
 
 // Loop to process mulƟ ple lines
 for (int i = 0; i < numLines; ++i) { 
 cout << "Enter line " << i + 1 << " coordinates (x1, y1) and (x2, y2): "; 
 cin >> p1.x >> p1.y >> p2.x >> p2.y; 
 
 // IniƟ alize GLUT and OpenGL
 glutInit(&argc, argv); 
 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
 glutInitWindowSize(500, 500); 
 glutCreateWindow("Cohen-Sutherland Line Clipping"); 
 
 // IniƟ alize OpenGL
 initOpenGL(); 
 
 // Register the display funcƟ on
 glutDisplayFunc(display); 
 
 // Perform line clipping 
 cohenSutherlandLineClipping(p1, p2, wx1, wy1, wx2, wy2); 
 
 // Enter the GLUT event loop 
 glutMainLoop(); 
 } 
 
 return 0; 
}




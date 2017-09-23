
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include "graphics.h"
#include "board.h"
#include "checkers.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

string p1name, p2name, p1color, p2color;
bool menuState = true;
bool infoState = false;

// window width and height
GLdouble width, height;

// mouse x and y
int mouseX, mouseY;

int originalCol, originalRow, finalCol, finalRow, numBlack, numRed;


// GLUT window handle
int wd;

// Checkers Board and Result
Board board = Board();
Result r;

void init(void)
{
    // initial window width and height,
    // within which we draw. (0,0) is the lower left corner
    width  = 780.0;
    height = 780.0;
    
    mouseX = 0;
    mouseY = 0;
    
    r = noResult;
    
    return;
}

void drawSquare(int x, int y, int length) {
    
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x, y + length);
    glVertex2f(x + length, y + length);
    glVertex2f(x + length, y);
    glEnd();
}

void drawCircle(int x, int y, int radius) {
    double theta = M_PI/20.0;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(x, y);
    for (double i = 0; i < 2*M_PI+theta; i += theta) {
        glVertex2i(x+radius*cos(i), y+radius*sin(i));
    }
    glEnd();
}

void printText(int x, int y, std::string text)
{
    glRasterPos2f(x,y);
    int len = (int) text.length();
    
    //loop to display character by character
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
        
    }
}

void display(void)
{
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.f, 1.f);
    
    
    int side_border = 30;
    int bottom_border = 30;
    int top_border = 30;
    // clear the screen */
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    glColor3f(128.0/255.0, 128.0/255.0, 128.0/255.0);
    glBegin(GL_QUADS);
    glVertex2i(side_border,bottom_border);
    glVertex2i(width-side_border,bottom_border);
    glVertex2i(width-side_border,height-top_border);
    glVertex2i(side_border,height-top_border);
    glEnd();
    
    // Begin solution
    glColor3f(224/250.0, 224/255.0, 224/255.0);
    
    drawCircle(mouseX, 780 - mouseY, 20);
    
    drawSquare(30, 30, 90);
    drawSquare(210, 30, 90);
    drawSquare(390, 30, 90);
    drawSquare(570, 30, 90);
    
    drawSquare(120, 120, 90);
    drawSquare(300, 120, 90);
    drawSquare(480, 120, 90);
    drawSquare(660, 120, 90);
    
    drawSquare(30, 210, 90);
    drawSquare(210, 210, 90);
    drawSquare(390, 210, 90);
    drawSquare(570, 210, 90);
    
    drawSquare(120, 300, 90);
    drawSquare(300, 300, 90);
    drawSquare(480, 300, 90);
    drawSquare(660, 300, 90);
    
    drawSquare(30, 390, 90);
    drawSquare(210, 390, 90);
    drawSquare(390, 390, 90);
    drawSquare(570, 390, 90);
    
    drawSquare(120, 480, 90);
    drawSquare(300, 480, 90);
    drawSquare(480, 480, 90);
    drawSquare(660, 480, 90);

    drawSquare(30, 570, 90);
    drawSquare(210, 570, 90);
    drawSquare(390, 570, 90);
    drawSquare(570, 570, 90);

    drawSquare(120, 660, 90);
    drawSquare(300, 660, 90);
    drawSquare(480, 660, 90);
    drawSquare(660, 660, 90);
    
    glColor3f(0/250.0, 0/255.0, 0/255.0);

    if (board.playerToMove() == player1) {
        printText(20, 760, "Player 1's Turn! (Blue)");
    } else {
        printText(20, 760, "Player 2's Turn! (Yellow)");

    }
    


    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (board.typeAtLocation(i, j) == black) {
                glColor3f(0/250.0, 0/255.0, 225/255.0);
                drawCircle(90 * j + 75, 90 * i + 75, 40);
            } else if (board.typeAtLocation(i, j) == kingBlack) {
                glColor3f(204/250.0, 229/255.0, 255/255.0);
                drawCircle(90 * j + 75, 90 * i + 75, 40);
            } else if (board.typeAtLocation(i, j) == red) {
                glColor3f(255/250.0, 255/255.0, 0/255.0);
                drawCircle(90 * j + 75, 90 * i + 75, 40);
            } else if (board.typeAtLocation(i, j) == kingRed) {
                glColor3f(255/250.0, 255/255.0, 204/255.0);
                drawCircle(90 * j + 75, 90 * i + 75, 40);
            } else if (board.typeAtLocation(i, j) == nothing) {
                glColor3f(1, 1, 1);
                
            }
            
            
        }
    }
    


    
    
    // End solution
    
    // force drawing to start
    glutSwapBuffers();
    
    return;
}


void mouse(int button, int state, int x, int y)
{
    
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        
        if (x >= 30 && x <= 120) {
            originalCol = 0;
        } else if (x >= 120 && x <= 210) {
            originalCol = 1;
        } else if (x >= 210 && x <= 300) {
            originalCol = 2;
        } else if (x >= 300 && x <= 390) {
            originalCol = 3;
        } else if (x >= 390 && x <= 480) {
            originalCol = 4;
        } else if (x >= 480 && x <= 570) {
            originalCol = 5;
        } else if (x >= 570 && x <= 660) {
            originalCol = 6;
        } else if (x >= 660 && x <= 750) {
            originalCol = 7;
        }
        
        if (y >= 660 && y <= 750) {
            originalRow = 0;
        } else if (y >= 570 && y <= 660) {
            originalRow = 1;
        } else if (y >= 480 && y <= 570) {
            originalRow = 2;
        } else if (y >= 390 && y <= 480) {
            originalRow = 3;
        } else if (y >= 300 && y <= 390) {
            originalRow = 4;
        } else if (y >= 210 && y <= 300) {
            originalRow = 5;
        } else if (y >= 120 && y <= 210) {
            originalRow = 6;
        } else if (y >= 30 && y <= 120) {
            originalRow = 7;
        }
        
        board.assignOldGraphics(originalRow, originalCol);

    }
    
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        
        if (x >= 30 && x <= 120) {
            finalCol = 0;
        } else if (x >= 120 && x <= 210) {
            finalCol = 1;
        } else if (x >= 210 && x <= 300) {
            finalCol = 2;
        } else if (x >= 300 && x <= 390) {
            finalCol = 3;
        } else if (x >= 390 && x <= 480) {
            finalCol = 4;
        } else if (x >= 480 && x <= 570) {
            finalCol = 5;
        } else if (x >= 570 && x <= 660) {
            finalCol = 6;
        } else if (x >= 660 && x <= 750) {
            finalCol = 7;
        }
        
        if (y >= 660 && y <= 750) {
            finalRow = 0;
        } else if (y >= 570 && y <= 660) {
            finalRow = 1;
        } else if (y >= 480 && y <= 570) {
            finalRow = 2;
        } else if (y >= 390 && y <= 480) {
            finalRow = 3;
        } else if (y >= 300 && y <= 390) {
            finalRow = 4;
        } else if (y >= 210 && y <= 300) {
            finalRow = 5;
        } else if (y >= 120 && y <= 210) {
            finalRow = 6;
        } else if (y >= 30 && y <= 120) {
            finalRow = 7;
        }
        
        board.assignFinalGraphics(finalRow, finalCol);
        
    }
    
    
    
    glutPostRedisplay();
    
    return;
}



 
int graphicsPlay(int argc, char *argv[])
{
    
    // perform initialization NOT OpenGL/GLUT dependent,
    // as we haven't created a GLUT window yet
    init();
    
    // initialize GLUT, let it extract command-line
    // GLUT options that you may provide
    // - NOTE THE '&' BEFORE argc
    glutInit(&argc, argv);
    
    // specify the display to be single
    // buffered and color as RGBA values
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    // set the initial window size
    glutInitWindowSize((int) width, (int) height);
    
    // create the window and store the handle to it
    wd = glutCreateWindow("Checkers");
    
    // --- register callbacks with GLUT ---
    
    // register function that draws in the window
    glutDisplayFunc(display);
    
    glutMouseFunc(mouse);
    
    // Set up initial OpenGL context
    // clear color buffer to white
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    // start the GLUT main loop
    glutMainLoop();
    
    
    return 0;
}



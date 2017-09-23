
#ifndef graphics_h
#define graphics_h


void init(void);

// Draws Square at x, y with a length l
void drawSquare(int x, int y, int length);

void drawCircle(int x, int y, int radius);

void printText(int x, int y, std::string text);

void mouse(int button, int state, int x, int y);



// Callback functions for GLUT */

// Draw the window
void display(void);


int graphicsPlay(int argc, char *argv[]);



#endif /* graphics_h */

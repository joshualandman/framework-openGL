#include "Window.h"

Window::Window(char* name, int widthIn, int heightIn)
{
	width = widthIn;
	height = heightIn;

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
		
	glutInitWindowSize(width, height);
	glutCreateWindow( name );

	//Whenever the draw command clears the color buffer, this color covers the screen
	float cornflowerBlue[] = {.392, .584, .929};
	glClearColor(cornflowerBlue[0], cornflowerBlue[1], cornflowerBlue[2], 1.0);
}

Window::Window(void)
{
}


Window::~Window(void)
{
}

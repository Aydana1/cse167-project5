#pragma once

/* OpenGL output window related routines */
class Window {
public:
	static int width, height; // window size

	static void idleCallback(void);
	static void reshapeCallback(int, int);
	static void displayCallback(void);
	static void mouseMotionCallback(int x, int y);
	static void mouseClickCallback(int button, int state, int x, int y);
};


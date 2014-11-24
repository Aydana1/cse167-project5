#pragma once
class MouseHandler {
private:
	
public:
	
	MouseHandler();
	~MouseHandler();

	static void mouseMotionCallback(int x, int y);
	static void mouseClickCallback(int button, int state, int x, int y);
	static void rotateTrackball(int w, int h, int startX, int startY, int endX, int endY);
};


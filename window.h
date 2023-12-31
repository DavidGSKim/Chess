#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
	Display *d;
	Window w;
	int s;
	GC gc;
	unsigned long colours[11];
	int width, height;

	public:
	Xwindow(int width=800, int height=800);  // Constructor; for displaying window
	~Xwindow();                              // Destructor; for destroying window

	enum {White = 0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown, DarkGreen}; // Enumeration of colors available

	// Draws a line from (x1, y1) to (x2, y2)
	void drawLine(int x1, int y1, int x2, int y2);

	// Draws an arc centered at (x, y) with width and height starting from angle1 to angle2
	void drawArc(int x, int y, int width, int height, int angle1, int angle2);
	void fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour);

	// Draws a rectangle
	void fillRectangle(int x, int y, int width, int height, int colour=Black);

	// Draws a circle centered at (x, y) with diameter d
	void fillCircle(int x, int y, int d, int colour = Black);

	// Draw a polygon with the first vertex at (x, y) with num vertices, side length side
	//     and rotated rotate radians. The second vertex is (x + side, y) rotated by
	//     rotate
	void fillPolygon(int x, int y, int num, int side, int rotate = 0, int colour = Black);

	// Draws a string
	void drawString(int x, int y, std::string msg, int colour = Black);
	void drawBigString(int x, int y, std::string msg, int colour = Black);

	// if you use this function, make sure font exists on the undergrad environment
	void drawStringFont(int x, int y, std::string msg, std::string font, int colour = Black);

  void showAvailableFonts();

 private:
  void printMessage(int x, int y, const std::string& msg, int colour, XFontStruct& f);
};

#endif
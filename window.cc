#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include "window.h"
#include <cmath>

using namespace std;
const double pi = std::acos(-1);

Xwindow::Xwindow(int width, int height) : width{width}, height{height}
{

	d = XOpenDisplay(NULL);
	if (d == NULL)
	{
		cerr << "Cannot open display" << endl;
		exit(1);
	}
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1, BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w, ExposureMask | KeyPressMask);
	XMapRaised(d, w);

	Pixmap pix = XCreatePixmap(d, w, width, height, DefaultDepth(d, DefaultScreen(d)));
	gc = XCreateGC(d, pix, 0, (XGCValues *)0);

	XFlush(d);
	XFlush(d);

	// Setting up the colors available
	XColor xcolour;
	Colormap cmap;
	char color_vals[11][11] = {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown", "darkgreen"};

	cmap = DefaultColormap(d, DefaultScreen(d));
	for (int i = 0; i < 11; ++i)
	{
		XParseColor(d, cmap, color_vals[i], &xcolour);
		XAllocColor(d, cmap, &xcolour);
		colours[i] = xcolour.pixel;
	}

	XSetForeground(d, gc, colours[Black]);

	// Making the window a fixed size
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);
	XSynchronize(d, True);
	usleep(1000);
}

Xwindow::~Xwindow()
{
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

void Xwindow::drawLine(int x1, int y1, int x2, int y2)
{
	XDrawLine(d, w, gc, x1, y1, x2, y2);
}

void Xwindow::drawArc(int x1, int y1, int width, int height, int angle1, int angle2)
{
	XDrawArc(d, w, gc, x1, y1, width / 2, height / 2, angle1 * 64, angle2 * 64);
}

void Xwindow::fillArc(int x, int y, int width, int height, int angle1, int angle2, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XFillArc(d, w, gc, x - (width / 2), y - (height / 2), width, height, angle1 * 64, angle2 * 64);
	XSetForeground(d, gc, colours[Black]);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XSetForeground(d, gc, colours[Black]);
}

void Xwindow::fillCircle(int x, int y, int di, int colour)
{
	fillArc(x, y, di, di, 0, 360, colour);
}

void Xwindow::fillPolygon(int x, int y, int vertices, int side, int rotate, int colour)
{
	XPoint *point = new XPoint[vertices];
	point[0] = XPoint{(short int)x, (short int)y};
	double angle = rotate + (pi / 2);

	for (int i = 1; i < vertices; ++i)
	{
		short int X = side * sin(angle);
		short int Y = side * cos(angle);
		point[i] = XPoint{X, Y};
		angle += (2 * pi) - (pi * 2) / vertices;
	}

	XSetForeground(d, gc, colours[colour]);
	XFillPolygon(d, w, gc, point, vertices, Convex, CoordModePrevious);
	XSetForeground(d, gc, colours[Black]);
	delete[] point;
}

void Xwindow::drawStringFont(int x, int y, string msg, string font, int colour)
{
	XFontStruct *f = XLoadQueryFont(d, font.c_str());
	if (f == nullptr)
	{
		f = XLoadQueryFont(d, "6x13");
	}
	printMessage(x, y, msg, colour, *f);
	delete f;
}

void Xwindow::drawBigString(int x, int y, string msg, int colour)
{
	ostringstream name;
	name << "-*-helvetica-bold-r-*-*-*-240-" << width / 5 << "-" << height / 5 << "-*-*-*-*";
	drawStringFont(x, y, msg, name.str(), colour);
}

void Xwindow::showAvailableFonts()
{
	int count;
	char **fnts = XListFonts(d, "*", 10000, &count);
	for (int i = 0; i < count; ++i)
	{
		cout << fnts[i] << endl;
	}
}

void Xwindow::printMessage(int x, int y, const string &msg, int colour, XFontStruct &f)
{
	XSetForeground(d, gc, colours[colour]);
	XTextItem ti;
	ti.chars = const_cast<char *>(msg.c_str());
	ti.nchars = msg.length();
	ti.delta = 0;
	ti.font = f.fid;
	XDrawText(d, w, gc, x, y, &ti, 1);
	XSetForeground(d, gc, colours[Black]);
	XFlush(d);
}
#include <u.h>
#include <libc.h>
#include <draw.h>
#include <event.h>
#define π 3.14159

struct Circle {
	Point center;
	int r;
};
typedef struct Circle Circle;

enum { Seconds, Minutes, Hours };

Point
pcircle(Circle c, int θ)
{
	Point p;

	p.x = c.center.x + c.r*sin((double) θ * π/180.00);
	p.y = c.center.y - c.r*cos((double) θ * π/180.00);

	return p;
}

int
min(int a, int b)
{
	return (a < b) ? a : b;
}

void
clearscreen(void)
{
	draw(screen, screen->r, display->white, nil, ZP);
}

void
linebetweencircles(Circle c, int d, int θ, int t, int end1, int end2, Image *src)
{
	Point p₁, p₂;

	p₁ = c.center;
	p₂ = pcircle((Circle){c.center, d}, θ);

	line(screen, p₁, p₂, end1, end2, t, src, ZP);
}

void
drawhand(Circle region, int hand, Tm t)
{
	Point end;
	int len, thick, pos;

	switch(hand){
	case Seconds:
		len = region.r;
		thick = 0;
		pos = t.sec;
		break;
	case Minutes:
		len = region.r;
		thick = 1;
		pos = t.min;
		break;
	case Hours:
		len = region.r * 0.50;
		thick = 3;
		pos = t.hour*5;
		break;
	}

	linebetweencircles(region, len, 2*pos*π, thick, Endsquare, Endarrow, display->black);
}

void
drawclock(Circle bounds, int thick)
{
	Tm *tm;
	int i;

	clearscreen();
	ellipse(screen, bounds.center, bounds.r - thick, bounds.r - thick, thick, display->black, ZP);
//	for(i = 1; i <= 12; i++){
		
		

	tm = localtime(time(0));
	for(i = Seconds; i <= Hours; i++)
		drawhand(bounds, i, *tm);
}

void
eresized(int new)
{
	Circle c;

	if(new && getwindow(display, Refnone) < 0)
		sysfatal("can't reattach to window");

	c.center.x = screen->r.min.x + Dx(screen->r)/2;
	c.center.y = screen->r.min.y + Dy(screen->r)/2;
	c.r = min(Dx(screen->r)/2, Dy(screen->r)/2);

	drawclock(c, 3);
}

void
main(void)
{
	Circle c;
	Mouse m;

	initdraw(0, 0, "clock");
	eresized(0);
	einit(Emouse);

	for(;;){
		while(ecanmouse)
			emouse();
/*		if(m.buttons & 4)
			break;*/
		c.center.x = screen->r.min.x + Dx(screen->r)/2;
		c.center.y = screen->r.min.y + Dy(screen->r)/2;
		c.r = min(Dx(screen->r)/2, Dy(screen->r)/2);
		drawclock(c, 3);
		print("aaaa");
		sleep(1000);
	}
}
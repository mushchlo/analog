#include <u.h>
#include <libc.h>
#include <draw.h>
#include <event.h>



void
eresized(int new)
{
	if(new && getwindow(display, Refnone) < 0)
		sysfatal("can't reattach to window");
}

void
main(void)
{

}
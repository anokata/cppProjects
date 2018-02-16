#include<X11/Xlib.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
    Display *d;
    int s;
    Window w;
    XEvent e;

    d=XOpenDisplay(NULL);
    if(d==NULL) {
        printf("Cannot open display\n");
        exit(1);
    }
    s=DefaultScreen(d);

    w=XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 0,
                             WhitePixel(d, s), BlackPixel(d, s));

    // Process Window Close Event through event handler so XNextEvent does Not fail
    Atom delWindow = XInternAtom( d, "WM_DELETE_WINDOW", 0 );
    XSetWMProtocols(d , w, &delWindow, 1);

    /* select kind of events we are interested in */
    XSelectInput(d, w, ExposureMask | KeyPressMask);

    /* map (show) the window */
    XMapWindow(d, w);

    /* event loop */
    while(1) {
        XNextEvent(d, &e);
        /* draw or redraw the window */
        if(e.type==Expose) {
            XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
        }
        /* exit on key press */
        if(e.type==KeyPress)
            break;

        // Handle Windows Close Event
        if(e.type==ClientMessage)
            break;
    }

    XDestroyWindow(d, w);
    XCloseDisplay(d);
    return 0;
}

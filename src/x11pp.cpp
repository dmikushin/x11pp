#include "x11pp.h"

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string>

namespace x11pp {

screenInfo::screenInfo(char *name, unsigned int width, unsigned int height, int x, int y) : Name(name),
                                                                                            Width(width), Height(height), X(x), Y(y)
{
}

int catch_error(Display *display, XErrorEvent *e)
{
    char msg[80];
    printf("Ignoring Xlib Error ...\n");
    XGetErrorText(display, e->error_code, msg, 80);
    printf("%s\n", msg);
    return 0;
}

x11pp::x11pp::x11pp()
{
    
}

x11pp::x11pp::~x11pp()
{
}

Window x11pp::GetWindowHandle(std::string windowName, int width, int height)
{
    Display *display = XOpenDisplay(NULL);

    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);
    Window rv = EnumerateWindows(display, root, (char*)windowName.c_str(), width, height);
    XFlush(display);
    XCloseDisplay(display);
    return rv;
}

void x11pp::RaiseWindow(Window window)
{
    printf("raise_window.....\n");
    Display *display = XOpenDisplay(NULL);
    XSetErrorHandler(catch_error);
    XRaiseWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
}

/* Lower the Window. */
void x11pp::LowerWindow(Window window)
{
    printf("lower_window.....\n");
    Display *display = XOpenDisplay(NULL);
    XSetErrorHandler(catch_error);
    XLowerWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
}

/* Show Window. */
void x11pp::ShowWindow(Window window)
{
    printf("map_window.....\n");
    Display *display = XOpenDisplay(NULL);
    XSetErrorHandler(catch_error);
    XMapWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
}

/* Hide Window. */
void x11pp::HideWindow(Window window)
{
    printf("unmap_window.....\n");
    Display *display = XOpenDisplay(NULL);
    XSetErrorHandler(catch_error);
    XUnmapWindow(display, window);
    XFlush(display);
    XCloseDisplay(display);
}

void x11pp::MoveWindow(Window window, int x, int y)
{
    Display *display = XOpenDisplay(NULL);
    XSetErrorHandler(catch_error);
    XMoveWindow(display, window, x, y);
    XFlush(display);
    XCloseDisplay(display);
}

void x11pp::ResizeWindow(Window window, int w, int h)
{
    Display *display = XOpenDisplay(NULL);
    XSetErrorHandler(catch_error);
    XResizeWindow(display, window, w, h);
    XFlush(display);
    XCloseDisplay(display);
}

int x11pp::MaximizeWindow(Window window)
{
    Display *display = XOpenDisplay(NULL);
    XClientMessageEvent ev = {};
    Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
    Atom maxH = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    Atom maxV = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

    if (wmState == None)
        return 0;

    ev.type = ClientMessage;
    ev.format = 32;
    ev.window = window;
    ev.message_type = wmState;
    ev.data.l[0] = 1;
    ev.data.l[1] = maxH;
    ev.data.l[2] = maxV;
    ev.data.l[3] = 1;

    int rv =  XSendEvent(display, DefaultRootWindow(display), False,
                      SubstructureNotifyMask,
                      (XEvent *)&ev);
    XFlush(display);
    XCloseDisplay(display);
    return rv;
}

void x11pp::RemoveWindowDecoration(Window window)
{

    Display *display = XOpenDisplay(NULL);
    MotifWmHints *hints;
    Atom property;
    int nelements;

    hints = get_motif_wm_hints(display, window);
    if (hints == NULL)
    {
        hints = (MotifWmHints *)calloc(1, sizeof(*hints));
        hints->decorations = (1L << 0);
    }

    hints->flags |= (1L << 1);
    hints->decorations = 0;

    property = XInternAtom(display, "_MOTIF_WM_HINTS", False);
    nelements = sizeof(*hints) / sizeof(long);

    XChangeProperty(display, window, property, property, 32, PropModeReplace,
                    (unsigned char *)hints, nelements);

    free(hints);
    XFlush(display);
    XCloseDisplay(display);
}

MotifWmHints *x11pp::get_motif_wm_hints(Display *display, Window window)
{
    Atom property;
    int result;
    Atom actual_type;
    int actual_format;
    unsigned long nitems;
    unsigned long bytes_after;
    unsigned char *data;

    property = XInternAtom(display, "_MOTIF_WM_HINTS", False);
    result = XGetWindowProperty(display, window, property,
                                0, LONG_MAX, False, AnyPropertyType,
                                &actual_type, &actual_format,
                                &nitems, &bytes_after, &data);

    if (result == Success && data != NULL)
    {
        size_t data_size;
        size_t max_size;
        MotifWmHints *hints;

        data_size = nitems * sizeof(long);
        max_size = sizeof(*hints);

        hints = (MotifWmHints *)calloc(1, max_size);

        memcpy(hints, data, data_size > max_size ? max_size : data_size);
        XFree(data);

        return hints;
    }

    return NULL;
}

std::vector<screenInfo> x11pp::GetScreenInfo()
{
    std::vector<screenInfo> screens;

    Display *display = XOpenDisplay(NULL);

    if (NULL == display)
    {
        perror("No DISPLAY in environment!");
        exit(EXIT_FAILURE);
    }
    Window window = DefaultRootWindow(display);
    XRRScreenResources *screenr = XRRGetScreenResources(display, window);

    // This is the key right here. Use XRRScreenResources::noutput
    int output = screenr->noutput;

    for (int i = 0; i < output; ++i)
    {
        XRROutputInfo *out_info = XRRGetOutputInfo(display, screenr, screenr->outputs[i]);

        if (NULL != out_info && out_info->connection == RR_Connected)
        {
            XRRCrtcInfo *crt_info = XRRGetCrtcInfo(display, screenr, out_info->crtc);
            screenInfo scr(out_info->name,
                           crt_info->width,
                           crt_info->height,
                           crt_info->x,
                           crt_info->y);
            screens.push_back(scr);
            XRRFreeCrtcInfo(crt_info);
        }

        XRRFreeOutputInfo(out_info);
    }

    XRRFreeScreenResources(screenr);
    XCloseDisplay(display);
    return screens;
}

Window x11pp::EnumerateWindows(Display *display, Window rootwindow, char *window_name, int window_width, int window_height)
{
    Window retWindow = 0, root, parent, *children;
    unsigned children_count;

    if (0 != XQueryTree(display, rootwindow, &root, &parent, &children, &children_count))
    {

        unsigned i;

        XSetErrorHandler(catch_error);
        for (i = 0; i < children_count; i++)
        {

            XTextProperty text;
            if (XGetWMName(display, children[i], &text) > 0)
            {
                std::string str = std::string((const char *)(text.value));
                //cout << "name = " << str << endl;
                size_t found = str.find(std::string(window_name));
                if (found != std::string::npos)
                {
                    if (window_width > 0 && window_height > 0)
                    {
                        XWindowAttributes window_attributes_return;
                        XGetWindowAttributes(display, children[i], &window_attributes_return);
                        //printf("%dx%d \n",window_attributes_return.width,window_attributes_return.height);

                        if (window_attributes_return.width == window_width && window_attributes_return.height == window_height)
                        {
                            printf("Enumerate windows - Window id = 0x%lx\n", children[i]);
                            retWindow = children[i];
                            break;
                        }
                    }
                    else
                    {
                        //cout << "Enumerate windows2 - name = " << str << " , window_name= " << string(window_name) << endl;
                        retWindow = children[i];
                        break;
                    }
                }
            }

            if (retWindow == 0)
            {
                /* Recurse through the children for their children */
                retWindow = EnumerateWindows(display, children[i], window_name, window_width, window_height);
            }
        }
        XFree(children);
    }
    //    XSetErrorHandler(NULL);

    return retWindow;
}

} // namespace x11pp

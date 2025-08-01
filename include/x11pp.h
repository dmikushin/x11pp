#ifndef X11PP
#define X11PP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrandr.h>
#include <xcb/xcb.h>

#include <string>
#include <iostream>
#include <vector>

namespace x11pp {

struct MotifWmHints
{
    unsigned long flags;
    unsigned long functions;
    unsigned long decorations;
    long input_mode;
    unsigned long status;
};

struct screenInfo
{
    std::string Name;
    unsigned int Width, Height;
    int X, Y;
    screenInfo(char *name, unsigned int width, unsigned int height, int x, int y);
    screenInfo() {}
};

class x11pp
{

private:
    MotifWmHints *get_motif_wm_hints(Display *display, Window window);
    const char* display_name;

public:
    x11pp();
    x11pp(const char* display);
    ~x11pp();

    Window GetWindowHandle(std::string windowName, int width=0, int height=0);

    /* Raise the Window. */
    void RaiseWindow(Window window);

    /* Lower the Window. */
    void LowerWindow(Window window);

    /* show Window. */
    void ShowWindow(Window window);

    /* Hide Window. */
    void HideWindow(Window window);

    /* Maximise the window */
    int MaximizeWindow(Window window);

    /* Removing the decoration of window */
    void RemoveWindowDecoration(Window window);

    /* Get Screen information of all available screens */
    std::vector<screenInfo> GetScreenInfo();

    /* Move Window @window to location (x,y) */
    void MoveWindow(Window window, int x, int y);

    /* Resize window to size w,h*/
    void ResizeWindow(Window window, int w, int h);

    /* Enumerate all Windows */
    Window EnumerateWindows(Display *display, Window rootwindow, char *window_name, int window_width, int window_height);
};

} // namespace x11pp

#endif

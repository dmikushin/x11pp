
#include "x11pp.h"

int main()
{
    // simple usage
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.MaximizeWindow(hdl);

    return 0;
}
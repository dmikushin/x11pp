
#include "WindowMgrLib.h"

int main()
{
    // simple usage
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.MaximizeWindow(hdl);

    return 0;
}

# X11Test Programs 

This is a simple C++ wrapper to do the following operations with X11 windows:

1. Raise Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.RaiseWindow(hdl)
    ```

2. Lower Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.LowerWindow(hdl)
    ```

3. Show Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.ShowWindow(hdl)
    ```

4. Hide Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.HideWindow(hdl)
    ```

5. Maximize Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.MaximizeWindow(hdl)
    ```

6. Remove Window Decorations
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.RemoveWindowDecoration(hdl)
    ```

7. Move Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.MoveWindow(hdl, 400, 300);
    ```

8. Resize Window
    ```cpp
    WindowManager::WindowMgrLib wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.ResizeWindow(hdl, 400, 300);
    ```

## Additional info

Window names can be found with following command
```shell
xwininfo -root -tree
```

## Install X11 libraries

Dependencies installation example for Ubuntu:

```shell
sudo apt install libx11-dev
sudo apt install libxrandr-dev
```

## Build and run

```shell
cd x11test
mkdir build
cd build
cmake ..
make -j4
```


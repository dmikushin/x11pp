
# x11pp - C++ X11 Window Management Library 

x11pp is a lightweight C++ library that provides a simple interface for X11 window management operations.

## Features

- Window search by name and optional size filtering
- Window manipulation (raise, lower, show, hide)
- Window positioning and resizing
- Window maximization
- Window decoration removal
- Multi-monitor support with screen information retrieval

## Usage Examples

1. Raise Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.RaiseWindow(hdl)
    ```

2. Lower Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.LowerWindow(hdl)
    ```

3. Show Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.ShowWindow(hdl)
    ```

4. Hide Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.HideWindow(hdl)
    ```

5. Maximize Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.MaximizeWindow(hdl)
    ```

6. Remove Window Decorations
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.RemoveWindowDecoration(hdl)
    ```

7. Move Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.MoveWindow(hdl, 400, 300);
    ```

8. Resize Window
    ```cpp
    x11pp::x11pp wmgr;
    // make sure one window with this name exists
    Window hdl = wmgr.GetWindowHandle("TestWindow");
    wmgr.ResizeWindow(hdl, 400, 300);
    ```

9. Get Screen Information
    ```cpp
    x11pp::x11pp wmgr;
    std::vector<x11pp::screenInfo> screens = wmgr.GetScreenInfo();
    for (const auto& screen : screens) {
        std::cout << "Screen: " << screen.Name 
                  << " Size: " << screen.Width << "x" << screen.Height
                  << " Position: " << screen.X << "," << screen.Y << std::endl;
    }
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
sudo apt install libxcb1-dev
```

## Build

```shell
git clone https://github.com/yourusername/x11pp.git
cd x11pp
mkdir build
cd build
cmake ..
make -j4
```

### Build artifacts

- `libx11pp.so` - Shared library
- `x11pp_test` - Test executable

## Integration

To use x11pp in your project:

1. Include the header:
```cpp
#include "x11pp.h"
```

2. Link against the library:
```cmake
target_link_libraries(your_app x11pp)
```

3. Use the x11pp namespace:
```cpp
x11pp::x11pp window_manager;
Window handle = window_manager.GetWindowHandle("YourWindow");
```



# About this.. 

This is a simple program to do the following operation on windows on x11 machine(ubuntu)

1. Raise Window
2. Lower Window
3. Show Window
4. Hide Window
5. Maximize Window
6. Remove Window Decorations
7. Move Window
8. Resize Window

## Install X11 libraries
---
Be sure to install X11 libraries before proceeding.

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

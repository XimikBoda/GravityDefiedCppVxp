#pragma once

#include <memory>

#include <string>

#include <vmgraph.h>

class Canvas;

class CanvasImpl {
private:
    Canvas* canvas;

    int width = 0;
    int height = 0;

    //static int convertKeyCharToKeyCode(SDL_Keycode keyCode);

public:
    CanvasImpl(Canvas* canvas);
    ~CanvasImpl();

    void repaint();
    int getWidth();
    int getHeight();

    VMINT getRenderer();
    void processEvents();
    void setWindowTitle(const std::string& title);
};
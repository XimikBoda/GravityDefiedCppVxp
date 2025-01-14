#pragma once
#include <memory>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>

#include "Image.h"
#include "Font.h"

constexpr auto PI_CONV = 3.1415926 / 180.0;

class Image;

class Graphics {
private:
    VMINT layer_handle = -1;
    VMUINT8* layer_buf = 0;
    std::shared_ptr<Font> font;
    vm_graphic_color currentColor;
    // void _ellipse(int cx, int cy, int xradius, int yradius);
    void _putpixel(int x, int y);

public:
    enum Anchors {
        HCENTER = 1,
        VCENTER = 2,
        LEFT = 4,
        RIGHT = 8,
        TOP = 16,
        BOTTOM = 32,
        BASELINE = 64
    };
    Graphics(VMINT layer_handle);
    void drawString(const std::string& s, int x, int y, int anchor);
    void setColor(int r, int g, int b);
    void setFont(std::shared_ptr<Font> font);
    std::shared_ptr<Font> getFont() const;
    void setClip(int x, int y, int w, int h);
    void drawChar(char c, int x, int y, int anchor);
    void fillRect(int x, int y, int w, int h);
    void fillArc(int x, int y, int w, int h, int startAngle, int arcAngle);
    void drawArc(int x, int y, int w, int h, int startAngle, int arcAngle);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawImage(Image* const image, int x, int y, int anchor);
    static int getAnchorX(int x, int size, int anchor);
    static int getAnchorY(int y, int size, int anchor);
};
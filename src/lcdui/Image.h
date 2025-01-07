#pragma once

#include <string>

#include <vmgraph.h>

class Image {
private:
    VMUINT8* surface = 0;
    int width = 0, height = 0;
public:
    Image(const std::string& embeddedPath);
    Image(int width, int height);
    ~Image();

    int getWidth() const;
    int getHeight() const;
    VMUINT8* getSurface() const;
};

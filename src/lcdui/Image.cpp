#include "Image.h"

#include <stdexcept>
#include <string>

#include <vmgraph.h>
#include <vmres.h>

Image::Image(int width, int height)
{
    this->surface = (VMUINT8*)vm_graphic_create_canvas(width, height);

    this->width = width;
    this->height = height;
}

Image::Image(const std::string& embeddedPath)
{
    VMINT size = 0;
    VMUINT8* res = vm_load_resource((char*)embeddedPath.c_str(), &size);
    this->surface = (VMUINT8*)vm_graphic_load_image(res, size);
    vm_free(res);

    frame_prop *prop = vm_graphic_get_img_property((VMINT)this->surface, 1);
    this->width = prop->width;
    this->height = prop->height;
}

Image::~Image()
{
    vm_graphic_release_canvas((VMINT)this->surface);
}

int Image::getWidth() const
{
    return this->width;
}

int Image::getHeight() const
{
    return this->height;
}

VMUINT8* Image::getSurface() const
{
    return this->surface;
}

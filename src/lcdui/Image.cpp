#include "Image.h"

#include <stdexcept>
#include <string>

#include <vmgraph.h>
#include <vmres.h>

#define STBI_ONLY_PNG
#define STBI_NO_WRITE         
#define STBI_NO_HDR           
#define STBI_NO_LINEAR        
#define STBI_NO_FAILURE_STRINGS 
#define STBI_NO_STDIO 
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const VMUINT16 trans_color = VM_COLOR_888_TO_565(255, 0, 255);

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

	int n;
	stbi_uc* im = stbi_load_from_memory(res, size, &width, &height, &n, 4);

	this->surface = (VMUINT8*)vm_graphic_create_canvas(width, height);

	VMUINT16 color;
	for (int i = 0; i < width * height; ++i) {
		stbi_uc* p = im + i * 4;
		if (p[3] != 255)
			color = trans_color;
		else {
			color = VM_COLOR_888_TO_565(p[0], p[1], p[2]);
			if (color == trans_color)
				color--;
		}

		((VMUINT16*)(surface + VM_CANVAS_DATA_OFFSET))[i] = color;
	}
	vm_free(res);
	stbi_image_free(im);

	vm_graphic_canvas_set_trans_color((VMINT)this->surface, trans_color);
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

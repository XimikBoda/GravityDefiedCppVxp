#include "Font.h"

#include <stdexcept>

#include <vmgraph.h>
#include <vmchset.h>

Font::Font(FontStyle style, FontSize pointSize)
{
	this->style = style;
	size = pointSize;

	setFont();
	int realSize = getRealFontSize(pointSize);

	this->height = realSize;
}

Font::~Font()
{
}

int Font::getBaselinePosition() const
{
	return height;
}

int Font::getHeight() const
{
	return height;
}

void Font::setFont() const {
	vm_graphic_set_font((font_size_t)size);
	vm_font_set_font_style(style == STYLE_BOLD, style == STYLE_ITALIC, 0);
}

int Font::charWidth(char c)
{
	return stringWidth(std::string(1, c));
}

int Font::stringWidth(const std::string& s)
{
	int width = 0;

	VMWCHAR wstr[200];
	vm_ascii_to_ucs2(wstr, s.size() * 2 + 2, (VMSTR)s.c_str());
	setFont();

	width = vm_graphic_get_string_width(wstr);
	return width;
}

int Font::substringWidth(const std::string& string, int offset, int len)
{
	return stringWidth(string.substr(offset, len));
}

int Font::getRealFontSize(FontSize size)
{
	return vm_graphic_get_character_height();
}

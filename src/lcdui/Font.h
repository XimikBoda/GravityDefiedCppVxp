#pragma once

#include <string>
#include <vmgraph.h>

class Font {
public:
    enum FontSize {
        SIZE_SMALL = VM_SMALL_FONT,
        SIZE_MEDIUM = VM_MEDIUM_FONT,
        SIZE_LARGE = VM_LARGE_FONT
    };

    enum FontStyle {
        STYLE_PLAIN,
        STYLE_BOLD,
        STYLE_ITALIC
    };

    enum FontFace {
        FACE_SYSTEM = 0
    };

    Font(FontStyle style, FontSize pointSize);
    ~Font();

    int getBaselinePosition() const;
    int getHeight() const;
    void setFont() const;
    int charWidth(char c);
    int stringWidth(const std::string& s);
    int substringWidth(const std::string& string, int offset, int len);

private:
    FontStyle style;
    FontSize size;

    int height;

    static int getRealFontSize(FontSize size);
};
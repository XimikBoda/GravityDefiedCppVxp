#include "Graphics.h"
#include <memory>
#include <vmchset.h>
#include <vmstdlib.h>

Graphics::Graphics(VMINT layer_handle)
{
	this->layer_handle = layer_handle;
	this->layer_buf = (VMUINT8*)vm_graphic_get_layer_buffer(layer_handle);
	this->currentColor.vm_color_565 = VM_COLOR_888_TO_565(0, 0, 0);
	vm_graphic_setcolor(&this->currentColor);
	this->font = nullptr;
}

void Graphics::drawString(const std::string& s, int x, int y, int anchor)
{
	VMWCHAR wstr[200];
	vm_ascii_to_ucs2(wstr, s.size() * 2 + 2, (VMSTR)s.c_str());

	font->setFont();

	int width, height;
	width = vm_graphic_get_string_width(wstr);
	height = vm_graphic_get_string_height(wstr);

	x = getAnchorX(x, width, anchor);
	y = getAnchorY(y, height, anchor);

	vm_graphic_textout_to_layer(layer_handle, x, y, wstr, vm_wstrlen(wstr));
}

void Graphics::setColor(int r, int g, int b)
{
	currentColor.vm_color_565 = VM_COLOR_888_TO_565(r, g, b);
	vm_graphic_setcolor(&currentColor);
}

void Graphics::setFont(std::shared_ptr<Font> font)
{
	this->font = font;
}

std::shared_ptr<Font> Graphics::getFont() const
{
	return font;
}

void Graphics::setClip(int x, int y, int w, int h)
{
	vm_graphic_set_clip(x, y, w + x - 1, h + y - 1);
}

void Graphics::drawChar(char c, int x, int y, int anchor)
{
	drawString(std::string(1, c), x, y, anchor);
}

void Graphics::fillRect(int x, int y, int w, int h)
{
	vm_graphic_fill_rect_ex(layer_handle, x, y, w, h);
}

/**
 * Draws the outline of a circular or elliptical arc covering the specified rectangle,
 * using the current color and stroke style. The resulting arc begins at startAngle
 * and extends for arcAngle degrees, using the current color. Angles are interpreted
 * such that 0 degrees is at the 3 o'clock position. A positive value indicates a
 * counter-clockwise rotation while a negative value indicates a clockwise rotation.
 *
 * The center of the arc is the center of the rectangle whose origin is (x, y) and
 * whose size is specified by the width and height arguments.
 *
 * The resulting arc covers an area width + 1 pixels wide by height + 1 pixels tall.
 * If either width or height is less than zero, nothing is drawn.
 *
 * The angles are specified relative to the non-square extents of the bounding rectangle
 * such that 45 degrees always falls on the line from the center of the ellipse to the
 * upper right corner of the bounding rectangle. As a result, if the bounding rectangle
 * is noticeably longer in one axis than the other, the angles to the start and end of
 * the arc segment will be skewed farther along the longer axis of the bounds.
 *
 * Parameters:
 * x - the x coordinate of the upper-left corner of the arc to be drawn
 * y - the y coordinate of the upper-left corner of the arc to be drawn
 * width - the width of the arc to be drawn
 * height - the height of the arc to be drawn
 * startAngle - the beginning angle
 * arcAngle - the angular extent of the arc, relative to the start angle
 */
void Graphics::drawArc(int x, int y, int width, int heigth, int startAngle, int arcAngle)
{
	// draw complete ellipse if (0, 360) specified
	if (startAngle == 0 && arcAngle == 360) {
		//vm_graphic_ellipse_ex(layer_handle, x, y, width, heigth);
	   // return;
	}

	// Draws an elliptical arc left-top at (x, y), with axes given by
	// xradius and yradius, traveling from startAngle to endangle.
	// Bresenham-based if complete
	int xradius = width / 2, yradius = heigth / 2;
	x += xradius;
	y += yradius;

	
	if (xradius == 0 && yradius == 0) {
		return;
	}

	int angle_step = asin(1.f / fmin(xradius, yradius)) / PI_CONV;
	if (angle_step == 0)
		angle_step = 1;

	int lx = x + int(xradius * cos(startAngle * PI_CONV));
	int ly = y - int(xradius * sin(startAngle * PI_CONV));

	for (int angle = startAngle; angle < startAngle + arcAngle; angle += angle_step) {
		int nx = x + int(xradius * cos(angle * PI_CONV));
		int ny = y - int(xradius * sin(angle * PI_CONV));
		drawLine(nx, ny, lx,ly);
		lx = nx, ly = ny;
	}

	drawLine(
		x + int(xradius * cos((startAngle + arcAngle) * PI_CONV)),
		y - int(xradius * sin((startAngle + arcAngle) * PI_CONV)),
		lx, ly);
}

vm_graphic_point polygon_buf[360 + 1];
void Graphics::fillArc(int x, int y, int w, int h, int startAngle, int arcAngle)
{
	if (startAngle == 0 && arcAngle == 360) {
		//vm_graphic_fill_ellipse_ex(layer_handle, x, y, w, h);
		//return;
	}

	int xradius = w / 2, yradius = h / 2;
	x += xradius;
	y += yradius;
	if (xradius == 0 && yradius == 0) {
		return;
	}

	if (arcAngle > 360)
		return;

	// draw complete ellipse if (0, 360) specified
	// if (startAngle == 0 && arcAngle == 360) {
	//     _ellipse(x, y, xradius, yradius);
	//     return;
	// }

	polygon_buf[0].x = x;
	polygon_buf[0].y = y;

	int polygon_count = 1;
	

	for (int angle = startAngle; angle < startAngle + arcAngle; angle+=5) {
		polygon_buf[polygon_count].x = x + int(xradius * cos(angle * PI_CONV));
		polygon_buf[polygon_count].y = y - int(xradius * sin(angle * PI_CONV));
		polygon_count++;
	}

	vm_graphic_fill_polygon(layer_handle, polygon_buf, polygon_count);
}

// void Graphics::fillArc(int x, int y, int w, int h, int startAngle, int arcAngle) {
//     // NOTE this impl assumes startAngle < arcAngle
//     int  _x, _y,      // circle centered point
//         xx,yy,rr,   // x^2,y^2,r^2
//         ux,uy,      // u
//         vx,vy,      // v
//         sx,sy;      // pixel position

//     arcAngle += startAngle;

//     (void)w; (void)h;
//     int r = 30; // TODO
//     rr = r*r;
//     ux = double(r)*cos(double(startAngle)*PI_CONV);
//     uy = double(r)*sin(double(startAngle)*PI_CONV);
//     vx = double(r)*cos(double(arcAngle)*PI_CONV);
//     vy = double(r)*sin(double(arcAngle)*PI_CONV);

//     if (abs(arcAngle - startAngle) < 180) { // small pie
//         for (_y = -r, yy = _y*_y, sy = y + _y; _y <= +r; _y++, yy = _y*_y, sy++)
//             for (_x = -r, xx = _x*_x, sx = x + _x; _x <= +r; _x++, xx = _x*_x, sx++)
//                 if (xx + yy <= rr)           // inside circle
//                     if (((_x*uy) - (_y*ux) <= 0)  // x,y is above a0 in clockwise direction
//                         && ((_x*vy) - (_y*vx) >= 0)) // x,y is below a1 in counter clockwise direction
//                         _putpixel(sx, sy);
//     } else { // big pie
//         for (_y = -r, yy = _y*_y, sy = y + _y; _y <= +r; _y++, yy = _y*_y, sy++)
//             for (_x = -r, xx = _x*_x, sx = x + _x; _x <= +r; _x++, xx = _x*_x, sx++)
//                 if (xx + yy <= rr)           // inside circle
//                     if (((_x*uy) - (_y*ux) <= 0)  // x,y is above a0 in clockwise direction
//                         || ((_x*vy) - (_y*vx) >= 0)) // x,y is below a1 in counter clockwise direction
//                         _putpixel(sx, sy);
//     }
// }

// int norm_ang(int angle) {
// // reduce the angle
// angle =  angle % 360;

// // force it to be the positive remainder, so that 0 <= angle < 360
// angle = (angle + 360) % 360;

// // force into the minimum absolute value residue class, so that -180 < angle <= 180
// if (angle > 180)
//     angle -= 360;
// return angle;
// }

int to_360(int ang)
{
	// if (ang != 0 && ang % 360 == 0) {
	//     ang = 360;
	// } else {
	//     ang %= 360;
	// }
	if (ang >= 0 && ang <= 360) {
		return ang;
	}
	if (ang < 0) {
		ang += 360;
	}
	return ang;
}



//void Graphics::fillArc(int x, int y, int w, int h, int startAngle, int arcAngle)
//{
//	int endAngle = startAngle + arcAngle;
//	// startAngle = norm_ang(startAngle);
//	// endAngle = norm_ang(endAngle);
//	// SDL_Log("startAngle = %d, endAngle = %d\n", startAngle, endAngle);
//	double a = w / 2.0, b = h / 2.0;
//	double e = sqrt(1.0 - (b * b) / (a * a));
//	for (int _y = y - b; _y < y + b; _y++) {
//		for (int _x = x - a; _x < x + a; _x++) {
//			// _putpixel(_x, _y);
//			// std::cout << atan2(_y, _x) << "\n";
//			// SDL_Log("_y = %d, _x = %d atan2 = %lf\n", _y, _x, atan2(_y - y, _x - x));
//			// if (atan2(_y - y, _x - x) >= startAngle*PI_CONV && atan2(_y - y, _x - x) <= endAngle*PI_CONV) {
//			//     _putpixel(_x, _y);
//			// }
//			// if (atan2(_y - y, _x - x) < 3.14/2.0) {
//			//     _putpixel(_x, _y);
//			// }
//			double ang = atan2(-(_y - y), _x - x); // cuz in screen y grows downwards (in maths y grows upwards)
//
//			// double rad = b/sqrt(1 - e*e*cos(ang)*cos(ang));
//			// double dist = sqrt((_x - x)*(_x - x) + (_y - y)*(_y - y));
//			double rad = b * b / (1 - e * e * cos(ang) * cos(ang));
//			double dist = ((_x - x) * (_x - x) + (_y - y) * (_y - y));
//
//			int ang2 = to_360(ang / PI_CONV);
//
//			if (ang2 >= to_360(startAngle)
//				&& ang2 <= to_360(endAngle)
//				&& dist <= rad) {
//				_putpixel(_x, _y);
//			}
//
//			if (endAngle > 360) {
//				if (ang2 < endAngle % 360 && dist <= rad) {
//					_putpixel(_x, _y);
//				}
//			}
//		}
//	}
//}

void Graphics::_putpixel(int x, int y)
{
	vm_graphic_set_pixel_ex(layer_handle, x, y);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2)
{
	vm_graphic_line_ex(layer_handle, x1, y1, x2, y2);
}

void Graphics::drawImage(Image* const image, int x, int y, int anchor)
{
	x = getAnchorX(x, image->getWidth(), anchor);
	y = getAnchorY(y, image->getHeight(), anchor);

	vm_graphic_blt(layer_buf, x, y, image->getSurface(), 0, 0, image->getWidth(), image->getHeight(), 1);
}

int Graphics::getAnchorX(int x, int size, int anchor)
{
	if ((anchor & LEFT) != 0) {
		return x;
	}
	if ((anchor & RIGHT) != 0) {
		return x - size;
	}
	if ((anchor & HCENTER) != 0) {
		return x - size / 2;
	}
	throw std::runtime_error("unknown xanchor = " + std::to_string(anchor));
}

int Graphics::getAnchorY(int y, int size, int anchor)
{
	if ((anchor & TOP) != 0) {
		return y;
	}
	if ((anchor & BOTTOM) != 0) {
		return y - size;
	}
	if ((anchor & VCENTER) != 0) {
		return y - size / 2;
	}
	throw std::runtime_error("unknown yanchor = " + std::to_string(anchor));
}
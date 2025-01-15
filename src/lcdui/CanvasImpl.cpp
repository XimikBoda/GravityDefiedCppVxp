#include "CanvasImpl.h"

#include <stdexcept>
//#include <iostream>

#include "Canvas.h"
#include "..\utils\Time.h"
#include <vmgraph.h>
#include <vmio.h>

extern VMINT layer_hdl[1];
static Canvas* g_canvas = 0;

static int convertKeyCharToKeyCode(int keyCode)
{
	switch (keyCode) {
	case VM_KEY_OK:
	case VM_KEY_NUM5:
		return Canvas::Keys::FIRE;
	case VM_KEY_LEFT:
	case VM_KEY_NUM4:
		return Canvas::Keys::LEFT;
	case VM_KEY_RIGHT:
	case VM_KEY_NUM6:
		return Canvas::Keys::RIGHT;
	case VM_KEY_UP:
	case VM_KEY_NUM2:
		return Canvas::Keys::UP;
	case VM_KEY_DOWN:
	case VM_KEY_NUM8:
		return Canvas::Keys::DOWN;
	default:
		return 0;
	}
}

static void handle_keyevt(VMINT event, VMINT keycode) {
#ifdef WIN32 //Fix for MoDis 
	if (keycode >= VM_KEY_NUM1 && keycode <= VM_KEY_NUM3)
		keycode += 6;
	else if (keycode >= VM_KEY_NUM7 && keycode <= VM_KEY_NUM9)
		keycode -= 6;
#endif

	int keyCode = convertKeyCharToKeyCode(keycode);

	switch (event) {
	case VM_KEY_EVENT_DOWN:
	case VM_KEY_EVENT_LONG_PRESS:
	case VM_KEY_EVENT_REPEAT:
		if (keyCode != 0)
			g_canvas->publicKeyPressed(keyCode);
		break;
	case VM_KEY_EVENT_UP:
		if (keyCode != 0)
			g_canvas->publicKeyReleased(keyCode);
		if (keycode == VM_KEY_LEFT_SOFTKEY)
			g_canvas->pressedEsc();
		break;
	}
}

static void handle_penevt(VMINT event, VMINT x, VMINT y) {
	switch (event) {
	case VM_PEN_EVENT_TAP:
		g_canvas->publicPointerPressed(x, y);
		break;
	case VM_PEN_EVENT_MOVE:
	case VM_PEN_EVENT_REPEAT:
	case VM_PEN_EVENT_LONG_TAP:
	case VM_PEN_EVENT_DOUBLE_CLICK:
		g_canvas->publicPointerDragged(x, y);
		break;
	case VM_PEN_EVENT_RELEASE:
	case VM_PEN_EVENT_ABORT:
		g_canvas->publicPointerReleased(x, y);
		break;
	}
}

CanvasImpl::CanvasImpl(Canvas* canvas)
{
	this->canvas = canvas;
	g_canvas = canvas;

	width = vm_graphic_get_screen_width();
	height = vm_graphic_get_screen_height();

	vm_reg_keyboard_callback(handle_keyevt);
	vm_reg_pen_callback(handle_penevt);
}

CanvasImpl::~CanvasImpl()
{

}

void CanvasImpl::repaint()
{
	vm_graphic_flush_layer(layer_hdl, 1);
}

void CanvasImpl::processEvents()
{
	Time::sleep(0);
}

int CanvasImpl::getWidth()
{
	return width;
}

int CanvasImpl::getHeight()
{
	return height;
}

bool CanvasImpl::hasPointerEvents()
{
	return vm_is_support_pen_touch();
}

VMINT CanvasImpl::getRenderer()
{
	return layer_hdl[0];
}

void CanvasImpl::setWindowTitle(const std::string& title)
{
}
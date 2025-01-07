#include "CanvasImpl.h"

#include <stdexcept>
#include <iostream>

#include "Canvas.h"
#include <vmgraph.h>

extern VMINT layer_hdl[1];

CanvasImpl::CanvasImpl(Canvas* canvas)
{
    this->canvas = canvas;

    width = vm_graphic_get_screen_width();
    height = vm_graphic_get_screen_height();
}

CanvasImpl::~CanvasImpl()
{
    
}

void CanvasImpl::repaint()
{
    vm_graphic_flush_layer(layer_hdl, 1);
}

int CanvasImpl::getWidth()
{
    return width;
}

int CanvasImpl::getHeight()
{
    return height;
}

VMINT CanvasImpl::getRenderer()
{
    return layer_hdl[0];
}

//void CanvasImpl::processEvents()
//{
//    SDL_Event e;
//
//    while (SDL_PollEvent(&e) != 0) {
//        switch (e.type) {
//        case SDL_QUIT:
//            exit(0); // IMPROVE This is a super dumb way to finish the game, but it works
//            break;
//        case SDL_KEYDOWN: {
//            int keyCode = convertKeyCharToKeyCode(e.key.keysym.sym);
//            // std::cout << "Key pressed: " << keyCode << std::endl;
//            if (keyCode != 0) {
//                canvas->publicKeyPressed(keyCode);
//            }
//        } break;
//        case SDL_KEYUP: {
//            int sdlCode = e.key.keysym.sym;
//            int keyCode = convertKeyCharToKeyCode(sdlCode);
//            // std::cout << "Key released: " << keyCode << std::endl;
//            if (keyCode != 0) {
//                canvas->publicKeyReleased(keyCode);
//            } else {
//                if (sdlCode == SDLK_ESCAPE) {
//                    // std::cout << "ESC released" << std::endl;
//                    canvas->pressedEsc();
//                }
//            }
//        } break;
//        default:
//            break;
//        }
//    }
//}

//int CanvasImpl::convertKeyCharToKeyCode(SDL_Keycode keyCode)
//{
//    switch (keyCode) {
//    case SDLK_RETURN:
//        return Canvas::Keys::FIRE;
//    case SDLK_LEFT:
//        return Canvas::Keys::LEFT;
//    case SDLK_RIGHT:
//        return Canvas::Keys::RIGHT;
//    case SDLK_UP:
//        return Canvas::Keys::UP;
//    case SDLK_DOWN:
//        return Canvas::Keys::DOWN;
//    default:
//        std::cout << "unknown keyEvent: " << keyCode << std::endl;
//        return 0;
//    }
//}

void CanvasImpl::setWindowTitle(const std::string& title)
{
   // SDL_SetWindowTitle(window, title.c_str());
}
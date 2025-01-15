#pragma once

#include <memory>
#include <vector>
#include <unordered_set>

#include "Displayable.h"
#include "Command.h"

class CanvasImpl;
class Graphics;

class Canvas : public Displayable {
private:
    std::unique_ptr<CanvasImpl> impl;
    std::unique_ptr<Graphics> graphics; // IMPROVE this is probably not the best place for graphics
    CommandListener* commandListener;

    std::unordered_set<Command*, Command::HashFunction, Command::EqualFunction> currentCommands;

public:
    enum Keys {
        UP = 1,
        DOWN = 6,
        LEFT = 2,
        RIGHT = 5,
        FIRE = 8
    };

    Canvas();
    ~Canvas();
    bool isShown() override;
    int getWidth() override;
    int getHeight() override;
    bool hasPointerEvents();
    void setWindowTitle(const std::string& title);
    CanvasImpl* getCanvasImpl();
    void repaint();
    void serviceRepaints();
    int getGameAction(int keyCode);
    void removeCommand(Command* command);
    void addCommand(Command* command);
    void setCommandListener(CommandListener* listener);
    void publicKeyPressed(int keyCode);
    void publicKeyReleased(int keyCode);
    void publicPointerPressed(int x, int y);
    void publicPointerReleased(int x, int y);
    void publicPointerDragged(int x, int y);
    void pressedEsc();
    virtual void paint(Graphics* g) = 0;
    virtual void keyPressed(int keyCode) = 0;
    virtual void keyReleased(int keyCode) = 0;
    virtual void pointerPressed(int x, int y) = 0;
    virtual void pointerReleased(int x, int y) = 0;
    virtual void pointerDragged(int x, int y) = 0;
};
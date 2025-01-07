cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "src")

add_library(${PROJECT_NAME} STATIC 
    utils/Time.cpp
    utils/EmbedFileStream.cpp
    main.cpp
    MathF16.cpp
    GameCanvas.cpp
    GamePhysics.cpp
    TimerOrMotoPartOrMenuElem.cpp
    class_10.cpp
    GameLevel.cpp
    LevelLoader.cpp
    Micro.cpp
    TextRender.cpp
    GameMenu.cpp
    SettingsStringRender.cpp
    MenuManager.cpp
    RecordManager.cpp
    Timer.cpp
    lcdui/CanvasImpl.cpp
    lcdui/Canvas.cpp
    lcdui/Graphics.cpp
    lcdui/Image.cpp
    lcdui/Font.cpp
    lcdui/Command.cpp
    lcdui/FontStorage.cpp
    rms/RecordEnumerationImpl.cpp
    rms/RecordStore.cpp
)

target_link_libraries(${PROJECT_NAME} mreapi)
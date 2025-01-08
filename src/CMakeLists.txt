cmake_minimum_required (VERSION 3.8)

set(PROJECT_NAME "src")

add_library(${PROJECT_NAME} STATIC 
    utils/Time.cpp
    utils/Time.h
    utils/EmbedFileStream.cpp
    utils/EmbedFileStream.h
    utils/FileStream.h
    utils/FileSystem.cpp
    utils/FileSystem.h
    utils/String.h
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

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()

target_link_libraries(${PROJECT_NAME} mreapi mreapi libco)
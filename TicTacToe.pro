LIBS += \
    -lGLEW \
    -lglfw \
    -lGL

QMAKE_CXXFLAGS += \
    -std=c++11 \
    -std=gnu++11

SOURCES += \
    main.cpp \
    window.cpp \
    board.cpp \
    lodepng.cpp \
    loadtexture.cpp \
    setupprogram.cpp \
    setupgame.cpp \
    playgame.cpp \
    winscreen.cpp \
    draw.cpp \
    mousekeyboard.cpp \
    ai.cpp \
    playerselection.cpp

HEADERS += \
    window.hpp \
    board.hpp \
    lodepng.h \
    loadtexture.hpp \
    setupprogram.hpp \
    playgame.hpp \
    setupgame.hpp \
    gameenums.hpp \
    winscreen.hpp \
    draw.hpp \
    mousekeyboard.hpp \
    ai.hpp \
    playerselection.hpp

OTHER_FILES += \
    textured.vs \
    textured.fs \
    notexture.vs \
    notexture.fs

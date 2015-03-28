TEMPLATE = app
TARGET = TQCanDebugger
QT += core \
    gui
HEADERS += TQInputMethod.h \
    src/uiSetCanPara.h \
    src/can_config.h \
    src/ThreadRec.h \
    tqcandebugger.h
SOURCES += src/uiSetCanPara.cpp \
    src/ThreadRec.cpp \
    main.cpp \
    tqcandebugger.cpp
FORMS += 
RESOURCES += 
LIBS += -L. \
	-lTQInputMethod

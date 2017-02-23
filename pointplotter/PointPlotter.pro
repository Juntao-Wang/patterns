HEADERS = Point.h \
	pointList.h \
	mainWindow.h

SOURCES = mainWindow.cpp\
	PointPlotter.cpp \
    pointlist.cpp \
    point.cpp


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
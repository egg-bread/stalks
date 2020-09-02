CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -Werror=vla ${PY}
PYHEADER = /usr/local/Cellar/python@3.7/3.7.8_1/Frameworks/Python.framework/Versions/3.7/Headers
PYLIB = /usr/local/Cellar/python@3.7/3.7.8_1/Frameworks/Python.framework/Versions/3.7/lib
PYVER = python3.7
PY = -I ${PYHEADER} -DWITHOUT_NUMPY -L ${PYLIB} -l${PYVER}
EXEC = stalks
OBJECTS = sellprice.o turnip.o csv.o turnipexception.o turnipart.o turnippatterns.o turniphelper.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
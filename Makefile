CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -Werror=vla 
PYHEADER = /usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/include/python3.7m
PYLIB = /usr/local/Cellar/python/3.7.7/Frameworks/Python.framework/Versions/3.7/lib
PYVER = -lpython3.7
PY = -I ${PYHEADER} -DWITHOUT_NUMPY -L ${PYLIB} ${PYVER}
EXEC = stalks
OBJECTS = sellprice.o turnip.o csv.o turnipexception.o turnipart.o turnippatterns.o turniphelper.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${PY}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
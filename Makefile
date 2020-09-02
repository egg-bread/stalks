CXX = g++
CXXFLAGS = -std=c++17 -Wall -MMD -Werror=vla
EXEC = stalks
OBJECTS = sellprice.o turnip.o csv.o turnipexception.o turnipart.o turnippatterns.o turniphelper.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
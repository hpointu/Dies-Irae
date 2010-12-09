CXX = 		g++
LD = 			g++
LDFLAGS = 	-lsfml-graphics -lsfml-window -lsfml-system -lBox2D

SRC =		main.cpp \
			PausableClock.cpp \
			World.cpp \
			DBloc.cpp \
			Bloc.cpp \
			Application.cpp \
			Canon.cpp \
			Ball.cpp \
			Entity.cpp \
			ContactListener.cpp \
			Ground.cpp

BIN = 	DiesIrae

OBJ = 	$(SRC:.cpp=.o)
DEP = 	$(SRC:.cpp=.d)

%.o: %.cpp
	$(CXX) -O1 -g -o $@ -c $<

%.d: %.cpp
	$(CXX) $< -MM -o $@

all: $(BIN)

$(BIN): $(OBJ)
	$(LD) -o $@ $+ $(LDFLAGS)

clean:
	@rm *.o *.d

-include $(DEP)

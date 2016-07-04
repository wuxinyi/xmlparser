.PHONY : all clean ctags xml 

TARGET  = main
OBJECTS = main.o \
					3Party/tinyxml2/tinyxml2.o\

CXXFLAGS = -I./src -I./3Party/tinyxml2 -I./3Party/lua  -g --std=c++11
LDFLAGS  = -L./3Party/lua -llua -ldl

all:$(TARGET)

$(TARGET):$(OBJECTS) lualib
	$(CXX) $(OBJECTS) -o$@ $(LDFLAGS)

$(OBJECTS):%.o:%.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o$@

lualib:
	@cd 3Party/lua ; make linux

clean:
	$(RM) -rf $(TARGET) $(OBJECTS)
	@cd 3Party/lua ; make clean
	@cd 3Party/tinyxml2 ; make clean

xml:
	@rm -rf main.o main;cd tools;python xmltool.py

ctags:
	@ctags -R .

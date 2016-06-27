.PHONY : all clean ctags cpp11

TARGET  = main
OBJECTS = main.o \
					tinyxml2/tinyxml2.o\

CXXFLAGS = -I./src -I./tinyxml2 -g --std=c++11 

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o$@

clean:
	$(RM) -rf $(TARGET) $(OBJECTS)

ctags:
	@ctags -R .

cpp11: CXXFLAGS += -std=c++11
cpp11: $(OBJECT)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o$@

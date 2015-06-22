SOURCE_PATH=src
BUILD_PATH=build
INCLUDE_PATH=include
FILES=main.cpp image.cpp sink.cpp source.cpp PNMreader.cpp PNMwriter.cpp filters.cpp filter.cpp logging.cpp
SOURCES = $(FILES:%.cpp=$(SOURCE_PATH)/%.cpp)
OBJ=$(FILES:%.cpp=$(BUILD_PATH)/%.o)

prog: $(OBJ)
	g++ $(OBJ) -o bin/proj

$(BUILD_PATH)/%.o : $(SOURCE_PATH)/%.cpp
	g++ -o $@ -g -I./$(INCLUDE_PATH) -c $<

clean:
	rm $(BUILD_PATH)/*.o bin/proj

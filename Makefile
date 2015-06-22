SOURCE_PATH=src
BUILD_PATH=build
INCLUDE_PATH=include
FILES=main.cpp image.cpp sink.cpp source.cpp PNMreader.cpp PNMwriter.cpp filters.cpp filter.cpp logging.cpp
SOURCES = $(FILES:%.cpp=$(SOURCE_PATH)/%.cpp)
OBJ=$(FILES:%.cpp=$(BUILD_PATH)/%.o)

prog: folders $(OBJ)
	g++ $(OBJ) -o bin/proj

$(BUILD_PATH)/%.o : $(SOURCE_PATH)/%.cpp
	g++ -o $@ -g -I./$(INCLUDE_PATH) -c $<

folders:
	mkdir -p bin build log

clean:
	rm -f $(BUILD_PATH)/*.o bin/proj
	rm -rf $(BUILD_PATH)
	rm -rf bin
	rm -rf log

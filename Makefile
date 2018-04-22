CFLAGS = g++  -Wall -g -std=c++11
OBJECTS = ./build/Image.o
DRIVER = ./build/driver.o
TEST_PATH = ./tests
# TEST_OBJECTS = ./build/test_Image.o
LIB = ./lib
SRC = ./src
BUILD = ./build

imageops: $(OBJECTS) $(DRIVER) #builds program
	$(CFLAGS) $(OBJECTS) $(DRIVER) -o imageops

test_objects: $(TEST_OBJECTS) $(OBJECTS) #builds tester
	$(CFLAGS) $(OBJECTS) $(TEST_OBJECTS) -o test

tests: | imageops test_objects test

$(BUILD)/%.o: $(SRC)/%.cpp #builds driver
	$(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(LIB)/%.cpp #builds lib files
	$(CFLAGS) -c $< -o $@

$(BUILD)/%.o: $(TEST_PATH)/%.cpp #builds test objects
	$(CFLAGS) -c $< -o $@

run:
	./imageops ./res/shrek_rectangular.pgm outfile.pgm
	# ./imageops outfile.pgm test.pgm

clean: 
	rm -f imageops test ./build/*
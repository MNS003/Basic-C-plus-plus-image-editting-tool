CFLAGS = g++  -Wall -g -std=c++11
OBJECTS = ./build/Image.o
DRIVER = ./build/driver.o
TEST_PATH = ./tests
TEST_OBJECTS = ./build/test_Image.o
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
	./imageops -a ./res/Lenna_standard.pgm ./res/Lenna_hat_mask.pgm
	./imageops -s ./res/Lenna_standard.pgm ./res/Lenna_hat_mask.pgm
	./imageops -i ./res/Lenna_standard.pgm ./res/Lenna_hat_mask.pgm
	./imageops -l ./res/Lenna_standard.pgm ./res/Lenna_hat_mask.pgm
	./imageops -t ./res/Lenna_standard.pgm ./res/Lenna_hat_mask.pgm

clean: 
	rm -f imageops test ./build/*
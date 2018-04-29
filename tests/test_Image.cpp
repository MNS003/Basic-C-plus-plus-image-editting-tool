#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../lib/Image.h"


using namespace STHMIN003;
using namespace std;

TEST_CASE("ctor with values"){
    SECTION("Default ctor"){

        Image img;

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char* pixels = img.get_pixels();

        REQUIRE(ints[0] == 0);
        REQUIRE(ints[1] == 0);
        REQUIRE(ints[2] == 0);
        REQUIRE(ints[3] == 0);
        REQUIRE(strings[0] == "");
        REQUIRE(strings[1] == "");
    }
    SECTION("blank image ctor"){
        int width = 100, height = 200;
        Image img(width,height);

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char *pixels = img.get_pixels();

        REQUIRE(ints[0] == 100);
        REQUIRE(ints[1] == 200);
        REQUIRE(ints[2] == 255);
        REQUIRE(ints[3] == 20000);
        REQUIRE(strings[0] == "P5");
        REQUIRE(strings[1] == "#Default blank image");
    }
    SECTION("ctor with filename + load"){
        // int width, height, max_value, size;
        // string version, comments;
        // unique_ptr<unsigned char[]> pixels;
        Image img("./tests/Lenna_standard.pgm");

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char *pixels = img.get_pixels();

        REQUIRE(ints[0] == 512);
        REQUIRE(ints[1] == 512);
        REQUIRE(ints[2] == 255);
        REQUIRE(ints[3] == 512*512);
        REQUIRE(strings[0] == "P5");
        REQUIRE(strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");
    }
    SECTION("copy ctor"){
        Image img("./tests/Lenna_standard.pgm");
        Image other(img);

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char *pixels = img.get_pixels();
        vector<int> other_ints = other.get_ints();
        vector<string> other_strings = other.get_strings();
        // unsigned char *pixels = img.get_pixels();

        REQUIRE(ints[0] == 512);
        REQUIRE(ints[1] == 512);
        REQUIRE(ints[2] == 255);
        REQUIRE(ints[3] == 512 * 512);
        REQUIRE(strings[0] == "P5");
        REQUIRE(strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");

        REQUIRE(other_ints[0] == 512);
        REQUIRE(other_ints[1] == 512);
        REQUIRE(other_ints[2] == 255);
        REQUIRE(other_ints[3] == 512 * 512);
        REQUIRE(other_strings[0] == "P5");
        REQUIRE(other_strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");
    }
    SECTION("copy assignment ctor"){
        Image img("./tests/Lenna_standard.pgm");
        Image other = img;

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char *pixels = img.get_pixels();
        vector<int> other_ints = other.get_ints();
        vector<string> other_strings = other.get_strings();
        // unsigned char *pixels = img.get_pixels();

        REQUIRE(ints[0] == 512);
        REQUIRE(ints[1] == 512);
        REQUIRE(ints[2] == 255);
        REQUIRE(ints[3] == 512 * 512);
        REQUIRE(strings[0] == "P5");
        REQUIRE(strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");

        REQUIRE(other_ints[0] == 512);
        REQUIRE(other_ints[1] == 512);
        REQUIRE(other_ints[2] == 255);
        REQUIRE(other_ints[3] == 512 * 512);
        REQUIRE(other_strings[0] == "P5");
        REQUIRE(other_strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");
    }
    SECTION("move ctor"){
        Image img("./tests/Lenna_standard.pgm");
        Image other(move(img));

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char *pixels = img.get_pixels();
        vector<int> other_ints = other.get_ints();
        vector<string> other_strings = other.get_strings();
        // unsigned char *pixels = img.get_pixels();

        REQUIRE(ints[0] == 0);
        REQUIRE(ints[1] == 0);
        REQUIRE(ints[2] == 0);
        REQUIRE(ints[3] == 0);
        REQUIRE(strings[0] == "");
        REQUIRE(strings[1] == "");

        REQUIRE(other_ints[0] == 512);
        REQUIRE(other_ints[1] == 512);
        REQUIRE(other_ints[2] == 255);
        REQUIRE(other_ints[3] == 512 * 512);
        REQUIRE(other_strings[0] == "P5");
        REQUIRE(other_strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");
    }
    SECTION("move assignment ctor"){
        Image img("./tests/Lenna_standard.pgm");
        Image other = move(img);

        vector<int> ints = img.get_ints();
        vector<string> strings = img.get_strings();
        // unsigned char *pixels = img.get_pixels();
        vector<int> other_ints = other.get_ints();
        vector<string> other_strings = other.get_strings();
        // unsigned char *pixels = img.get_pixels();

        REQUIRE(ints[0] == 0);
        REQUIRE(ints[1] == 0);
        REQUIRE(ints[2] == 0);
        REQUIRE(ints[3] == 0);
        REQUIRE(strings[0] == "");
        REQUIRE(strings[1] == "");

        REQUIRE(other_ints[0] == 512);
        REQUIRE(other_ints[1] == 512);
        REQUIRE(other_ints[2] == 255);
        REQUIRE(other_ints[3] == 512 * 512);
        REQUIRE(other_strings[0] == "P5");
        REQUIRE(other_strings[1] == "# CREATOR: GIMP PNM Filter Version 1.1");
    }
}

#endif

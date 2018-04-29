#include <string>
#include <memory>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Image.h"

using namespace std;

namespace STHMIN003{

    //default ctor
    Image::Image(){
        cout << "default ctor" << endl;
        width = height = max_value = size = 0;
        pixels = unique_ptr<unsigned char []>(new unsigned char[width*height]);
    }
    //ctor for blank image
    Image::Image(int w, int h){
        cout << "ctor width and height" << endl;
        version = "P5";
        width = w;
        height = h;
        max_value = 255;
        comments = "#Default blank image";
        size = width*height;
        pixels = unique_ptr<unsigned char []>(new unsigned char[size]);
    }
    //dtor
    Image::~Image(){
        cout << "dtor" << endl;
        width = height = max_value = size = 0;
    }
    //ctor with filename
    Image::Image(string filename){
        cout << "ctor with file name" << endl;
        load(filename);
    }
    //copy ctor
    Image::Image(const Image & other){
        cout << "copy ctor" << endl;
        size = other.size;
        width = other.width;
        height = other.height;
        version = other.version;
        comments = other.comments;
        max_value = other.max_value;
        pixels = unique_ptr<unsigned char []>(new unsigned char[width*height]);
        for(int i=0 ; i < size; ++i)
            pixels[i] = other.pixels[i];
    }
    //copy assignment ctor
    Image & Image::operator=(const Image & other){
        cout << "copy assign" << endl;
        if(this != &other){
            size = other.size;
            width = other.width;
            height = other.height;
            version = other.version;
            comments = other.comments;
            max_value = other.max_value;
            pixels = unique_ptr<unsigned char []>(new unsigned char[width*height]);
            size = width * height;
            for(int i=0 ; i < size; ++i)
                pixels[i] = other.pixels[i];
        }
        return *this;
    }
    //move ctor
    Image::Image(Image && other){
        cout << "move ctor" << endl;
        size = other.size;
        width = other.width;
        height = other.height;
        version = move(other.version);
        comments = move(other.comments);
        max_value = other.max_value;
        pixels = unique_ptr<unsigned char []>(new unsigned char[width*height]);
        size = width * height;
        for(int i=0 ; i < size; ++i)
            pixels[i] = other.pixels[i];
        other.size = other.width = other.height = other.max_value = 0;
    }
    //move asssignment ctor
    Image & Image::operator=(Image && other){
        cout << "move assign" << endl;
        if(this != &other){
            size = other.size;
            width = other.width;
            height = other.height;
            max_value = other.max_value;
            version = move(other.version);
            comments = move(other.comments);
            max_value = other.max_value;
            pixels = unique_ptr<unsigned char[]>(new unsigned char[width * height]);
            size = height * width;
            for(int i=0 ; i < size; ++i)
                pixels[i] = other.pixels[i];

            other.size = other.width = other.height = other.max_value = 0;
        }
        return *this;
    }
    
    //addition
    Image Image::operator+(const Image & other){
        cout << "operator+" << endl;
        Image result(*this);
        for(int j = 0; j < size; ++j)
            if( (int) pixels[j] + (int) other.pixels[j] < max_value)
                result.pixels[j] = (unsigned char) ((int) pixels[j] + (int) other.pixels[j]);
            else
                result.pixels[j] = max_value;
        return result;
    }
    Image Image::operator+(const Image && other){
        cout << "operator+" << endl;
        Image result(*this);
        for(int j = 0; j < size; ++j)
            if ((int)pixels[j] + (int)other.pixels[j] < max_value)
                result.pixels[j] = (unsigned char) ((int) pixels[j] - (int) other.pixels[j]);
            else
                result.pixels[j] = 0;
        return result;
    }

    //subtraction
    Image Image::operator-(const Image & other){
        cout << "operator-" << endl;
        Image result(*this);
        for(int j = 0; j < size; ++j)
            if( (int) pixels[j] - (int) other.pixels[j] > 0)
                result.pixels[j] = (unsigned char) ((int) pixels[j] - (int) other.pixels[j]);
            else
                result.pixels[j] = 0;
        return result;
    }
    Image Image::operator-(const Image && other){
        cout << "operator-" << endl;
        Image result(*this);
        for(int j = 0; j < size; ++j)
            if ((int)pixels[j] - (int)other.pixels[j] > 0)
                result.pixels[j] = (unsigned char)((int)pixels[j] - (int)other.pixels[j]);
            else
                result.pixels[j] = 0;
        return result;
    }

    //inversion
    Image Image::operator!(){
        cout << "operator!" << endl;
        for(int j = 0; j < size; ++j)
            pixels[j] = (unsigned char)( 255 - (int)pixels[j]);
        return *this;
    }
 
    //mask
    Image Image::operator/(const Image &&other){
        cout << "operator/" << endl;
        Image result(*this);
        for(int j = 0; j < size ; ++j){
            unsigned char tmp = other.pixels[j];
            if (abs((int)tmp - max_value) < 0.000001)
                result.pixels[j] = (unsigned char)(pixels[j]);
            else
                result.pixels[j] = (unsigned char)0;
        }
        return result;
    }
    Image Image::operator/(const Image &other){
        cout << "operator/" << endl;
        Image result(*this);
        for(int j = 0; j < size ; ++j){
            unsigned char tmp = other.pixels[j];
            if (abs((int)tmp - max_value) < 0.000001)
                result.pixels[j] = (unsigned char)(pixels[j]);
            else
                result.pixels[j] = (unsigned char)0;
        }
        return result;
    }

    //threshold
    Image Image::operator*(int f){//image = img * 5
        cout << "operator*" << endl;
        Image result(*this);
        for(int j = 0; j < size; ++j)
            if ((int)pixels[j] > f)
                result.pixels[j] = (unsigned char)255;
            else
                result.pixels[j] = (unsigned char)0;
        return result;
    } 
    Image Image::operator*(int & f){ //image = img * f
        cout << "operator*" << endl;
        Image result(*this);
        for(int j = 0; j < size; ++j)
            if ((int)pixels[j] > f)
                result.pixels[j] = (unsigned char)255;
            else
                result.pixels[j] = (unsigned char)0;
        return result;
    }

    //filter
    Image Image::operator%(int f){  //image = img % 5
        return *this;
    } 
    Image Image::operator%(int &f){ //image = img % f
        return *this;
    } 

    //stream out
    ostream &operator<<(ostream &out, const Image &other){
        out << "version: " << other.version << endl
            << "comments: " << other.comments
            << "width: " << other.width << " height: " << other.height << " " << endl
            << "max value: " << other.max_value << flush;
            return out;
    }
    //stream in
    istream &operator>>(istream &in, Image &other){//only allow comments, preserve integrity of img
        string line;
        while (getline(in , line))
            other.comments+= "#" + line +"\n";
        return in;
    }
    //load
    void Image::load(string filename){
        // cout << "loading" << endl;
        ifstream ifs(filename,ios::binary|ios::in);
        if(ifs.is_open()){
            string line;
            getline(ifs,line);//pop version

            if(line.compare("P5\n")){
                version = line;
                while(getline(ifs,line) && line[0] == '#'){//pop comments
                    comments += line;
                }

                stringstream ss(line);
                ss >> height >> width;
                size = width * height;

                getline(ifs, line);
                stringstream max(line);
                max >> max_value;

                pixels = unique_ptr<unsigned char[]>(new unsigned char[size]);
                ifs.read(reinterpret_cast<char *>(pixels.get()), size * sizeof(unsigned char)); //get pixel values

            }//end version == "P5"
        }else//end ifs is_open 
            cout << "Could not open file" << endl;
    }
    //save
    void Image::save(string filename){
        cout << "saving... " << width << " " << height << endl;
        ofstream ofs(filename,ios::binary|ios::out);
        if(ofs.is_open()){
            ofs << version << endl
            	<< comments << endl
            	<< to_string(height) +" "+ to_string(width) << endl
            	<< max_value << endl;
            ofs.write(reinterpret_cast<char*>(pixels.get()),size * sizeof(pixels[0]));
        }else{
            cout <<"File not open" << endl;
        }
        ofs.close();

    }

    vector<int> Image::get_ints() { return vector<int>({width, height, max_value, size}); }
    vector<string> Image::get_strings() { return vector<string>({version, comments}); }
    unsigned char* Image::get_pixels() { return pixels.get(); }

    //iterator class

    Image::iterator::iterator(unsigned char *p): ptr(p){

    }
    //copy ctor
    Image::iterator::iterator(const iterator &other){
        ptr = other.ptr;
    }
    //copy assignment
    Image::iterator &Image::iterator::operator=(const iterator &other){
        if(this != &other){
            ptr = other.ptr;
        }
        return *this;
    }
    //move ctor
    Image::iterator::iterator(iterator &&other){
        ptr = move(other.ptr);
    }
    //move assignment
    Image::iterator &Image::iterator::operator=(iterator &&other){
        if(this != &other){
            ptr = move(other.ptr);
        }
        return *this;
    }
    //incriment
    Image::iterator Image::iterator::operator++(){
        ++ptr;
        return *this;
    }
    Image::iterator Image::iterator::operator++(int){
        auto tmp = *this;
        ++ptr;
        return tmp;
    }
    //decriment
    Image::iterator Image::iterator::operator--(){
        --ptr;
        return *this;
    }
    Image::iterator Image::iterator::operator--(int){
        auto tmp = *this;
        --ptr;
        return tmp ;
    }

    bool Image::iterator::operator==(iterator &other){
        return this->ptr == other.ptr;
    }
    bool Image::iterator::operator!=(iterator &other){
        return this->ptr != other.ptr;
    }

    //deref
    unsigned char& Image::iterator::operator*(){
        return *ptr;
    }

    Image::iterator Image::begin(){
        return Image::iterator(pixels.get());
    }

    Image::iterator Image::end(){
        return Image::iterator(&pixels[size]);
    }
}
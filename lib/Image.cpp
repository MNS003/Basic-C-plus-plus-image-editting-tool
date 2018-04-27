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
        width = height = max_value = 0;
        make_vector(width, height);
    }
    //dtor
    Image::~Image(){
        cout << "dtor" << endl;
        width = height = max_value = 0;
    }
    //ctor with filename
    Image::Image(std::string filename){
        cout << "ctor with file name" << endl;
        load(filename);
    }
    //copy ctor
    Image::Image(const Image & other){
        cout << "copy ctor" << endl;
		if(this != &other){
            width = other.width;
            height = other.height;
            version = other.version;
            comments = other.comments;
            max_value = other.max_value;
            make_vector(width, height);
            int size = width * height;
            for(int i=0 ; i < size; ++i)
                pixels[i] = other.pixels[i];
        }
    }
    //copy assignment ctor
    Image & Image::operator=(const Image & other){
        cout << "copy assign" << endl;
        if(this != &other){
            width = other.width;
            height = other.height;
            version = other.version;
            comments = other.comments;
            max_value = other.max_value;
            make_vector(width, height);
            int size = width * height;
            for(int i=0 ; i < size; ++i)
                pixels[i] = other.pixels[i];
        }
        return *this;
    }
    //move ctor
    Image::Image(Image && other){
        cout << "move ctor" << endl;
        if(this != &other){
            width = other.width;
            height = other.height;
            version = move(other.version);
            comments = move(other.comments);
            max_value = other.max_value;
            make_vector(width, height);
            int size = width * height;
            for(int i=0 ; i < size; ++i)
                pixels[i] = other.pixels[i];
            other.width = other.height = other.max_value = 0;
        }
    }
    //move asssignment ctor
    Image & Image::operator=(Image && other){
        cout << "move assign" << endl;
        if(this != &other){
            width = other.width;
            height = other.height;
            max_value = other.max_value;
            version = move(other.version);
            comments = move(other.comments);
            max_value = other.max_value;
            make_vector(width,height);
            for(int i=0 ; i < height * width; ++i)
                pixels[i] = other.pixels[i];
            other.width = other.height = other.max_value = 0;
        }
        return *this;
    }
    //addition
    Image Image::operator+(const Image & other){
        cout << "operator+" << endl;
        Image result(*this);
        if(this != &other){
            int size = width * height;
	        for(int j = 0; j < size; ++j)
	            result.pixels[j] = (unsigned char) ((int) pixels[j] + (int) other.pixels[j]);
        }
        return result;
    }
    Image Image::operator+(const Image && other){
        cout << "operator+" << endl;
        Image result(*this);
        if(this != &other){
            int size = width * height;
	        for(int j = 0; j < size; ++j)
	            result.pixels[j] = (unsigned char) ((int) pixels[j] + (int) other.pixels[j]);
        }
        return result;
    }

    //subtraction
    Image Image::operator-(const Image & other){
        cout << "operator-" << endl;
        Image result(*this);
        if(this != &other){
            int size = width * height;
	        for(int j = 0; j < size; ++j)
	            result.pixels[j] = (unsigned char) ((int) pixels[j] - (int) other.pixels[j]);
        }
        return result;
    }
    Image Image::operator-(const Image && other){
        cout << "operator-" << endl;
        Image result(*this);
        if(this != &other){
            int size = width * height;
	        for(int j = 0; j < size; ++j)
	            result.pixels[j] = (unsigned char) ((int) pixels[j] - (int) other.pixels[j]);
        }
        return result;
    }

    //inversion
    Image Image::operator!(){
        cout << "operator!" << endl;
        int size = width * height;
        for(int j = 0; j < size; ++j)
            pixels[j] = (unsigned char)( 255 - (int)pixels[j]);
        return *this;
    }
 
    //mask
    Image Image::operator/(const Image &&other){
        cout << "operator/" << endl;
        Image result(*this);
        int size = width * height;
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
        int size = width * height;
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
        int size = width * height;
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
        int size = width * height;
        for(int j = 0; j < size; ++j)
            if ((int)pixels[j] > f)
                result.pixels[j] = (unsigned char)255;
            else
                result.pixels[j] = (unsigned char)0;
        return result;
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
    void Image::load(std::string filename){
        // cout << "loading" << endl;
        ifstream ifs(filename,ios::binary);

        if(ifs.is_open()){
            string line;
            getline(ifs,line);//pop version

            if(line.compare("P5\n")){
                version = line;
                while(getline(ifs,line) && line[0] == '#'){//pop comments
                    comments += "#" + line +"\n";
                }

                stringstream ss(line);
                ss >> height >> width;

                getline(ifs, line);
                stringstream max(line);
                max >> max_value;

                make_vector(width,height);
                ifs.read(reinterpret_cast<char *>(pixels.get()), width * height * sizeof(unsigned char)); //get pixel values

            }//end version == "P5"
        }else//end ifs is_open 
            cout << "Could not open file" << endl;
    }
    //save
    void Image::save(std::string filename){
        cout << "saving..." << width << " " << height << endl;
        ofstream ofs(filename,ios::binary|ios::out);
        if(ofs.is_open()){
            ofs << version << endl
            	<< comments << endl
            	<< to_string(height) +" "+ to_string(width) << endl
            	<< max_value << endl;
            int array_size = height * height;
            ofs.write(reinterpret_cast<char*>(pixels.get()),array_size * sizeof(pixels));
        }else{
            cout <<"File not open" << endl;
        }
        ofs.close();

    }
    //intialize image vector
    void Image::make_vector(int width, int height){
        cout << "Making vector " << width << " "<< height<< endl;
        pixels = unique_ptr<unsigned char []>(new unsigned char[width*height]);
    }

    class iterator{
        private:
            unsigned char * ptr;
            iterator(unsigned char * p);
        public:
            //copy ctor
            iterator(const iterator & other){

            }
            //copy assignment
            iterator & operator=(const iterator & other){

            }
            //move ctor
            iterator( iterator && other){

            }
            //move assignment
            iterator &operator=(iterator &&other){
                
            }
    };
}
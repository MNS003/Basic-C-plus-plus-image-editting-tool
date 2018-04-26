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
        width = height = 0;
        make_vector(width, height);
    }
    //dtor
    Image::~Image(){
        cout << "dtor" << endl;
        width = height = 0;
        pixels.clear();
    }
    //ctor with vec values
    Image::Image(int width, int height){
        cout << "default ctor" << endl;
        this->width = width;
        this->height = height;
        make_vector(width, height);
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
            make_vector(width, height);
            for(int i=0 ; i < height; ++i)
                for(int j=0 ; j < height; ++j)
                    pixels[i][j] = other.pixels[i][j];
                    // pixels[i][j].reset( other.pixels[i][j].get() );
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
            for(int i=0 ; i < height; ++i)
                for(int j=0 ; j < height; ++j)
                    pixels[i][j] = other.pixels[i][j];
                    // pixels[i][j].reset( other.pixels[i][j].get() );
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
            make_vector(width, height);
            for(int i=0 ; i < height; ++i)
                for(int j=0 ; j < height; ++j)
                    pixels[i][j] = other.pixels[i][j];
                    // pixels[i][j].reset( other.pixels[i][j].get() );
            width = height = 0;
            other.pixels.clear();
        }
    }
    //move asssignment ctor
    Image & Image::operator=(Image && other){
        cout << "move assign" << endl;
        if(this != &other){
            width = other.width;
            height = other.height;
            version = move(other.version);
            comments = move(other.comments);
            for(int i=0 ; i < height; ++i)
                for(int j=0 ; j < height; ++j)
                    pixels[i][j] = other.pixels[i][j];
                    // pixels[i][j].reset( other.pixels[i][j].get() );
            width = height = 0;
            other.pixels.clear();
        }
        return *this;
    }
    //addition
    Image Image::operator+(const Image & other){
        cout << "operator+" << endl;
        Image img(other);
        if(this != &other){
	        for(int j = 0; j < height; ++j)
	            for(int k = 0; k < width; ++k)
	                img.pixels[j][k] = (unsigned char) ((int) pixels[j][k] + (int) other.pixels[j][k]);
        }
        return img;
    }

    //inversion
    Image Image::operator!(){
        cout << "operator!" << endl;
        for(int j = 0; j < height; ++j){
            for(int k = 0; k < width; ++k){
                pixels[j][k] = (unsigned char)( 255 - (int)pixels[j][k]);
                }
        }
        return *this;
    }
 
    //load
    void Image::load(std::string filename){
        cout << "loading" << endl;
        ifstream ifs(filename,ios::binary);

        if(ifs.is_open()){
            string line;
            char tmp;
            cout << "ifs is open" << endl;
            getline(ifs,line);//pop version
            if(line.compare("P5\n")){
                version = line;
                cout << "version P5" << endl;
                while(ifs.get(tmp) && tmp == '#'){//rest of file
                    getline(ifs,line);//pop comments
                    comments += "#" + line +"\n";
                    cout << "Comment " << line << endl;
                }

                getline(ifs,line);
                line = tmp +line;//first digit popped by tmp
                cout << "dimensions" << endl; 
                stringstream ss(line);
                ss >> height >> width;
                cout << width << " " << height << endl;

                getline(ifs, line);
                cout << "max value" << endl;
                stringstream max(line);
                max >> max_value;
                cout << max_value << endl;

                cout << "pixel values" << endl;
                make_vector(width,height);
                for(int j = 0; j < height; ++j){
                    for(int k = 0; k < width; ++k){
                        ifs.read(&tmp,sizeof(tmp));//get pixel values
                        if ( abs((int) tmp - 0) < 0.000001)
                            // pixels[j][k].reset((unsigned char*)'\000');
                            pixels[j][k] = (unsigned char)0;
                        else if( abs((int) tmp - max_value) < 0.000001)
                            // pixels[j][k].reset((unsigned char*)(&max_value));
                            pixels[j][k] = (unsigned char)(max_value);
                        else
                            // pixels[j][k].reset((unsigned char*)(&tmp));
                            pixels[j][k] = (unsigned char)(tmp);
                        // cout << "found " << endl;
                    }///end cols loop
                }//end rows loop
                
                cout << "image read" << endl;
            }//end version == "P5"
        }else//end ifs is_open 
            cout << "Could not open file" << endl;
    }
    //save
    void Image::save(std::string filename){
        cout << "saving.." << endl;
        ofstream ofs(filename,ios::binary|ios::out);
        if(ofs.is_open()){
            ofs << version << endl
            	<< comments << endl
            	<< to_string(height) +" "+ to_string(width) << endl
            	<< max_value << endl;

            for(int j = 0; j < height; ++j){
                for(int k = 0; k < width; ++k)
                    ofs.write(reinterpret_cast<char*>(&pixels[j][k]),sizeof(pixels[j][k]));
            }
            cout << endl;
        }else{
            cout <<"File not open" << endl;
        }
        ofs.close();

    }


    void Image::make_vector(int width, int height){
        cout << "Making vector " << width << " "<< height<< endl;
        pixels.clear();
        for(int j = 0; j < height; ++j){
            // vector< unique_ptr<unsigned char >> row(width);
            vector< unsigned char > row(width);
            pixels.push_back(move(row));
        }
    }
}
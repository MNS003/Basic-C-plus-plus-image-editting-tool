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
        width = height = 0;
        make_vector();
    }
    //dtor
    Image::~Image(){
        width = height = 0;
        pixels.clear();
    }
    //ctor with filename
    Image::Image(std::string filename){
        cout << "ctor with file name" << endl;
        make_vector();
        load(filename);
    }
    //copy ctor
    Image::Image(const Image & other){
		
    }
    //copy assignment ctor
    Image & Image::operator=(const Image & other){

        return *this;
    }
    //move ctor
    Image::Image(Image && other){

    }
    //move asssignment ctor
    Image & Image::operator=(Image && other){
        
        return *this;
    }
    //addition
    Image  Image::operator+(const Image & other){
        if(this != &other){
	        for(int j = 0; j < height; ++j)
	            for(int k = 0; k < width; ++k)
	                pixels[j][k] = (int) pixels[j][k] + (int) other.pixels[j][k];
        }
        return *this;
    }
    //subtraction
    Image Image::operator-(const Image && other){
        
        return *this;
    }
    //inversion
    Image Image::operator!(){
        for(int j = 0; j < height; ++j){
            for(int k = 0; k < width; ++k){
                pixels[j][k] = 255 - pixels[j][k];
                }
        }
        return *this;
    }
    //mask
    Image Image::operator/(const Image && other){
        
        return *this;
    }
    //threshold
    Image Image::operator*(const Image && other){
        
        return *this;
    }
    //stream in
    // ostream & Image::operator<<(const Image && other){
        
    // }
    //stream out
    // ostream &Image::operator>>(const Image && other) {
        
    // }
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
                for(int j = 0; j < height; ++j){
                    for(int k = 0; k < width; ++k){
                        ifs.read(&tmp,sizeof(tmp));//get pixel values
                        if ( abs((int) tmp - 0) < 0.000001)
                            pixels[j][k] = 0;
                        else if( abs((int) tmp - max_value) < 0.000001)
                            pixels[j][k] = max_value;
                        else
                            pixels[j][k] = tmp;
                        
                    }///end cols loop
                }//end rows loop
                
                cout << "image read" << endl;
            }//end version == "P5"
        }else//end ifs is_open 
            cout << "Could not open file" << endl;
    }
    //save
    void Image::save(std::string filename){
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


    void Image::make_vector(){
        for(int i = 0; i < height; ++i){
            // cout << "Making vector " << endl;
            std::unique_ptr <unsigned char []> row( new unsigned char [width] );
            pixels.push_back(move(row));
        }
    }

    // Image::iterator::iterator(unsigned char *p):ptr(p){

    // }

    //copy ctor
    Image::iterator::iterator(const iterator & other){

    }
    //copy assignment
    Image::iterator &Image::iterator::operator=(const Image::iterator & other) {
        
        return *this;
    }
    //move ctor
    Image::iterator::iterator(const iterator && other){}
    //move assignment
    Image::iterator & Image::iterator::operator=(const Image::iterator && other){
        
        return *this;
    }
    //incriment
    Image::iterator & Image::iterator::operator++(){
        
        return *this;
    }
    //decriment
    Image::iterator &Image::iterator::operator--(){
        
        return *this;
    }
    //deref
    // Image Image::iterator::operator*(){
        
    //     //return *this;
    // }

    // Image::iterator begin() {
        
    //     //return *this;
    // }
    // Image::iterator end() {
        
    //     //return *this;
    // }
}
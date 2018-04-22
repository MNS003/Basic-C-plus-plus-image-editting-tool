#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Image.h"

using namespace std;

namespace STHMIN003{

    //default ctor
    Image::Image(){
        width = height = 0;
        pixels = nullptr;
    }
    //dtor
    Image::~Image(){
        width = height = 0;
        pixels = nullptr;
        for(int i = 0; i < height; ++i)
            delete[] pixels.get()[i];
    }
    //ctor with filename
    Image::Image(std::string filename){
        cout << "ctor" << endl;
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
    Image & Image::operator+(const Image && other){
        
        return *this;
    }
    //subtraction
    Image & Image::operator-(const Image && other){
        
        return *this;
    }
    //inversion
    Image & Image::operator!(){
        for(int j = 0; j < height; ++j){
            for(int k = 0; k < width; ++k){
                pixels.get()[j][k] = 255 - pixels.get()[j][k];
                }
        }
        return *this;
    }
    //mask
    Image & Image::operator/(const Image && other){
        
        return *this;
    }
    //threshold
    Image & Image::operator*(const Image && other){
        
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

                pixels = unique_ptr<unsigned char * []>(new unsigned char *[height]);
                cout << "pixel values" << endl;
                for(int j = 0; j < height; ++j){
                    pixels.get()[j] = new unsigned char[width];
                    for(int k = 0; k < width; ++k){
                        ifs.read(&tmp,1);//get pixel values
                        if (tmp < 0)
                            pixels.get()[j][k] = (unsigned char)0;
                        else if(tmp > 255)
                            pixels.get()[j][k] = (unsigned char)255;
                        else
                            pixels.get()[j][k] = (unsigned char)tmp;
                        
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
            ofs << version +'\n' << comments << to_string(height) +" "+ to_string(width) +'\n'<< max_value;
            for(int j = 0; j < height; ++j){
                for(int k = 0; k < width; ++k)
                    // ofs.write((char*)&pixels.get()[j][k],sizeof(char*));
                    ofs << (unsigned char)pixels.get()[j][k];
            }
            cout << endl;
        }else{
            cout <<"File not open" << endl;
        }
        ofs.close();

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
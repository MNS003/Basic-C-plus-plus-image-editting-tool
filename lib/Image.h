#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <memory>
#include <iostream>

namespace STHMIN003{

    class Image{
        private:
          public:
            int width, height, max_value;
            std::string version, comments;
            std::unique_ptr <unsigned char *[]> pixels; //make_unique< unique_ptr<unsigned char>[] >(3)
            //default ctor
            Image();
            //dtor 
            ~Image();
            //ctor with filename
            Image(std::string filename);
            //copy ctor
            Image(const Image & other );
            //copy assignment ctor
            Image & operator=(const Image & other);
            //move ctor
            Image(Image && other);
            //move asssignment ctor
            Image & operator=(Image && other);
            //addition
            Image & operator+(const Image && other);
            //subtraction
            Image & operator-(const Image && other);
            //inversion
            Image & operator!();
            //mask
            Image & operator/(const Image && other);
            //threshold
            Image & operator*(const Image &&other);
            //stream in
            std::ostream &operator<<(const Image &&other);
            //stream out
            std::ostream &operator>>(const Image &&other);
            //load
            void load(std::string filename);
            //save
            void save(std::string filename);

            class iterator{
                private:
                    unsigned char * ptr;
                    iterator(unsigned char * p);
                public:
                    //copy ctor
                    iterator(const iterator & other);
                    //copy assignment
                    iterator & operator=(const iterator & other);
                    //move ctor
                    iterator(const iterator && other);
                    //move assignment
                    iterator & operator=(const iterator && other);
                    //incriment
                    iterator & operator++();
                    //decriment
                    iterator & operator--();
                    //deref
                    Image operator*();

            };

            iterator begin();
            iterator end();
    };

}

#endif
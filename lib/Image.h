#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace STHMIN003{

    class Image{
        private:
          public:
            int width, height, max_value;
            std::string version, comments;
            // std::vector< std::vector< std::unique_ptr<unsigned char>>> pixels; //make_unique< unique_ptr<unsigned char>[] >(3)
            std::vector< std::vector< unsigned char>> pixels;
            //default ctor
            Image();
            Image(int width, int height);
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
            Image operator+(const Image && other);//image = img + new Image()
            Image operator+(const Image & other);//image = img + img2

            //subtraction
            Image operator-(const Image && other);//image = img - new Image()
            Image operator-(const Image & other);//image = img - img2

            //inversion
            Image operator!();
            //mask
            Image operator/(const Image && other);//image = img / new Image()
            Image operator/(const Image & other);//image = img / img2

            //threshold
            Image operator*(const Image && other);//image = img * new Image()
            Image operator*(const Image & other);//image = img * img2

            //stream in
            std::ostream &operator<<(const Image &&other);
            //stream out
            std::ostream &operator>>(const Image &&other);
            //load
            void load(std::string filename);
            //save
            void save(std::string filename);
            //intialize image vector
            void make_vector(int width, int height);

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
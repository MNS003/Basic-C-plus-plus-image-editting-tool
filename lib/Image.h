#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace STHMIN003{

    class Image{
        private:
            int width, height, max_value;
            std::string version, comments;
        public:
        std::unique_ptr<unsigned char[]> pixels; //make_unique< unique_ptr<unsigned char>[] >(3)

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
        Image operator+(const Image & other);//image = img + img2
        Image operator+(const Image && other);//image = img + new Image()

        //subtraction
        Image operator-(const Image && other);//image = img - new Image()
        Image operator-(const Image & other);//image = img - img2

        //inversion
        Image operator!();
        //mask
        Image operator/(const Image && other);//image = img / new Image()
        Image operator/(const Image & other);//image = img / img2

        //threshold
        Image operator*(int f);//image = img * 5
        Image operator*(int & f);//image = img * f

        //stream out
        friend std::ostream &operator<<(std::ostream& out,const Image &other);
        //stream in
        friend std::istream &operator>>(std::istream& out, Image &other);

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
                iterator( iterator && other);
                //move assignment
                iterator & operator=( iterator && other);
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
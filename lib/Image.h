#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace STHMIN003{

    
    class Image{
        private:
            int width, height, max_value,size;
            std::string version, comments;
            std::unique_ptr<unsigned char[]> pixels; 
        public:
        //==========GETTERS FOR TESTS====================
        std::vector<int> get_ints(){return std::vector<int>({width,height,max_value,size});}
        std::vector<std::string> get_strings() { return std::vector<std::string>({version,comments}); }
        unsigned char* get_pixels(){return pixels.get();}
        //===============================================
        class iterator{
            private:
                unsigned char *ptr;
            public:
                iterator(unsigned char *p);
                //copy ctor
                iterator(const iterator &other);
                //copy assignment
                iterator &operator=(const iterator &other);
                //move ctor
                iterator(iterator && other);
                //move assignment
                iterator &operator=(iterator &&other);
                //incriment
                iterator operator++();
                iterator operator++(int);
                //decriment
                iterator operator--();
                iterator operator--(int);
                //deref
                unsigned char& operator*();

                //equals
                bool operator==(iterator & other);
                bool operator!=(iterator & other);

        };//Iterator


        //default ctor
        Image();
        //ctor for blank image
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

        //filter
        Image operator%(int f);  //image = img % 5
        Image operator%(int &f); //image = img % f

        //stream out
        friend std::ostream &operator<<(std::ostream& out,const Image &other);
        //stream in
        friend std::istream &operator>>(std::istream& out, Image &other);

        //load
        void load(std::string filename);
        //save
        void save(std::string filename);

        iterator begin();
        iterator end();
    };//Image

}

#endif
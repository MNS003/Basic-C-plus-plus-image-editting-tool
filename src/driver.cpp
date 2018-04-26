#include "../lib/Image.h"
#include <iostream>
#include <string>

using namespace std;
int main(int argc , char * argv[]){
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // {
    //     std::vector< std::vector<std::unique_ptr <unsigned char>>> pixels;
    //     for(int j = 0; j < 1200; ++j){
    //         auto row = vector< std::unique_ptr <unsigned char> >();
    //         for(int i = 0; i < 1000; ++i){
    //             row.push_back(unique_ptr <unsigned char>( new unsigned char('j') ));
    //         }
    //         pixels.push_back(move(row));
    //     }
    //     cout << pixels[0][0].get();
    //     pixels[0][0].reset(new unsigned char('g'));
    //     cout << pixels[0][0].get() << endl; 
    // }
    //========================================================================
    string infile = argv[1], outfile = argv[2];
    cout << "Started imageops with " << infile << endl;
    STHMIN003::Image img(infile);
    img.save(outfile);
    STHMIN003::Image new_img(outfile);
    int error_count = 0;
    for(int j = 0; j < img.height; ++j)
        for(int k = 0; k < img.width; ++k)
            if(img.pixels[j][k] != new_img.pixels[j][k])
                ++error_count;
    cout << "Testing... \n" << error_count << " errors found" << endl;
    !new_img;
    STHMIN003::Image img_plus = new_img + img;
    new_img.save("inverted.pgm");
    img_plus.save("solid.pgm");
    cout << "end" << endl;
}
#include "../lib/Image.h"
#include <iostream>

using namespace std;
int main(int argc , char * argv[]){
    string infile = argv[1], outfile = argv[2];
    cout << "Started imageops with " << infile << endl;
    STHMIN003::Image img(infile);
    if(outfile[0] != 't'){
        img.save(outfile);
        STHMIN003::Image new_img(outfile);
        int count = 0;
        for(int j = 0; j < img.height; ++j)
            for(int k = 0; k < img.width; ++k)
                if(img.pixels[j][k] != new_img.pixels[j][k])
                    ++count;
        cout << "Testing... \n" << count << " errors found" << endl;
    }
    cout << "end" << endl;
}
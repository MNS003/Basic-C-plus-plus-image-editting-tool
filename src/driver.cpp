#include "../lib/Image.h"
#include <iostream>
#include <string>

using namespace std;
int main(int argc , char * argv[]){
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    {
        // unique_ptr<unsigned char[]> pixels(new unsigned char[100]);
        // pixels[2] = '5';
        // cout << pixels[2] << endl;
        
    }
    //========================================================================
    
    cout << "Started imageops with" << endl;
    
    if(string(argv[1]) =="-a"){// -a I1 I2
    cout << "plus" << endl;
        string I1 = argv[2], I2 = argv[3];
        STHMIN003::Image a(I1), b(I2), plus;
        plus = a + b;
        plus.save("plus.pgm");
    }
    else if (string(argv[1]) == "-s"){// -s I1 I2 (subtract I2 from I1)
        cout << "subtract" << endl;
        string I1 = argv[2], I2 = argv[3];
        STHMIN003::Image a(I1), b(I2), subtract;
        subtract = a - b;
        subtract.save("subtract.pgm");
    }
    else if (string(argv[1]) == "-i"){// -i I1 (invert I1)
        cout << "invert" << endl;
        string I1 = argv[2];
        STHMIN003::Image invert(I1);
        !invert;
        invert.save("invert.pgm");
    }
    else if (string(argv[1]) == "-l"){// -l I1 I2 (mask I1 with I2)
        cout << "mask" << endl;
        string I1 = argv[2], I2 = argv[3];
        STHMIN003::Image a(I1), b(I2), mask;
        mask = a/b;
        mask.save("mask.pgm");
    }
    else if (string(argv[1]) == "-t"){// -t I1 f (threshold I1 with integer value f)
        cout << "threshold" << endl;
        string I1 = argv[2];
        STHMIN003::Image threshold, a(I1);
        threshold = a*128;
        threshold.save("threshold.pgm");
        cout << threshold << endl;
    }
    cout << "end" << endl;
}
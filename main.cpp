#include <iostream>
#include <fstream>
#include "square.h"


using namespace std;

int main()
{
    int size = 1000;

    /*
    square* s = new square(size);
    int i,j;

    for (i=0;i<size;i++) {
        for (j=0;j<size;j++) {
                s->setValue(i,j,true);
        }
    }

    for (i=0;i<size;i++) {
        for (j=0;j<size;j++) {
                if ((i+j)%2)
                    s->setValue(i,j,false);
        }
    }

    s->setValue(2,5,true);
    s->setValue(2,6,true);
    s->setValue(2,7,true);

            cout << "s" << endl;
            for (int i=0;i<size;i++) {
                for (int j=0;j<size;j++) cout << s->getValue(i,j);
                cout << endl;
            }
    char z;
    cin >> z;
    */

    bool debug = false;
    int* result = new int[size*size];
    for (int i=0;i<size;i++)
        for (int j=0;j<size;j++) result[i*size+j] = -1;

    int filled = 0;
    int height = 0;
    square* xt;
    square* yt;
    square* xyt;

    while (filled < size*(size+1)/2) {
        if (height > 0) {
            square* xt_previous = xt;
            xt = new square(size);

            for (int i=1;i<size;i++)
                for (int j=0;j<size;j++)
                    if (xt_previous->getValue(i-1,j)) xt->setValue(i,j,true);
            delete xt_previous;

            square* yt_previous = yt;
            yt = new square(size);
            for (int i=0;i<size;i++)
                for (int j=1;j<size;j++)
                    if (yt_previous->getValue(i,j-1)) yt->setValue(i,j,true);
            delete yt_previous;

            square* xyt_previous = xyt;
            xyt = new square(size);
            for (int i=1;i<size;i++)
                for (int j=1;j<size;j++)
                    if (xyt_previous->getValue(i-1,j-1)) xyt->setValue(i,j,true);
            delete xyt_previous;

        } else {
            xt = new square(size);
            yt = new square(size);
            xyt = new square(size);
        }

        bool* y = new bool[size];
        for (int i=0;i<size;i++) y[i] = false;

        bool* xy = new bool[size];
        for (int i=0;i<size;i++) xy[i] = false;

        int i = 0;
        do {
            int j = 0;
            bool found;
            do {

                if (debug) {
                    cout << "i = " << i << " j = " << j << endl;
                    cout << "result[i*size+j] = " << result[i*size+j] << endl;
                    cout << "!y[j] = " << !y[j] << endl;
                    cout << "!xy[i-j] = " << !xy[i-j] << endl;
                    cout << "!xt->getValue(i,j) = " << !xt->getValue(i,j) << endl;
                    cout << "!yt->getValue(i,j) = " << !yt->getValue(i,j) << endl;
                    cout << "!xyt->getValue(i,j) = " << !xyt->getValue(i,j) << endl;
                }

                found = (result[i*size+j] == -1) && !y[j] && !xy[i-j] && !xt->getValue(i,j) && !yt->getValue(i,j) && !xyt->getValue(i,j);
                if (debug) cout << "found = " << found << endl;

                if (found) {
                    filled++;
                    y[j] = true;
                    y[i] = true;
                    xy[i-j] = true;
                    xt->setValue(i,j,true);
                    yt->setValue(i,j,true);
                    xyt->setValue(i,j,true);

                    xt->setValue(j,i,true);
                    yt->setValue(j,i,true);
                    xyt->setValue(j,i,true);

                    result[i*size+j] = height;
                    if (i != j) result[j*size+i] = height;
                    //cout << "height=" << height << "\t" << "i=" << i << "\t" << "j=" << j << " filled: " << filled << endl;
                } else {
                    j++;
                }
            } while ((j <= i) && (!found));
            i++;
        } while (i<size) ;

        delete y;
        delete xy;

        /*
        if (xt->getValue(0,3))
            cout << "bummer" << endl;

        if (debug) {
            cout << "xt" << endl;
            for (int i=0;i<size;i++) {
                for (int j=0;j<size;j++) cout << xt->getValue(i,j);
                cout << endl;
            }
        }
        */
        height++;
        if (height%100==0) 
	    cout << "height: " << height << " filled: " << filled << endl;
    }

    std::fstream resultFile = std::fstream("result.bin", std::ios::out | std::ios::binary);
    resultFile.write((char*)result, size*size*sizeof(int));
    resultFile.close();

    cout << "done" << endl;
    return 0;
}

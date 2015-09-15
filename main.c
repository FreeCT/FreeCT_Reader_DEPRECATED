#include <stdio.h>
#include <stdlib.h>
#include <fct/fct_read.h>

int main(int argc, char ** argv){

    FILE * file;
    file=fopen("/home/john/raw_data/noo_test_data/binaries/noo16_100.bin","rb");

    float * f=(float*) malloc(sizeof(float)*100*100);
    
    ReadDICOMFrame(file,10,100,100,f);

    for (int i=0;i<100*100;i++)
	printf("%.2f\n",f[i]);

    fclose(file);

    return 0;
}

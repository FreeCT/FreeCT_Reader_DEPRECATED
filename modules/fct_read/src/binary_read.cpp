
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "../include/binary_read.h"

// Binary Files
void ReadBinaryFrame(FILE* fp, int frame_index, int num_channels, int num_slices, float *f,size_t d_offset){
    // Seek to beginning of requested frame
    size_t offset = frame_index*num_channels*num_slices*sizeof(float)+d_offset;
    fseek(fp,offset,SEEK_SET);

    // Fread the frame into our frame holder
    fread(f,sizeof(float),num_channels*num_slices,fp);
}

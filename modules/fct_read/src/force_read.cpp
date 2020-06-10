#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "../include/force_read.h"

struct force_frame read_force_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset);

//Force Readers
void ReadForceFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

float ReadForceTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}
long ReadForceTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

struct force_frame read_force_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

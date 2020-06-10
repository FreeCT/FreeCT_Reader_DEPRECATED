
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "../include/definitionas_read.h"

struct definitionas_frame read_PTR_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset);

void ReadPTRFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

float ReadPTRTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

long ReadPTRTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

struct definitionas_frame read_PTR_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset){
    printf("PTR file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

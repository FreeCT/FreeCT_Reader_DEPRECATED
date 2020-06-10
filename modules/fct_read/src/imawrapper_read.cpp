#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#include "../include/imawrapper_read.h"

struct  sensation64_frame read_CTDv1794_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset);
struct  sensation64_frame read_CTDv2007_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset);
struct definitionas_frame read_PTR_frame(FILE* fp, int frame_index,int num_channels,int num_slices,int frame_flag,size_t offset);

// IMA files (Note: IMA is a wrapper for one of the other two types)
void ReadIMAFrame(FILE* fp, int frame_index, int num_channels, int num_slices, float *f,int raw_data_type,size_t offset){
    printf("Siemens IMA file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

float ReadIMATubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices,int raw_data_type,size_t offset){
    printf("Siemens IMA file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

long ReadIMATablePosition(FILE* fp, int frame_index,int num_channels,int num_slices,int raw_data_type,size_t offset){
    printf("Siemens IMA file types are not supported in this version of FreeCT Reader. Sorry!\n");
    exit(1); // Linux error for "operation not permitted"
}

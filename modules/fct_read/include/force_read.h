#ifndef force_read_h
#define force_read_h

#include "force.h"

//Force Readers
void ReadForceFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f);
float ReadForceTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices);
long ReadForceTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices);

#endif

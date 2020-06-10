
#ifndef definitionas_read_h
#define definitionas_read_h

#include "definitionas.h"

//PTR Readers
extern void ReadPTRFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f);
extern float ReadPTRTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices);
extern long ReadPTRTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices);

#endif

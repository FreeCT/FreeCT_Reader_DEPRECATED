
#ifndef sensation64_v2007_read_h
#define sensation64_v2007_read_h

#include "sensation64.h"

//CTD Readers
extern void ReadCTDv2007Frame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f);
extern float ReadCTDv2007TubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices);
extern long ReadCTDv2007TablePosition(FILE* fp, int frame_index,int num_channels,int num_slices);

#endif

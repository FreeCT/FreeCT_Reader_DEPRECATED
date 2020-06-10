#ifndef sensation64_v1794_read_h
#define sensation64_v1794_read_h

#include "sensation64.h"

//CTD Readers
extern void ReadCTDv1794Frame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f);
extern float ReadCTDv1794TubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices);
extern long ReadCTDv1794TablePosition(FILE* fp, int frame_index,int num_channels,int num_slices);

#endif

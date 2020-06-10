#ifndef imawrapper_read_h
#define imawrapper_read_h

#include "sensation64.h"
#include "definitionas.h"
#include "force.h" // just in case

// IMA files (Can be either PTR defintionas or CTDv1794 or CTDv2007)
extern void ReadIMAFrame(FILE* fp, int frame_index, int num_channels, int num_slices, float *f,int raw_data_type,size_t offset);
extern float ReadIMATubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices,int raw_data_type,size_t offset);
extern long ReadIMATablePosition(FILE* fp, int frame_index,int num_channels,int num_slices,int raw_data_type,size_t offset);

#endif

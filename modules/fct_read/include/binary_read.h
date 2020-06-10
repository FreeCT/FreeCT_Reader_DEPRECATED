
#ifndef binary_read_h
#define binary_read_h

extern void ReadBinaryFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f,size_t d_offset);

#endif

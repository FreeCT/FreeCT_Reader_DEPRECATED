#ifndef dicom_read_h
#define dicom_read_h

//DICOM Readers
extern void ReadDICOMFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f);
extern float ReadDICOMTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices);
extern long ReadDICOMTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices);

#endif

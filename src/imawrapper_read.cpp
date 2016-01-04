/* libfct_read is reads CT raw data from binary files and DICOM format. */
/* It is distributed as part of the FreeCT package, as well as a standalone library */
/* Copyright (C) 2015  John Hoffman */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA *

   /* Questions and comments should be directed to */
/* jmhoffman@mednet.ucla.edu with "CTBANGBANG" in the subject line*/

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

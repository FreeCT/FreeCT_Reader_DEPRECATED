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

#include "../include/dicom.h"

void ReadDICOMFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f){
    printf("We are in the process of adding support for the open dicom raw data format.\n");
}

float ReadDICOMTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("We are in the process of adding support for the open dicom raw data format.\n");
    return 0;
}

long ReadDICOMTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("We are in the process of adding support for the open dicom raw data format.\n");
    return 0;
}

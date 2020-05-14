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

#include "../include/binary_read.h"

// Binary Files
void ReadBinaryFrame(FILE* fp, int frame_index, int num_channels, int num_slices, float *f,size_t d_offset){
    // Seek to beginning of requested frame
    size_t offset = frame_index*num_channels*num_slices*sizeof(float)+d_offset;
    fseek(fp,offset,SEEK_SET);

    // Fread the frame into our frame holder
    fread(f,sizeof(float),num_channels*num_slices,fp);
}

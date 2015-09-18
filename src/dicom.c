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
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "../include/dicom.h"

// DCMTK includes
//#include <dcmtk/config/osconfig.h>
//#include <dcmtk/ofstd/ofstd.h>
//#include <dcmtk/dcmdata/dctk.h>
#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/ofstd/ofstream.h"
#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/ofstd/ofconapp.h"
#include "dcmtk/ofstd/ofstd.h"

using namespace std;

long dicom_scan(FILE* fp,const char * tag);
int check_str(char * a, const char * b);


void ReadDICOMFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f){


    // Extract the filename from the pointer (allows us to maintain
    // a constant function signature for different file types)
    int MAXSIZE = 0xFFF;
    char proclnk[0xFFF];
    char filename[0xFFF]={0};
    int fno;
    ssize_t r;

    fno = fileno(fp);
    sprintf(proclnk, "/proc/self/fd/%d", fno);
    r = readlink(proclnk, filename, MAXSIZE);
    if (r < 0){
	printf("failed to readlink\n");
	exit(1);
    }
    filename[r] = '\0';
    
    //printf("fp -> fno -> filename: %p -> %d -> %s\n",fp, fno, filename);

    DcmFileFormat fileformat;
    OFCondition status=fileformat.loadFile(filename);
    if (status.good()){
	OFString patientName;
	if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName,patientName).good())
	    cout << "Patient's name:" << patientName << endl;
	else
	    cerr << "Error: failed to get patient name" << endl;
    }
    else{
	cerr << "You broke it!" << endl;
    }
    
}

float ReadDICOMTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("We are in the process of adding support for the open dicom raw data format.\n");
    return 0;
}

long ReadDICOMTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices){
    printf("We are in the process of adding support for the open dicom raw data format.\n");
    return 0;
}


long dicom_scan(FILE* fp,const char * tag){
    // This function will search through a dicom file for the
    // hexadecimal "tag".  Once it has found "tag" it will return the
    // byte offset from the beginning of the file and the size of the
    // data referred to by "tag." It is aware of transfer syntax and
    // will adjust reading routines accordingly.
    //
    // All information to create this function was take from:
    // ftp://medical.nema.org/medical/dicom/final/sup01_ft.pdf
    // from page 18 on 2015/09/18.
    //
    // While it  be compliant with the DICOM standard
    // however should not be used in any other DICOM reading context
    // other than this raw data reader

    // Until we reach the transfer syntax tag, all data is stored as
    // "Explicit VR Little Endian" (UID=1.2.840.10008.1.2.1) as per
    // the DICOM std (pg. 19 lines 16-22)

    char tag[8]={0};
    char vr[2]={0};
    uint16 size;
    char buffer[0xFFF]={0}; // Throwaway buffer that we'll use to check various things

    // 128 bytes of padding
    fseek(fp,128,SEEK_SET);

    // check for "DICM"
    fread(buffer,4,sizeof(char),fp);
    check_str(buffer,"DICM");
    
    //Check for Group length tag (0002,0000)
    fread(tag,4,sizeof(char),fp);
    check_str(tag,"\x02\x00\x00\x00");

    fread(vr,1,sizeof(char),fp);
    check_str(vr,"UL");
    
}
	
int check_str(char * a, const char * b){
    if (strcmp(a,b)!=0){
	printf("File is either not DICOM or malformed DICOM.  Quitting.\n");
	exit(1);
    }
}

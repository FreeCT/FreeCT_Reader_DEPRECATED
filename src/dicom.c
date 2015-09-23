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

struct dicom_tag{
    char group[3];
    char element[3];
    char vr[3];
    uint16_t size_16;
    uint32_t size_32;
    size_t size;
    size_t byte_offset_to_data;
};

struct dicom_tag dicom_scan(FILE* fp,const char * search_group,const char * search_element);
struct dicom_tag read_tag_info(FILE* fp,const char * transfer_syntax);

int check_str(char * a, const char * b);

void ReadDICOMFrame(FILE* fp,int frame_index,int num_channels,int num_slices,float *f){

    struct dicom_tag t;

    char raw_DS[17]={0}; // to hold the raw decimal strings for rescale fields
    
    // Get the rescale intercept
    float rescale_intercept;
    t=dicom_scan(fp,"\x28\x00","\x52\x10");
    fseek(fp,t.byte_offset_to_data,SEEK_SET);
    fread(raw_DS,sizeof(char),t.size,fp);
    rescale_intercept=atof(raw_DS);
    memset(raw_DS,0,17*sizeof(char));
    fseek(fp,0,SEEK_SET);
    
    // Get the rescale slope
    float rescale_slope;
    t=dicom_scan(fp,"\x28\x00","\x53\x10");
    fseek(fp,t.byte_offset_to_data,SEEK_SET);
    fread(raw_DS,sizeof(char),t.size,fp);
    rescale_slope=atof(raw_DS);
    memset(raw_DS,0,17*sizeof(char));
    fseek(fp,0,SEEK_SET);

    // Get the memory pitch (i.e. total number of projections)
    uint16_t n_readings;
    t=dicom_scan(fp,"\x28\x00","\x11\x00");
    fseek(fp,t.byte_offset_to_data,SEEK_SET);
    fread(&n_readings,1,t.size,fp);
    fseek(fp,0,SEEK_SET);

    // Grab the frame in question
    // Data are stored as int16 (or uint16?)
    int16_t * f_hold=(int16_t*)malloc(sizeof(int16_t)*num_channels*num_slices);
    t=dicom_scan(fp,"\xe0\x7f","\x10\x00");
    //t=dicom_scan(fp,"\xe0\x7f","\x19\x99");    
    fseek(fp,t.byte_offset_to_data,SEEK_SET);

    /* Data is currently stored as: */
    //    
    //             proj1             proj2             proj3      ...    projNproj
    // row1,chan1  mem_add_1         mem_add_2         mem_add_3  ...    mem_add_Nproj
    // row1,chan2  mem_add_(Nproj+1) mem_add_(Nproj+2) mem_add_(Nproj+3) mem_add_(2*Nproj)
    //    ...                                       ...........
    // row1,chanM
    // row2,chan1
    // row2,chan2
    //    ...
    // row2,chanM
    //    ...
    // rowN,chanM 
    //
    // All of the projection data for one detector element is stored
    // linearly in memory.  This is very inefficient given that we do
    // not use projection data in this way for reconstruction.  It is
    // more beneficial (both intuitively and computationally) to store
    // a single frame linearly in memory, then move on to the next
    // frame.  I'm going to lobby Mayo to see if this would be a
    // tractable change, however we implement a reader here for the
    // current format, despite my reservations.

    // Seek to the frame we want
    fseek(fp,sizeof(uint16_t)*frame_index,SEEK_CUR);
    for (int i=0; i<num_channels*num_slices;i++){
    	fread(&f_hold[i],sizeof(uint16_t),1,fp);
    	fseek(fp,(n_readings-1)*sizeof(uint16_t),SEEK_CUR);
    	f[i]=rescale_slope*(float)f_hold[i]+rescale_intercept;
    }

    /* If the data had be stored the way I want it to be */
    //size_t offset=frame_index*num_channels*num_slices*sizeof(int16_t);
    //fseek(fp,offset,SEEK_CUR);
    //fread(f_hold,sizeof(int16_t),num_channels*num_slices,fp);
    //for (int i=0;i<num_channels*num_slices;i++){
    //	f[i]=rescale_slope*(float)f_hold[i]+rescale_intercept;
    //}

}

float ReadDICOMTubeAngle(FILE* fp, int frame_index,int num_channels,int num_slices){

    struct dicom_tag t;
    
    float tube_angle;
    t=dicom_scan(fp,"\x31\x70","\x01\x10");
    // Seek to start of data
    fseek(fp,t.byte_offset_to_data,SEEK_SET);
    // Seek to requested frame
    fseek(fp,sizeof(float)*frame_index,SEEK_CUR);
    fread(&tube_angle,sizeof(float),1,fp);
    fseek(fp,0,SEEK_SET);
    
    return tube_angle;
}

long ReadDICOMTablePosition(FILE* fp, int frame_index,int num_channels,int num_slices){

    struct dicom_tag t;
    
    float table_position;
    t=dicom_scan(fp,"\x31\x70","\x02\x10");
    // Seek to start of data
    fseek(fp,t.byte_offset_to_data,SEEK_SET);

    // Seek to requested frame
    fseek(fp,sizeof(float)*frame_index,SEEK_CUR);
    fread(&table_position,sizeof(float),1,fp);
    fseek(fp,0,SEEK_SET);

    // Scaled to make function match format of other Siemens readers
    return table_position*1000;
}


struct dicom_tag dicom_scan(FILE* fp,const char * search_group,const char* search_element){
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
    // While it should be compliant with the DICOM standard,
    // it should not be used in any other DICOM reading context
    // other than this raw data reader.  

    // All of the file meta information is stored as
    // "Explicit VR Little Endian" (UID=1.2.840.10008.1.2.1) as per
    // the DICOM standard (pg. 19 lines 16-22)

    // We do explicit reading of the File Meta Information to ensure
    // that the file is well formed.  This is also to ensure that we
    // read to the proper location using the Explicit VR little Endian
    // transfer syntax specified by the standard.  After we get past
    // the file meta information block, we read in a loop according to
    // whatever transfer syntax is specified in (0002,0010).

    struct dicom_tag tag;
    memset(&tag,0,sizeof(struct dicom_tag));
    
    char buffer[0xFFF]={0}; // Throwaway buffer that we'll use to check various things
    char transfer_syntax[64]={0}; // allocate this further down

    // Get the file size so we don't actually read out of bounds.
    size_t fp_size;
    fseek(fp,0L,SEEK_END);
    fp_size=ftell(fp);
    fseek(fp,0,SEEK_SET);
    
    // 128 bytes of padding
    fseek(fp,128,SEEK_SET);

    // check for "DICM"
    fread(buffer,4,sizeof(char),fp);
    check_str(buffer,"DICM");

    // GROUP LENGTH
    /*  tag (0002,0000) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x00\x00");
    check_str(tag.vr,"UL");
    fseek(fp,tag.size,SEEK_CUR);

    // FILE META INFORMATION VERSION
    // Stored as OB, which is totally wonky.  See:
    // http://medical.nema.org/dicom/2013/output/chtml/part05/chapter_7.html
    /*  tag (0002,0001) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x01\x00");
    check_str(tag.vr,"OB");
    fseek(fp,tag.size,SEEK_CUR);
    
    // MEDIA STORAGE SOP CLASS UID
    /*  tag (0002,0002) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x02\x00");
    check_str(tag.vr,"UI");
    fseek(fp,tag.size,SEEK_CUR);

    // MEDIA STORAGE SOP INSTANCE UID
    /*  tag (0002,0003) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x03\x00");
    check_str(tag.vr,"UI");
    fseek(fp,tag.size,SEEK_CUR);
   
    // TRANSFER SYNTAX UID
    /*  tag (0002,0010) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x10\x00");
    check_str(tag.vr,"UI");
    fread(transfer_syntax,tag.size,sizeof(char),fp);
    
    // IMPLEMENTATION CLASS UID
    /* tag (0002,0012) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x12\x00");
    check_str(tag.vr,"UI");
    fseek(fp,tag.size,SEEK_CUR);

    // IMPLEMENTATION VERSION NAME
    /* tag (0002,0013) */
    tag=read_tag_info(fp,"E-LE");
    check_str(tag.group,"\x02\x00");
    check_str(tag.element,"\x13\x00");
    check_str(tag.vr,"SH");
    fseek(fp,tag.size,SEEK_CUR);

    // From here on out we read according to the transfer syntax
    // specified in tag (0002,0010)

    // There are only 2 transfer syntaxes that we care about:
    //
    // (1) 1.2.840.10008.1.2      -> Implicit VR Endian: Default Transfer Syntax for DICOM
    // (2) 1.2.840.10008.1.2.1    -> Explicit VR Little Endian
    //
    // Other transfer sytaxes do not apply here and will be
    // ignored (i.e. program will exit).

    if (strcmp(transfer_syntax,"1.2.840.10008.1.2")==0){
	memset(transfer_syntax,0,64*sizeof(char));
	strcpy(transfer_syntax,"I-LE"); // Implicit VR Little endian
    }
    else if (strcmp(transfer_syntax,"1.2.840.10008.1.2.1")==0){
	memset(transfer_syntax,0,64*sizeof(char));
	strcpy(transfer_syntax,"E-LE"); // Explicit VR Little endian
    }
    else{
	printf("DICOM transfer syntax is invalid for a raw data file.  Quitting.\n");
    }
    
    while ((strcmp(tag.group,search_group)!=0)||strcmp(tag.element,search_element)!=0){
	tag=read_tag_info(fp,(const char *)transfer_syntax);

	if (ftell(fp)+tag.size<=fp_size){
	    fseek(fp,tag.size,SEEK_CUR);
	}
	else{
	    printf("Reached end of raw file without finding tag %02hhx%02hhx,%02hhx%02hhx\n",search_group[1],search_group[0],search_element[1],search_element[0]);
	    exit(1);
	}
	
    }
    
    return tag;    
}

struct dicom_tag read_tag_info(FILE* fp,const char * transfer_syntax){
    // fp must be on the start of a tag otherwise we'll misread

    struct dicom_tag tag;

    // Get GROUP,ELEMENT
    fread(&tag.group,2,sizeof(char),fp);
    fread(&tag.element,2,sizeof(char),fp);

    // Get VR (if negotiated) and SIZE
    if (strcmp(transfer_syntax,"I-LE")==0){
	fread(&tag.size_32,1,sizeof(uint32_t),fp);
	tag.size=tag.size_32;
    }
    else if (strcmp(transfer_syntax,"E-LE")==0){
	fread(&tag.vr,2,sizeof(char),fp);
	if (strcmp(tag.vr,"OB")==0||
	    strcmp(tag.vr,"OW")==0||
	    strcmp(tag.vr,"OF")==0||
	    strcmp(tag.vr,"SQ")==0||
	    strcmp(tag.vr,"UT")==0||
	    strcmp(tag.vr,"UN")==0){

	    // Skip two bytes then read size as 32 bit unsigned integer
	    fseek(fp,2,SEEK_CUR);
	    fread(&tag.size_32,1,sizeof(uint32_t),fp);
	    tag.size=tag.size_32;
	}
	else{
	    fread(&tag.size_16,1,sizeof(uint16_t),fp);
	    tag.size=tag.size_16;
	}
    }
    else{
	printf("DICOM transfer syntax is invalid for a raw data file.  Quitting.\n");
    }


    tag.byte_offset_to_data=ftell(fp);

    return tag;
}

int check_str(char * a, const char * b){
    if (strcmp(a,b)!=0){
	printf("File is either not DICOM or malformed DICOM.  Quitting.\n");
	exit(1);
    }
}

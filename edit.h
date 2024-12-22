#ifndef EDIT_H
#define EDIT_H

#include "type.h"

typedef struct mp3
{
    char tag[3];         // 'TAG'
    char title[50];
    char artist[50];
    char album[50];
    char year[8];
    char comment[50];
    unsigned char genre;

    /* Source Image info */
    char *src_fname;  //Source file name
    FILE *fptr_src;  
    //char version[20];
    char *duplicate;
                       //source File point
    /*Temp file*/
    char *temp_file;
    FILE *fptr_temp_file;
}TAG_EDIT;

/*read and validate*/
status read_validate(char *argv[],TAG_EDIT *Tag);

/*open files*/
status open_files_e(TAG_EDIT *Tag);

/*checking ID3*/
status mp3_ID_E(TAG_EDIT *Tag);

/*check for edit*/
status check_for_edit(char *argv[],TAG_EDIT *Tag);

/*edit mp3*/
status edit_mp3(char *argv[],TAG_EDIT *Tag);

/*conversion big to little*/
status convert_big_little_e(int x);

/*copy mp3 header*/
status copy_mp3_header(FILE *fptr_src,FILE *fptr_temp_file);

/*copying all type of content*/
status all_type(TAG_EDIT *Tag);


/*convert little to big endian*/
status Little_big(int x);

/*To check size*/
status check_size(TAG_EDIT *Tag);

/*copy remaining data*/
status copy_remaning_data(TAG_EDIT *Tag);

status file_close(TAG_EDIT *Tag);

status file_open_to_transfer(TAG_EDIT *Tag);
#endif
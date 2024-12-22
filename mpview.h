#ifndef MPVIEW_H
#define MPVIEW_H

#include "type.h"


typedef struct MPID3V2Tag
{   
    //title
    char title[50];
    int title_pos;

    char artist[50];
    int artist_pos;

    char album[50];
    int album_pos;

    char year[8];
    int year_pos;
    
    char comment[50];
    int comment_pos;
    unsigned char genre;

    /* Source Image info */
    char src_fname[30];  //Source file name
    FILE *fptr_src;  
    char version[20];
                        //source File pointer
}TAG_VIEW;

/*check opertion*/
opertiontype check_opertion_type(char *argv[]);

/*file open*/
status open_files(TAG_VIEW *tag);

/*read and validate*/
status read_and_validate_args(char *argv[],TAG_VIEW *tag);

/*checking mp3 ID*/
status mp3_ID(TAG_VIEW *tag);

/*view the mp3 file*/
status view_mp3(TAG_VIEW *tag);

/*read all frames*/
status read_frame(TAG_VIEW *tag, const char *frame_id, char *output, size_t output_size);

/*conversion big to little*/
status convert_big_little(int size);

/*Song title*/
status Song_title(TAG_VIEW *tag);

/*Artist name*/
status Artist_name(TAG_VIEW *tag);

/*Alubm name*/
status Album_name(TAG_VIEW *tag);

/*Year*/
status year(TAG_VIEW *tag);

/*Tag content*/
status Tag_content(int x,TAG_VIEW *tag);

/*content type*/
status content_type(TAG_VIEW *tag);

/*Composer*/
status Composer(TAG_VIEW *tag);



#endif
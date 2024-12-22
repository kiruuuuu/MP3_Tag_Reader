#include<stdio.h>
#include "type.h"
#include<string.h>
#include "mpview.h"

#define ID3_HEADER_SIZE 3
#define FRAME_ID_SIZE 4
#define FRAME_HEADER_SIZE 10

opertiontype check_opertion_type(char *argv[])
{
    if(strcmp(argv[1],"-v")==0)
    {
        return mp3_view;
    }
    if(strcmp(argv[1],"-e")==0)
    {
        return mp3_edit;
    }
    else
    {
        return mp3_invalid;
    }
}
/*file open*/
status open_files(TAG_VIEW *tag)
{
    tag->fptr_src=fopen(tag->src_fname,"r");
    if(tag->fptr_src==NULL)
    {
        return e_failure;
    }
    return e_success;
}

/*read and validate*/
status read_and_validate_args(char *argv[],TAG_VIEW *tag)
{
    if(strstr(argv[2],".mp3")!=NULL)
    {
      strcpy(tag->src_fname,argv[2]);
    }
    else
    {
        return e_failure;
    }
    return e_success;
}

/*checking mp3 ID*/
status mp3_ID(TAG_VIEW *tag)
{
            printf("------------------------SELECTED VIEW DETAILS--------------------------------\n");
            printf("\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("                      MP3 TAG READER AND EDITOR FOR ID3V2                    \n");
            printf("-----------------------------------------------------------------------------\n");
            printf("\n");
    char buf[4];
    fread(buf,3,1,tag->fptr_src);
     if(strcmp(buf,"ID3")==0)
     {
        return e_success;
     }
     else
     {
        return e_failure;
     }
     return e_success;
}

/*view the mp3 file*/
status view_mp3(TAG_VIEW *tag)
{
    Song_title(tag);
    Artist_name(tag);
    Album_name(tag);
    year(tag);
    content_type(tag);
    Composer(tag);
    return e_success;
}
/*conversion big to little*/
status convert_big_little(int x)
{
           int size=((x >> 24) & 0x000000FF) | // Move byte 3 to byte 0
           ((x >> 8)  & 0x0000FF00) | // Move byte 2 to byte 1
           ((x << 8)  & 0x00FF0000) | // Move byte 1 to byte 2
           ((x << 24) & 0xFF000000);  // Move byte 0 to byte 3
           return size-1;
    
}
status read_frame(TAG_VIEW *tag, const char *frame_id, char *output, size_t output_size) {
    char buf_frame[FRAME_ID_SIZE + 1] = {0};
    fread(buf_frame, FRAME_ID_SIZE, 1, tag->fptr_src);
    if (strcmp(buf_frame, frame_id) != 0) {
        return e_failure;
    }
    
    int size;
    fread(&size, sizeof(size), 1, tag->fptr_src);
    size = convert_big_little(size);
    
    fseek(tag->fptr_src, 3, SEEK_CUR);
    fread(output, size, 1, tag->fptr_src);
    output[size] = '\0';
    return e_success;
} 
status Song_title(TAG_VIEW *tag) {

    fseek(tag->fptr_src, 10, SEEK_SET);
    char title[128]; // Adjust buffer size as needed
    if (read_frame(tag, "TIT2", title, sizeof(title)) == e_success) {
        printf("Title    : %s\n", title);
    } else {
        printf("Title frame not found or invalid.\n");
    }
    return e_success;
}
/*Artist name*/
status Artist_name(TAG_VIEW *tag) {
    char artist[128]; // Adjust buffer size as needed
    if (read_frame(tag, "TPE1", artist, sizeof(artist)) == e_success) {
        printf("Artist   : %s\n", artist);
    } else {
        printf("Artist frame not found or invalid.\n");
    }
    return e_success;
}
/*Alubm name*/
status Album_name(TAG_VIEW *tag) {
    char album[128]; // Adjust buffer size as needed
    if (read_frame(tag, "TALB", album, sizeof(album)) == e_success) {
        printf("Album    : %s\n", album);
    } else {
        printf("Album frame not found or invalid.\n");
    }
    return e_success;
}

/*Year*/
status year(TAG_VIEW *tag)
{
    char year[128];
    if (read_frame(tag, "TYER", year, sizeof(year)) == e_success) {
        printf("Year     : %s\n", year);
    } else {
        printf("Album frame not found or invalid.\n");
    }
    return e_success;
}
/*content type*/
status content_type(TAG_VIEW *tag)
{
     char content[128];
    if (read_frame(tag, "TCON", content, sizeof(content)) == e_success) {
        printf("content  : %s\n", content);
    } else {
        printf("Album frame not found or invalid.\n");
    }
    return e_success;
}
/*Composer*/
status Composer(TAG_VIEW *tag)
{
     char buf_comp[4];
    fread(buf_comp,4,1,tag->fptr_src);
    buf_comp[4]='\0';
    if(strcmp(buf_comp,"COMM")==0)
    {
        int x3;
        fread(&x3,sizeof(x3),1,tag->fptr_src);
        int size3=convert_big_little(x3);
        fseek(tag->fptr_src,(ftell(tag->fptr_src))+3,SEEK_SET);
        char buf5[size3];
        fread(buf5,size3,1,tag->fptr_src);
        printf("Composer : ");
        for(int i=0;i<size3;i++)
        {
            printf("%c",buf5[i]);
        }
        printf("\n");
        printf("-----------------------------------------------------------------------------\n");
        printf("\n");
        printf("-------------------------DETAILS DISPLAYED SUCCESSFULLY----------------------\n");
        printf("\n");
    }
}


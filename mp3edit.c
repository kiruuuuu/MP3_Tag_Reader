#include<stdio.h>
#include "type.h"
#include<string.h>
#include "edit.h"

/*file open*/
status open_files_e(TAG_EDIT *Tag)
{
    Tag->fptr_src=fopen(Tag->src_fname,"r+");
    if(Tag->fptr_src==NULL)
    {
        return e_failure;
    }
    Tag->fptr_temp_file=fopen(Tag->temp_file,"w");
    if(Tag->fptr_temp_file==NULL)
     {
        return e_failure;
     }
    return e_success;
}

/*read and validate*/
status read_validate(char *argv[],TAG_EDIT *Tag)
{
    if(strstr(argv[4],".mp3")!=NULL)
    {
        Tag->src_fname=argv[4];
    }
    if(argv[3]!=NULL)
    {
       Tag->duplicate=argv[3];
    }
    if(argv[5]==NULL)
    {
        Tag->temp_file="sample.mp3";
    }
    return e_success;
}
/*copy mp3 header*/
status copy_mp3_header(FILE *fptr_src,FILE *fptr_temp_file)
{
    char str[10];
    fseek(fptr_src,0,SEEK_SET);
    fread(str,10,1,fptr_src);
    fwrite(str,10,1,fptr_temp_file);
    return e_success;
}
status mp3_ID_E(TAG_EDIT *Tag)
{
    char buf[4];
    fread(buf,3,1,Tag->fptr_src);
     if(strcmp(buf,"ID3")==0)
     {
        return e_success;
     }
     else
     {
        return e_failure;
     }
}

status check_for_edit(char *argv[],TAG_EDIT *Tag)
{
    copy_mp3_header(Tag->fptr_src,Tag->fptr_temp_file);
    if(strcmp(argv[2],"-t")==0)
    {
        fseek(Tag->fptr_src,10,SEEK_SET);
        char buf_title[4];
        fread(buf_title,4,1,Tag->fptr_src);
        buf_title[4]='\0';
        fwrite(buf_title,4,1,Tag->fptr_temp_file);
        if(strcmp(buf_title,"TIT2")==0)
        all_type(Tag);
        fseek(Tag->fptr_src,67,SEEK_SET);
        copy_remaning_data(Tag);
    }
    else if(strcmp(argv[2],"-ar")==0)
    {
        char buffer[57];
        fread(buffer,57,1,Tag->fptr_src);
        fwrite(buffer,57,1,Tag->fptr_temp_file);
        fseek(Tag->fptr_src,67,SEEK_SET);
        char buf_Artist[4];
        fread(buf_Artist,4,1,Tag->fptr_src);
        buf_Artist[4]='\0';
        fwrite(buf_Artist,4,1,Tag->fptr_temp_file);
        if(strcmp(buf_Artist,"TPE1")==0)
        all_type(Tag);
        fseek(Tag->fptr_src,110,SEEK_SET);
        copy_remaning_data(Tag);

    }
    else if(strcmp(argv[2],"-al")==0)
    {
        char buffer[100];
        fread(buffer,100,1,Tag->fptr_src);
        fwrite(buffer,100,1,Tag->fptr_temp_file);
        fseek(Tag->fptr_src,110,SEEK_SET);
        char buf_Album[4];
        fread(buf_Album,4,1,Tag->fptr_src);
        buf_Album[4]='\0';
        fwrite(buf_Album,4,1,Tag->fptr_temp_file);
        if(strcmp(buf_Album,"TALB")==0)
        all_type(Tag);
        fseek(Tag->fptr_src,129,SEEK_SET);
        copy_remaning_data(Tag);
    }
    else if(strcmp(argv[2],"-y")==0)
    {
        char buffer[119];
        fread(buffer,119,1,Tag->fptr_src);
        fwrite(buffer,119,1,Tag->fptr_temp_file);
        fseek(Tag->fptr_src,129,SEEK_SET);
        char buf_year[4];
        fread(buf_year,4,1,Tag->fptr_src);
        buf_year[4]='\0';
        fwrite(buf_year,4,1,Tag->fptr_temp_file);
        if(strcmp(buf_year,"TYER")==0)
        all_type(Tag);
        fseek(Tag->fptr_src,144,SEEK_SET);
        copy_remaning_data(Tag);
    }
     else if(strcmp(argv[2],"-c")==0)
    {
        char buffer[134];
        fread(buffer,134,1,Tag->fptr_src);
        fwrite(buffer,134,1,Tag->fptr_temp_file);
        fseek(Tag->fptr_src,144,SEEK_SET);
        char buf_cont[4];
        fread(buf_cont,4,1,Tag->fptr_src);
        buf_cont[4]='\0';
        fwrite(buf_cont,4,1,Tag->fptr_temp_file);
        if(strcmp(buf_cont,"TCON")==0)
        all_type(Tag);
        fseek(Tag->fptr_src,185,SEEK_SET);
        copy_remaning_data(Tag);
    }
    else if(strcmp(argv[2],"-cm")==0)
    {
        char buffer[175];
        fread(buffer,175,1,Tag->fptr_src);
        fwrite(buffer,175,1,Tag->fptr_temp_file);
        fseek(Tag->fptr_src,185,SEEK_SET);
        char buf_comp[4];
        fread(buf_comp,4,1,Tag->fptr_src);
        buf_comp[4]='\0';
        printf("%s\n",buf_comp);
        fwrite(buf_comp,4,1,Tag->fptr_temp_file);
        if(strcmp(buf_comp,"COMM")==0)
        all_type(Tag);
        copy_remaning_data(Tag);
    }
    else
    {
         printf("To edit please pass like:./a.out -e -t/-ar/-al/-y/-c/-cm changing_text mp3file\n");
         return 0;
    }
}

/*copy remaining data*/
status copy_remaning_data(TAG_EDIT *Tag)
{
    char ch;
    while(fread(&ch,1,1,Tag->fptr_src)!=0)
    fwrite(&ch,1,1,Tag->fptr_temp_file);
}
/*copying content of all type*/
status all_type(TAG_EDIT *Tag)
{
        int var=strlen(Tag->duplicate);
        int x=Little_big(var+1);
        fwrite(&x,4,1,Tag->fptr_temp_file);
        char buf[3];
        fwrite(buf,3,1,Tag->fptr_temp_file);
        fwrite(Tag->duplicate,strlen(Tag->duplicate),1,Tag->fptr_temp_file);
        printf("\n");
        printf("------------------------------ADDED SUCESSFULLY!!!---------------------------\n");
        printf("\n");
    
}
/*convert little to big endian*/
status Little_big(int x)
{
   int size=((x >> 24) & 0x000000FF) | // Move byte 3 to byte 0
           ((x >> 8)  & 0x0000FF00) | // Move byte 2 to byte 1
           ((x << 8)  & 0x00FF0000) | // Move byte 1 to byte 2
           ((x << 24) & 0xFF000000);  // Move byte 0 to byte 3
           return size;
}
// status file_close(TAG_EDIT *Tag){
//      fclose(Tag->fptr_temp_file);
//      fclose(Tag->fptr_src);
// }
// status file_open_to_transfer(TAG_EDIT *Tag){
//     Tag->fptr_src=fopen(Tag->src_fname,"w");
//     Tag->fptr_temp_file=fopen(Tag->temp_file,"r");
//       char ch;
//         while(fread(&ch,1,1,Tag->fptr_temp_file)!=0){
//             fwrite(&ch,1,1,Tag->fptr_src);
//         }
//     fclose(Tag->fptr_src);
//     fclose(Tag->fptr_temp_file);
// }
   

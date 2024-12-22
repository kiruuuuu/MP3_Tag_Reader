#ifndef TYPE_H
#define TYPE_H
typedef enum
{
    mp3_view,
    mp3_edit,
    mp3_invalid
}opertiontype;

typedef enum
{
    e_failure,
    e_success
}status;

typedef enum{

    edit_Title,
    edit_Artist,
    edit_Album,
    edit_Year,
    edit_unsupported
}opertion;

#endif
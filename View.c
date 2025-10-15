#include<stdio.h>
#include "header.h"
#include<stdlib.h>
#include<string.h>

void view_tag(FILE *fp)
{
    printf("-------------Selected View details-------------\n\n");
    printf("---------------------------------------------\n");
    printf("\tMP3 Tag Reader for ID3v2\n");
    printf("---------------------------------------------\n");
    
    char tag[5];
    int size;

   //skip 10 bytes for header file
   fseek(fp,10,SEEK_SET);
   //loop for 6 times
   for(int i=0;i<6;i++)
   {
   //read tag
   fread(tag,sizeof(char),4,fp);
   tag[4]='\0';
   //read tag size
   fread(&size,sizeof(int),1,fp);
   //convert big to little endian
   Big_To_Little_endian(&size,sizeof(size));
   //skip 3 bytes
   fseek(fp,3,SEEK_CUR);
   //allocate dynamic memory
   char *content=malloc(sizeof(size+1));
   //read content
   fread(content,sizeof(char),size-1,fp);
   //print the tag
   print_tag(tag,content);
   //free dynamic memory
   free(content);
   }
   printf("--------------------------------------------\n\n");
   printf("-------------Details displayed successfully--------------\n\n");
}
//conver big to little endian
void Big_To_Little_endian(void *p,int size)
{
    char t;
    char *p1=(char *)p;
    for(int i=0;i<size/2;i++)
    {
       t=p1[i];
       p1[i]=p1[size-1-i];
       p1[size-1-i]=t;
    }
}
//print tag contents
void print_tag(char *tag, char *content)
{
    if(strcmp(tag,"TIT2")==0)
    printf("Title   :   %s\n",content);
    else if(strcmp(tag,"TPE1")==0)
    printf("Artist  :   %s\n",content);
    else if(strcmp(tag,"TALB")==0)
    printf("Album   :   %s\n",content);
    else if(strcmp(tag,"TYER")==0)
    printf("Year    :   %s\n",content);
    else if(strcmp(tag,"TCON")==0)
    printf("Genre   :   %s\n",content);
    else if(strcmp(tag,"COMM")==0)
    printf("Comment :   %s\n",content);
}

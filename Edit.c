#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "header.h"

void edit_tag(char *filename, char *tag_type, char *new_tag)
{
    char *tag_name=NULL;
    //check tag_type
    if(strcmp(tag_type,"-t")==0)
    tag_name="TIT2";
    else if(strcmp(tag_type,"-a")==0)
    tag_name="TPE1";
    else if(strcmp(tag_type,"-A")==0)
    tag_name="TALB";
    else if(strcmp(tag_type,"-y")==0)
    tag_name="TYER";
    else if(strcmp(tag_type,"-g")==0)
    tag_name="TCON";
    else if(strcmp(tag_type,"-c")==0)
    tag_name="COMM";
    else
    {
    printf("Invalid tag_type\n");
    return;
    }

    FILE *fp,*fp1;
    //open sample.mp3 read mode
    fp=fopen(filename,"r");
    //open temp.mp3 write mode
    fp1=fopen("temp.mp3","w");
    //validate 
    if(!fp || !fp1)
    {
        printf("file not present\n");
        return;
    }
    //copy 10 bytes header to temp.mp3 file
    char header[10];
    //read 10 bytes from sample.mp3 file
    fread(header,sizeof(char),10,fp);
    //write 10 bytes to temp.mp3 file
    fwrite(header,sizeof(char),10,fp1);
    //6 tag loop rotate 6 times
    for(int i=0;i<6;i++)
    {
        char tag[5];
        int size;
        char skip_byte[3];
        int new_size;

        //read tag from sample.mp3file
        fread(tag,sizeof(char),4,fp);
        tag[4]='\0';
        //read tag size from sample.mp3file
        fread(&size,sizeof(int),1,fp);
        //covert big to litten endian
         endian_conversion(&size,sizeof(size));
        //read skip 3 bytes from sample.mp3file
        fread(skip_byte,sizeof(char),3,fp);
        //allocate dynamic memory
        char *content=malloc(size+1);
        //read tag content from sample.mp3file(size-1 because 1byte we already skiped for \0)
        fread(content,sizeof(char),size-1,fp);
        //check entered tag_type and sample.mp3 file tag matching or not
        if(strcmp(tag_name,tag)==0)
        {
          //check new_tag content size
          new_size=strlen(new_tag)+1;
          //copy sample.mp3 file tag to temp.mp3 file
          fwrite(tag,sizeof(char),4,fp1);
          //covert little to big  endian
          endian_conversion(&new_size,sizeof(new_size));
          //copy new_tag content size to temp.mp3 file
          fwrite(&new_size,sizeof(int),1,fp1);
          //copy skip 3 bytes to temp.mp3 file(1 for \0 , 2 for flag)
          fwrite(skip_byte,sizeof(char),3,fp1);
          //covert little to big  endian    
          endian_conversion(&new_size,sizeof(new_size));
          //copy new_tag content to temp.mp3 file
          fwrite(new_tag,sizeof(char),new_size-1,fp1);

          printf("-------------Selected edit details-------------\n\n");
          //print command line tag content
          if(strcmp(tag,"TIT2")==0)
          {
            printf("--------Changed the title---------\n");
            printf("title   :   %s\n",new_tag);
            printf("--------Title Changed successfully---------\n");
          }
          else if(strcmp(tag,"TPE1")==0)
          {
            printf("--------Changed the Artist---------\n");
            printf("Artist  :   %s\n",new_tag);
            printf("--------Artist Changed successfully---------\n");
          }
          else if(strcmp(tag,"TALB")==0)
          {
            printf("--------Changed the Album---------\n");
            printf("Album   :   %s\n",new_tag);
            printf("--------Album Changed successfully---------\n");
          }
          else if(strcmp(tag,"TYER")==0)
          {
            printf("--------Changed the Year---------\n"); 
            printf("Year    :   %s\n",new_tag);
            printf("--------Year Changed successfully---------\n");
          }
          else if(strcmp(tag,"TCON")==0)
          {
            printf("--------Changed the Genre---------\n");
            printf("Genre   :   %s\n",new_tag);
            printf("--------Genre Changed successfully---------\n");
          }
          else if(strcmp(tag,"COMM")==0)
          {
            printf("--------Changed the Comment---------\n"); 
            printf("Comment :   %s\n",new_tag);
            printf("--------Comment Changed successfully---------\n");
          }
          break;
        }
        else//not matching copy sample.mp3 file content to temp.mp3 file until tag match
        {
          //copy sample.mp3 file tag to temp.mp3 file
          fwrite(tag,sizeof(char),4,fp1);
          //covert little to big  endian
          endian_conversion(&size,sizeof(size));
          //copy sample.mp3 file tag size to temp.mp3 file
          fwrite(&size,sizeof(int),1,fp1);
          //covert little to big  endian
          endian_conversion(&size,sizeof(size));
          //copy skip 3 bytes to temp.mp3 file (1 for \0 , 2 for flag)
          fwrite(skip_byte,sizeof(char),3,fp1);
          //copy sample.mp3 file tag content to temp.mp3 file
          fwrite(content,size-1,1,fp1);
        }
      //free dynamically allocated memory
      free(content);
    }

char data;
//read remaing data from sample.mp3 file
while(fread(&data,1,1,fp) > 0)
//copy remaing data to temp.mp3 file
  fwrite(&data,1,1,fp1);

  //close file pointers
  fclose(fp);
  fclose(fp1);
  //remove sample.mp3 file
  remove(filename);
  //rename temp.mp3 file to sample.mp3 file
  rename("temp.mp3",filename);
}
//Endian conversion
void endian_conversion(void *p,int size)
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
                                                                        
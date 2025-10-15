#include<stdio.h>
#include<string.h>
#include "header.h"
void main(int argc,char *argv[])
{
    FILE *fp;
  
    if(argc==3 && strcmp(argv[1],"-v")==0 )
    {
        fp=fopen(argv[2],"rb");
    
        if(fp==NULL)
        {
            printf("file not present\n");
            return;
        } 

        view_tag(fp);
        fclose(fp); 
    }
    else if(argc==5 && strcmp(argv[1],"-e")==0 )
    {
       edit_tag(argv[2],argv[3],argv[4]);
    }
    else if(argc==2)
    {
        printf("---------------HELP MENU----------------\n");
        printf(" -v -> to view mp3 file contents\n");
        printf(" -e -> to edit mp3 file contents\n");
        printf(" -t -> to edit song title\n");  
        printf(" -a -> to edit artist name\n");
        printf(" -A -> to edit album name\n");
        printf(" -y -> to edit year\n");
        printf(" -g -> to edit content\n");
        printf(" -c -> to edit comment\n");
    }
    else
    {
     printf("------------------------------------------\n");
     printf("Error: ./a.out : INVALID ARGUMENTS\n");
     printf("USAGE : ");
     printf("To view : ./a.out -v sample.mp3\n");
     printf("To edit : ./a.out -e sample.mp3 -y 2025\n");
     printf("To get help : ./a.out -help\n");
     printf("------------------------------------------\n");
    }
}


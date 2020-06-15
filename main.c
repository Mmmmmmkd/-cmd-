#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<io.h>
#include<string.h>

int i;
FILE* fp;
char ch;
COORD point={0,0};
HANDLE hOut;

void flash(int fps,int col,int row)
{
    SetConsoleCursorPosition(hOut,point);
    char* read;
    read=(char*)malloc((sizeof(char)*row*col));
    i=0;
    for(;;)
    {
        ch=getc(fp);
        if(ch!=EOF&&i<row*col)
        {
            read[i]=ch;
            i++;
        }
        else
            break;
    }
    puts(read);
    free(read);
    read=NULL;
    fclose(fp);
    Sleep(fps);
}

int main()
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    int fps,row=1,col=1;
    char ch;
    char* name;
    name=(char*)malloc(sizeof(char)*32);
    struct _finddata_t fa;
    long fHandle;
    for(i=0;i<32;i++)
        name[i]='\0';
    FILE* size;
    if( (fHandle=_findfirst( "*.txt", &fa ))==-1L )//这里可以改成需要的目录
    {
    printf( "当前目录下没有txt文件\n");
    exit(0);
    }
    strcpy(name,fa.name);
    if((size=fopen(name,"r"))==NULL)
        exit(0);
    for(;ch!=EOF;)
    {
        ch=getc(size);
        col++;
        if(ch=='\n')
            row++;
    }
    col=col/row;
    free(size);
    size=NULL;
    printf("播放速度(fps):");
    scanf("%d",&fps);
    if(fps>0)
        fps=1000/fps;
    else
    {
        printf("非法输入,以fps24默认速度播放.");
        fps=24;
        Sleep(1000);
    }
    system("cls");
    do
    {
        strcpy(name,fa.name);
        fp=fopen(name,"r");
        flash(fps,col,row);
        fclose(fp);
    }while( _findnext(fHandle,&fa)==0 );
    _findclose( fHandle );
    fp=NULL;
    return 0;
}

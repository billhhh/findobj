#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include <windows.h>

char tFPath[60];//target folder
char dFPath[20];//destination folder

char path[60];//temp path


void fileFinder(char * lpPath,char *fileName) 
{
	char szFind[MAX_PATH],szFile[MAX_PATH];
	
	WIN32_FIND_DATA FindFileData;
	
	strcpy(szFind,lpPath);
	strcat(szFind,"\\*.*");
	
	HANDLE hFind=::FindFirstFile(szFind,&FindFileData);
	
	if(INVALID_HANDLE_VALUE == hFind) 
		return;
	
	while(TRUE) 
	{
		if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
			//���������ļ���
			if(FindFileData.cFileName[0]!='.') 
			{
				strcpy(szFile,lpPath);
				strcat(szFile,"\\");
				strcat(szFile,FindFileData.cFileName);

				//�˴���szFile���ǵ�ǰ�ļ���
				fileFinder(szFile,fileName);
			}
		}
		
		else 
		{
			//�ҵ��ļ��ˡ�����������
			if (strcmp(fileName,FindFileData.cFileName)==0)
			{
				printf("find this file: %s\n",FindFileData.cFileName);

				//���Ƶ�Ŀ���ļ���
				strcat(path,fileName);
				char SysOrder[100]="copy ";
				strcat(SysOrder,path);
				strcat(SysOrder," ");
				strcat(SysOrder,dFPath);
				
				system(SysOrder);
			}
		}
		
		if(!FindNextFile(hFind,&FindFileData)) 
			break;
	}
}


void findFiles(char *fileName)
{	
	strcpy(path,tFPath);
	strcat(path,"\\");
	//strcat(path,fileName);

	fileFinder(path,fileName); //��������ļ������ļ�
	
	//printf("path == %s\n",path);
}


int main()
{
	FILE *fp=NULL;
	char fileName[30];
	char a;
	
	char txtSrc[30];
	printf("Please enter the TXT Source file path:\n");
	scanf("%s",txtSrc);
	
	fp=fopen(txtSrc,"r");
	
	printf("Please enter the target folder path:\n");
	scanf("%s",tFPath);
	
	printf("Please enter the destination folder path:\n");
	scanf("%s",dFPath);
	
	int i=0;
	do
	{
		a=fgetc(fp);
		
		if (a!='\n')
			fileName[i++]=a;
		else
		{
			fileName[i]='\0';
			findFiles(fileName);
			i=0;
		}
		
	}while(a!=EOF);
	
	fclose(fp);
	
	getchar();
	getchar();
	
	return 0;
}
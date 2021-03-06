#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<io.h>
#include <windows.h>

char tFPath[60];//target folder
char dFPath[20];//destination folder

char path[60];//now path
char fatherPath[60];//father path


void fileFinder(char * lpPath,char *fileName) 
{
	strcpy(path,lpPath);
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
			//go deeper folders
			if(FindFileData.cFileName[0]!='.') 
			{
				strcpy(szFile,lpPath);
				strcat(szFile,"\\");
				strcat(szFile,FindFileData.cFileName);

				//szFile is the path of now
				strcpy(fatherPath,path);
				strcpy(path,szFile);
				//strcat(path,"\\");
				fileFinder(szFile,fileName);
			}
		}
		
		else 
		{
			//find the specific file
			if (strcmp(fileName,FindFileData.cFileName)==0)
			{
				printf("find this file: %s\n",FindFileData.cFileName);

				//copy to destination folder
				//make sure szFile has the right path

				strcat(path,"\\");
				printf("path == %s\n",path);

				strcat(path,fileName);
				char SysOrder[100]="copy ";
				strcat(SysOrder,path);
				strcat(SysOrder," ");
				strcat(SysOrder,dFPath);

				//printf("%s\n\n",SysOrder);
				
				system(SysOrder);
			}
		}
		
		if(!FindNextFile(hFind,&FindFileData)) 
		{
			//return to father folder
			strcpy(path,fatherPath);
			break;
		}
	}
}


int main()
{
	//freopen("in.txt","r",stdin);

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
			fileFinder(tFPath,fileName);
			i=0;
		}
		
	}while(a!=EOF);
	
	fclose(fp);

	system("pause");
		
	return 0;
}


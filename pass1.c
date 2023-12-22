#include<stdio.h>
#include<string.h>
struct estab
{
  char csname[10];
  char extsym[10];
  int address;
  int length;
}es[20];
void main()
{
	char input[10],name[10],symbol[10],ch;
	int count=0,progaddr,csaddr,add,len;
	FILE *fp1,*fp2;
	fp1=fopen("INPUT.DAT","r");
	fp2=fopen("ESTAB.DAT","w");
	printf("\n\nEnter the address where the program has to be loaded : ");
	scanf("%x",&progaddr);
	csaddr=progaddr;
	fscanf(fp1,"%s",input);
	while(strcmp(input,"END")!=0)
	{
		if(strcmp(input,"H")==0)
		{
			fscanf(fp1,"%s",name);
			strcpy(es[count].csname,name);
			strcpy(es[count].extsym,"  ");
			fscanf(fp1,"%x",&add);
			es[count].address=add+csaddr;
			fscanf(fp1,"%x",&len);
			es[count].length=len;
			fprintf(fp2,"%s ** %x %x\n",es[count].csname,es[count].address,es[count].length);
			count++;
		}
		else if(strcmp(input,"D")==0)
		{
			fscanf(fp1,"%s",input);
			while(strcmp(input,"R")!=0)
			{
				strcpy(es[count].csname,"  ");
				strcpy(es[count].extsym,input);
				fscanf(fp1,"%x",&add);
				es[count].address=add+csaddr;
				es[count].length=0;
				fprintf(fp2,"** %s %x\n",es[count].extsym,es[count].address);
				count++;
				fscanf(fp1,"%s",input);
			}
			csaddr=csaddr+len;
		}
		else if(strcmp(input,"T")==0)
		{
			while(strcmp(input,"E")!=0)
			fscanf(fp1,"%s",input);
		}
		fscanf(fp1,"%s",input);
	}
  fclose(fp1);
  fclose(fp2);
  fp2=fopen("ESTAB.DAT","r");
  ch=fgetc(fp2);
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp2);
  }
  fclose(fp2);
}

/*
H PROGA 000000 000063
D LISTA 000054
R LISTB ENDB LISTC ENDC
T 000020 0A 03201D 77100004 050014
T 000054 0F 100014 000008 004051 000004 100000
M 000024 05 +LISTB
M 000054 06 +LISTC
M 000060 06 +LISTB
M 000060 06 -LISTA
E 000020

H PROGB 000000 00007F
D LISTB 000060 ENDB 000070
R LISTA LISTC ENDY
T 000036 0B 03100000 772027 05100000
T 000070 0F 100000 000008 004051 000004 100060
M 000037 05 +LISTA
M 00003E 05 -LISTA
M 000070 06 -LISTA
M 000070 06 +LISTC
M 00007C 06 +PROGB
M 00007C 06 -LISTA
E 000000

H PROGC 000000 0000051
D LISTC 000030 ENDC 000042
R LISTA LISTB ENDB
T 000018 0C 03100000 77100004 05100000
T 000042 0F 100030 000008 004051 000004 100000
M 00001D 05 +LISTB
M 000021 05 -LISTA
M 000042 06 -LISTA
M 000042 06 +PROGC
M 00004E 06 +LISTB
M 00004E 06 -LISTA
E
END
*/

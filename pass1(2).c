#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

struct estab
{
    char csname[10];
    char extsym[10];
    unsigned int address;
     int length;
} es[MAX];
int check(char name[100],int count)
{
    for(int i=0;i<count;i++)
    {
        if(!strcmp(name,es[i].csname))
            return 1;
    }
    return 0;

}
int main(void)
{
    char input[100], name[100], symbol[100];
    int count = 0,flag;
    unsigned progaddr, len, csaddr, add;
    FILE *fp1, *fp2;
    system("cls");
    fp1 = fopen("INPUT.dat", "r");
    fp2 = fopen("loadmap.txt", "w");
    printf("Enter the location where the program has to be loaded : ");
    scanf("%x", &progaddr);
    csaddr = progaddr;
    fprintf(fp2, "CS_NAME\tEXT_SYM_NAME\tADDRESS\tLENGTH\n");
    fprintf(fp2, "--------------------------------------\n");
    fscanf(fp1, "%s", input);
    while (strcmp(input, "END") != 0)
    {
        if (strcmp(input, "H") == 0)
        {
            fscanf(fp1, "%s", name);
            flag=check(name,count);
            if(flag==1)
            {
                printf("same cs name:\n");
            }
            strcpy(es[count].csname, name);
            strcpy(es[count].extsym, "**");
            fscanf(fp1, "%d", &add);
            es[count].address = add + csaddr;
            fscanf(fp1, "%x", &len);
            es[count].length = len;
           if(flag!=1)
            {
                fprintf(fp2, "%s\t%s\t\t%x\t%x\n", es[count].csname, es[count].extsym, es[count].address, es[count].length);
            }
            count++;
        }
        else if (strcmp(input, "D") == 0)
        {
            fscanf(fp1, "%s", input);
                    if(flag==1){}
            else{
            while (strcmp(input, "R") != 0)
            {
                strcpy(es[count].csname, "**");
                strcpy(es[count].extsym, input);
                fscanf(fp1, "%x", &add);
                es[count].address = add + csaddr;
                es[count].length = 0;
                fprintf(fp2, "%s\t%s\t\t%x\t%x\n", es[count].csname, es[count].extsym, es[count].address, es[count].length);
                count++;
                fscanf(fp1, "%s", input);
            }
            }
            csaddr = csaddr + len;
        }
        else if (strcmp(input, "T") == 0)
        {
            while (strcmp(input, "E") != 0)
                fscanf(fp1, "%s", input);
        }
        fscanf(fp1, "%s", input);
    }
    fprintf(fp2, "--------------------------------------\n");
    fclose(fp1);
    fclose(fp2);
    printf("FINISHED\n");
    getchar();
    return 0;
}

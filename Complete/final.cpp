#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <string>
#include<stdlib.h>
#include<conio.h>

#include "CSHA1Test.h"
#include "SHA1.cpp"

#include "SHA1.h" // CSHA1 class
using std::endl;

#ifdef _UNICODE
typedef std::wstring tstring;
#define tcout std::wcout
#define tcin std::wcin
#else
typedef std::string tstring;
#define tcout std::cout
#define tcin std::cin
#endif

#pragma warning(push)
// Disable compiler warning 'Unreferenced formal parameter'
#pragma warning(disable: 4100)
// Disable compiler warning 'Conditional expression is constant'
#pragma warning(disable: 4127)
tstring strReport;
void HashFile()
{

	tstring strPath="H:/temp1.txt";


	CSHA1 sha1;
	const bool bSuccess = sha1.HashFile(strPath.c_str());
	sha1.Final();


	sha1.ReportHashStl(strReport, CSHA1::REPORT_HEX_SHORT);

	if(bSuccess)
	{
		//tcout << endl << _T("File contents hashed to:") << endl;
		//tcout << strReport << endl;
	}
	else
		tcout << endl << _T("An error occured (does the file really exist?).") << endl;
}


int num=0;
 struct node
    {
    //int id;
    char *data;
    struct node* left;
    struct node* right;
    };
int main()
{
    FILE* myfile = fopen("new.txt", "r");
    char line1[128];
    int ch;
    int j,i;

    do
    {
    ch = fgetc(myfile);
    if(ch == '\n')
    	num++;
    } while (ch != EOF);

printf("the no of leaves is %d\n",num+1);
int height=0;
int leaves=num;
 while(leaves!=0)
    {
        leaves=leaves/2;
        height++;
    }
//height--;
printf("The height of the tree is %d\n",height);
node merkle[height][64];
   fclose(myfile);


    FILE* myfile1 = fopen("new.txt", "r");
    i=0;
    if ( myfile1 != NULL )
        {
        char line [ 128 ]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, myfile1 ) != NULL ) /* read a line */
        {

                merkle[0][i].data=new char[128];
                merkle[0][i].left=NULL;
                merkle[0][i].right=NULL;

                strcpy(merkle[0][i].data,line);
                i++;
        }

    }

    float c=1;

    for(int row=1;row<=height;row++)
    {
        int ncol=0;
        for(int column=0;column < num*c;)
        {
            FILE *fp1;
            fp1=fopen("H:/temp1.txt","w");
            fprintf(fp1,"%s",merkle[row-1][column].data);
            fprintf(fp1,"%s",merkle[row-1][column+1].data);
            fclose(fp1);
            HashFile();
            char *cptr = new char[strReport.size()+1]; // +1 to account for \0 byte
            strncpy(cptr, strReport.c_str(), strReport.size()+1);
            merkle[row][ncol].data=new char[128];
            strcpy(merkle[row][ncol].data,cptr);
            merkle[row][ncol].left=NULL;
            merkle[row][ncol].right=NULL;
            delete[] cptr;
            ncol++;
            column=column+2;


        }
        c=c/2;
    }
            FILE *fp1;
            fp1=fopen("H:/temp1.txt","w");
            fprintf(fp1,"%s",merkle[2][0].data);
            fprintf(fp1,"%s",merkle[2][1].data);
            fclose(fp1);
            c=1;
            for(int row=height;row<=1;row--)
            {
                for(int column=0;column<2*c;column+2)
                {
                    merkle[row][column].left= &merkle[row-1][column];
                    merkle[row][column].right= &merkle[row-1][column+1];
                }
                c*=2;
            }

                 c=1;

    for(int row=height;row>=0;row--)
    {
        printf("\n\n The %dt h row\n\n",row);

        for(int column=0;column < 1*c;column++)
        {
            printf("%s\n",merkle[row][column].data);

        }
        c=c*2;
    }
    int id1;
    printf("\n\n#####Authentication Path ######\n\n");
    printf("\n\nenter the user id to be authenticated\n");
    printf("\nPlease enter the number less than %d\n",num+1);
    scanf("%d",&id1);
    int column=id1;
    for(int row=0;row<height;row++)
    {

        if(column%2==0)
        printf("%d %d\n",row,column+1);
        else
        printf("%d %d\n",row,column-1);
        column=column/2;
    }
getchar();
getchar();
getchar();
}

#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <dirent.h>
#include<ctype.h>


/* PROTOTYPE DECLARATION for important functions*/
void regularfunction(int j,int argc, char *argv[],int option,int count);
int search(char *filename, char *ch);
int StartsWith(const char *a, const char *b);
int EndsWith(const char *str, const char *suffix);
int withorwithout_option(char *argv[]);
void getoption(char *argv[], int argc);


/* OPTION'S PROTOTYPE */
void help();
int invertsearch(char *filename, char *ch);
int icasesearch(char *filename, char *ch);
int countsearch(char *filename, char *ch);
int fwoutsearch(char *filename, char *ch);
int fwsearch(char *filename, char *ch);
int maxsearch(char *filename, char *ch, int count);


/*MAIN FUNCTION */
int main(int argc, char *argv[])
{
    int flag=0;


    if (argc < 2)
    {
      printf("Not enough command line parameters given!\n");
      return 3;
    }

    flag=withorwithout_option(argv);
    /*without option */
    if(flag==1)
    {
        regularfunction(2,argc,argv,0,0);
    }
    /*with option */
    else if(flag==0)
    {
        getoption(argv,argc);
    }
    return 0;
}


/* This function handle options */
void getoption(char *argv[],int argc)
{
    int i;
    char oppname[1000]={0};
    int k=0,l=0;
    char pattern[1000]={0};
    char filename[1000]={0};
    char c;
    FILE *fp;
    int count;
    char fline[10000];

    for (i = 1; argv[1][i] != 0; i++)
    {
            c=argv[1][i];
            if(c=='=')
                break;
            oppname[k]=argv[1][i];
            k++;
    }
    oppname[k]='\0';
   // printf("it's with option %s",oppname);



    /*matching control options */
    if(!stricmp(oppname,"-help"))
    {
        help();
    }

    else if((strcmp(oppname,"V")==0)||(stricmp(oppname,"-version")==0))
    {
        printf("\nGREPROJECT VERSION : 1.00  ");
        printf("\nLicence : contact <somnathpaul119@gmail.com>  ");
        printf("\nThis is free software: you are free to change and redistributed it  ");
        printf("\ncontact <somnathpaul119@gmail.com for any suggestion, feel free to suggest ");
        printf("\nCopyright \(c\) : <somnathpaul119@gmail.com> and APC college  ");
    }


    else if(stricmp(oppname,"-regexp")==0)
    {
        for (i = 1; argv[1][i] != 0; i++)
        {
            c=argv[1][i];
            if(c=='=')
            {
                l=0;
                for(k=(i+1); argv[1][k]!=0; k++)
                {
                    pattern[l]=argv[1][k];
                    l++;
                }
                pattern[l]='\0';
            }
        }
        argv[1]=pattern;
        regularfunction(2,argc,argv,0,0);
    }
    else if(stricmp(oppname,"e")==0)
    {
        regularfunction(2,argc,argv,0,0);
    }
    else if((strcmp(oppname,"i")==0) || (strcmp(oppname,"y")==0) || (stricmp(oppname,"-ignore-case")==0))
    {
       regularfunction(3,argc,argv,1,0);
    }

    else if((strcmp(oppname,"f")==0) || (stricmp(oppname,"-file")==0))
    {
        if(stricmp(oppname,"-file")==0)
        {
            for (i = 1; argv[1][i] != 0; i++)
            {
                c=argv[1][i];
                if(c=='=')
                {
                    l=0;
                    for(k=(i+1); argv[1][k]!=0; k++)
                    {
                        filename[l]=argv[1][k];
                        l++;
                    }
                    filename[l]='\0';
                }
            }
            fp = fopen(filename, "r");
            if (fp != NULL)
            {
                while (fgets(fline, 1000, fp)!= NULL)
                {
                    argv[1]=fline;
                    regularfunction(2,argc,argv,0,0);
                }
            }
        }
        else
        {
            fp=fopen(argv[2],"r");
            if (fp != NULL)
            {
                while (fgets(fline, 1000, fp)!= NULL)
                {
                    argv[1]=fline;
                    regularfunction(2,argc,argv,0,0);
                }
            }
        }
    }

    else if((strcmp(oppname,"v")==0) || (stricmp(oppname,"-invertmatch")==0))
    {
       regularfunction(3,argc,argv,2,0);
    }


    /*GENERAL OUTPUT CONTROLS */
    else if((strcmp(oppname,"c")==0) || (stricmp(oppname,"-count")==0))
    {
        regularfunction(3,argc,argv,3,0);
    }
    else if((strcmp(oppname,"L")==0) || (stricmp(oppname,"-files-without-match")==0))
    {
        regularfunction(3,argc,argv,4,0);
    }
    else if((strcmp(oppname,"l")==0) || (stricmp(oppname,"-files-with-match")==0))
    {
        regularfunction(3,argc,argv,5,0);
    }
    else if((strcmp(oppname,"m")==0) || (stricmp(oppname,"-max-count")==0))
    {
        if(strcmp(oppname,"m")==0)
        {
            count=atoi(argv[2]);
            regularfunction(4,argc,argv,6,count);
        }
        else
        {
            for (i = 1; argv[1][i] != 0; i++)
            {
                c=argv[1][i];
                if(c=='=')
                {
                    l=0;
                    for(k=(i+1); argv[1][k]!=0; k++)
                    {
                        pattern[l]=argv[1][k];
                        l++;
                    }
                    pattern[l]='\0';
                }

            }
            count=atoi(pattern);
            regularfunction(3,argc,argv,6,count);
        }
    }

    /*multiple options */
    else if((strcmp(oppname,"i-e")==0) || (stricmp(oppname,"i--regexp")==0))
    {
        if(stricmp(oppname,"i--regexp")==0)
        {
            for (i = 1; argv[1][i] != 0; i++)
            {
                c=argv[1][i];
                if(c=='=')
                {
                    l=0;
                    for(k=(i+1); argv[1][k]!=0; k++)
                    {
                        pattern[l]=argv[1][k];
                        l++;
                    }
                    pattern[l]='\0';
                }
            }
            argv[1]=pattern;
            regularfunction(2,argc,argv,1,0);
        }
        else
        {
            regularfunction(2,argc,argv,1,0);
        }
    }

    else
    {
        printf("\nSORRY \" %s  \" is not a valid option for this GREP, or not implemented, we will provide you that option ASAP",oppname);
        help();

    }
}

/* help function */
void help()
{
    printf("\nUSAGE: greproject [OPTION...] <PATTERN> [FILE]......");
    printf("\nSearch for PATTERN in each FILE or standard input.");
    printf("\nExample: greproject -i 'hello world' menu.h main.c");
    printf("\n\n\n GENERIC PROGRAMMING INFORMATION ");
    printf("\n------------------------------------------------------");
    printf("\n        --help\t Print a usage message briefly summarizing\n\t\t\tthe command-line options and then exit ");
    printf("\n -V,    --version\t Print the version number of grep project ");
    printf("\n\n MATCHING CONTROL OPTIONS");
    printf("\n------------------------------------------------------");
    printf("\n -e, --regexp=pattern \tUse pattern for matching ");
    printf("\n -f, --file=FILE \tUse pattern from file ");
    printf("\n -i, --ignore-case \tignore case distinction  ");
    printf("\n -v, --invert-match \tselect non-matching lines ");
    printf("\n\n GENERAL OUTPUT CONTROL");
    printf("\n------------------------------------------------------");
    printf("\n -c, --count \tCount Number of matching line in a file ");
    printf("\n -L, --files-without-match \tprint only names of file containing no matching line ");
    printf("\n -l, --files-with-match \tprint only names of file containing matching line ");
    printf("\n -m num, --max-count=num \tStop reading a file after num matching lines ");
    printf("\n\n OUTPUT LINE PREFIX CONTROL/DEFAULT IN greproject(adv)");
    printf("\n------------------------------------------------------");
    printf("\n -H, --with-filename \tTHIS OPTION IS BY DEFAULT HERE ");
    printf("\n -n, --line-number \tTHIS OPTION IS BY DEFAULT HERE ");
    printf("\n\n\n 'egreproject' means 'greproject -e'. 'fgreproject' means 'greproject -f' ");
    printf("\n Direct invocation as either 'egreprojet' or 'fgreproject' is deprecated. ");
    printf("\n multi option facility provided in this greproject like egreproject with \(-invert-match/-v\) ");
    printf("\n  example 'greproject -i--regexp=cout [file]' ");
    printf("\n \t\tThank u.");


}

/* check 1st argument to know, the 1st argument is option or not */
int withorwithout_option(char *argv[])
{
    int i;
    char c;
    int flag;

        c = argv[1][0];
        if(c=='-')
        {
            flag=0;
        }
        else
        {
            flag=1;
        }
    return(flag);
}

/*REGULAR FUNCTION IMPLEMENTATION */
void regularfunction(int j,int argc, char *argv[], int option,int count)
{
    int i;
    int k=0;
    int l;
    char filename[1000]={0};
    int flag=0;
    int flag2=0;
    DIR *d;
    char c;
    struct dirent *dir;
    char ch[1000]={0};
    char *pattern=argv[j-1];
    if(argv[j-1][0]=='\'')
    {
        for (i = 1; argv[j-1][i] != 0; i++)
        {
                ch[k]=argv[j-1][i];
                k++;
        }
        ch[k-1]='\0';
        flag2=1;
    }
    k=0;
    l=j;
    for(j=l;j<argc;j++)
    {
            memset(filename, 0, 255);
            flag=2;
            if(argv[j][0]=='*')
            {
                for (i = 1; argv[j][i] != 0; i++)
                {
                        filename[k]=argv[j][i];
                        k++;
                }
                filename[k]='\0';
                flag=0;
                goto lp;
            }
            else
            {
                 for (i = 0; argv[j][i] != 0; i++)
                    {
                        c = argv[j][i];
                        if(c=='*')
                        {
                            for(k=0;k<i;k++)
                            {
                                filename[k]=argv[j][k];
                            }
                            filename[i]='\0';
                            flag=1;
                            goto lp;
                        }
                        else
                        {
                           flag=2;
                        }
                    }
            }
            lp:
                if(flag==0 || flag==1)
                {
                    d = opendir(".");
                    if (d)
                    {
                        while ((dir = readdir(d)) != NULL)
                        {
                            if(flag==1)
                            {
                               if(StartsWith(dir->d_name,filename)!=0)
                                {
                                    if(option==2)
                                    {
                                        if(flag2==1)
                                            invertsearch(dir->d_name,ch);
                                        else
                                            invertsearch(dir->d_name,pattern);
                                    }
                                    else if(option==1)
                                    {
                                        if(flag2==1)
                                            icasesearch(dir->d_name,ch);
                                        else
                                            icasesearch(dir->d_name,pattern);
                                    }
                                    else if(option==3)
                                    {
                                        if(flag2==1)
                                            countsearch(dir->d_name,ch);
                                        else
                                            countsearch(dir->d_name,pattern);
                                    }
                                    else if(option==4)
                                    {
                                        if(flag2==1)
                                            fwoutsearch(dir->d_name,ch);
                                        else
                                           fwoutsearch(dir->d_name,pattern);
                                    }
                                    else if(option==5)
                                    {
                                        if(flag2==1)
                                            fwsearch(dir->d_name,ch);
                                        else
                                            fwsearch(dir->d_name,pattern);
                                    }
                                    else if(option==6)
                                    {

                                        if(flag2==1)
                                            maxsearch(dir->d_name,ch,count);
                                        else
                                            maxsearch(dir->d_name,pattern,count);
                                    }
                                    else
                                    {
                                        if(flag2==1)
                                            search(dir->d_name,ch);
                                        else
                                            search(dir->d_name,pattern);
                                    }
                                }
                            }
                            else if(flag==0)
                            {
                                if(EndsWith(dir->d_name,filename)!=0)
                                    if(option==2)
                                    {

                                        if(flag2==1)
                                            invertsearch(dir->d_name,ch);
                                        else
                                            invertsearch(dir->d_name,pattern);
                                    }
                                    else if(option==1)
                                    {

                                        if(flag2==1)
                                            icasesearch(dir->d_name,ch);
                                        else
                                            icasesearch(dir->d_name,pattern);
                                    }
                                    else if(option==3)
                                    {
                                        if(flag2==1)
                                            countsearch(dir->d_name,ch);
                                        else
                                            countsearch(dir->d_name,pattern);
                                    }
                                    else if(option==4)
                                    {
                                        if(flag2==1)
                                            fwoutsearch(dir->d_name,ch);
                                        else
                                            fwoutsearch(dir->d_name,pattern);
                                    }
                                    else if(option==5)
                                    {
                                        if(flag2==1)
                                            fwsearch(dir->d_name,ch);
                                        else
                                            fwsearch(dir->d_name,pattern);
                                    }
                                    else if(option==6)
                                    {
                                        if(flag2==1)
                                            maxsearch(dir->d_name,ch,count);
                                        else
                                            maxsearch(dir->d_name,pattern,count);
                                    }
                                    else
                                    {

                                        if(flag2==1)
                                            search(dir->d_name,ch);
                                        else
                                            search(dir->d_name,pattern);
                                    }
                            }

                        }
                        closedir(d);
                    }
                }
                else if(flag==2)
                {
                    if(option==1)
                    {
                        if(flag2==1)
                            icasesearch(argv[j],ch);
                        else
                            icasesearch(argv[j],pattern);
                    }
                    else if(option==2)
                    {
                        if(flag2==1)
                            invertsearch(dir->d_name,ch);
                        else
                            invertsearch(dir->d_name,pattern);
                    }

                    else if(option==3)
                    {
                        if(flag2==1)
                            countsearch(argv[j],ch);
                        else
                            countsearch(argv[j],pattern);
                    }
                    else if(option==4)
                    {
                        if(flag2==1)
                            fwoutsearch(argv[j],ch);
                        else
                            fwoutsearch(argv[j],pattern);
                    }
                    else if(option==5)
                    {

                        if(flag2==1)
                            fwsearch(dir->d_name,ch);
                        else
                            fwsearch(dir->d_name,pattern);
                    }
                    else if(option==6)
                    {

                        if(flag2==1)
                            maxsearch(dir->d_name,ch,count);
                        else
                            maxsearch(dir->d_name,pattern,count);
                    }
                    else
                    {

                        if(flag2==1)
                            search(argv[j],ch);
                        else
                            search(argv[j],pattern);
                    }
                }
    }
}

/* SEARCH FUNCTION FOR PATTERN SEARCH */
int search(char *filename, char *ch)
{

    FILE *fp;
    char fline[10000], *nline;
    int line=0;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
        line++;
                if (strstr(fline, ch) != NULL)
                {

                    printf("%s  line-%d  %s", filename, line, fline);
                }
        }
        return 0;
}

/* invert SEARCH FUNCTION FOR PATTERN SEARCH */
int icasesearch(char *filename, char *ch)
{

    FILE *fp;
    char fline[10000];
    char nline[10000];
    int line=0;
    int i;
    fp = fopen(filename, "r");
    i=0;
    printf("\n");
    while(ch[i])
    {
        ch[i]=toupper(ch[i]);
        i++;
    }
    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
            memset(nline, '\0', sizeof(nline));
            strncpy(nline,fline,sizeof(fline));
            i=0;
            line++;
            while(nline[i])
            {
                nline[i]=toupper(nline[i]);
                i++;
            }
            if (strstr(nline,ch) != NULL)
            {

                if(fline!=NULL)
                {
                 printf("%s  line-%d  %s", filename, line, fline);
                }
            }
        }
        fclose(fp);

        return 0;
}

/* invert SEARCH FUNCTION FOR PATTERN SEARCH */
int invertsearch(char *filename, char *ch)
{

    FILE *fp;
    char fline[10000];
    int line=0;
    fp = fopen(filename, "r");
    printf("%s",ch);
    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
        line++;
                if (strstr(fline, ch) == NULL)
                {
                    if(fline!=NULL)
                    {
                     printf("%s  line-%d  %s", filename, line, fline);

                    }
                }
        }

        return 0;
}

/* COUNT AND SEARCH OPTION */
int countsearch(char *filename, char *ch)
{

    FILE *fp;
    char fline[10000], *nline;
    int occ=0;
    int line=0;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
        line++;
                if (strstr(fline, ch) != NULL)
                {

                    printf("%s  line-%d  %s", filename, line, fline);
                    occ++;
                }
        }

        printf("\nTOTAL OCCARANCE: %d",occ);
        return 0;
}

/* files without match FUNCTION */
int fwoutsearch(char *filename, char *ch)
{

    FILE *fp;
    char fline[10000], *nline;
    int flag=0;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
            if (strstr(fline, ch) != NULL)
            {
                    flag=1;
            }
        }
        if(flag==0)
        {
           printf("\n%s",filename);
        }

        return 0;
}

/* files without match FUNCTION */
int fwsearch(char *filename, char *ch)
{

    FILE *fp;
    char fline[10000], *nline;
    int flag=0;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
            if (strstr(fline, ch) != NULL)
            {
                    flag=1;
            }
        }
        if(flag==1)
        {
           printf("\n%s",filename);
        }

        return 0;
}

/* SEARCH FUNCTION with count max FOR PATTERN SEARCH */
int maxsearch(char *filename, char *ch, int count)
{

    FILE *fp;
    char fline[10000], *nline;
    int line=0;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
      return 0;
    }
        while (fgets(fline, 1000, fp)!= NULL)
        {
        line++;
                if (strstr(fline, ch) != NULL)
                {
                    printf("%s  line-%d  %s", filename, line, fline);
                    count--;
                    if(count==0)
                        goto max;
                }
        }
        max:
        return 0;
}


/* GET THE FILENAMES THAT COMESWITH FILENAME* */
int EndsWith(const char *str, const char *suffix)
{
    size_t lenstr;
    size_t lensuffix;
    if (!str || !suffix)
        return 0;
     lenstr = strlen(str);
     lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strnicmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

/* GET THE FILENAMES THAT COMESWITH *PATTERN */
int StartsWith(const char *a, const char *b)
{
   if(strnicmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

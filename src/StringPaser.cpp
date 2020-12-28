#include "StringPaser.hpp"
#include <string.h>
#include <stdlib.h>

char *MyFgets(char str[], const int maxn, FILE *fp)
{
    auto r=fgets(str,maxn,fp);
    if(nullptr!=r)
    {
        for(int i= (int) strlen(str) - 1; 0<=i; --i)
        {
            if(str[i]<' ')
            {
                str[i]=0;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        str[0]=0;
    }
    return r;
}


int ParseString(int wordTop[],int wordLen[],int maxlen,char input[])
{
    if(0==maxlen)
    {
        return 0;
    }
    
    int state=0;
    int wordCount=0;
    for(int i=0; 0!=input[i]; ++i)
    {
        if(0==state)
        {
            if(' '<input[i])
            {
                wordTop[wordCount]=i;
                wordLen[wordCount]=1;
                state=1;
                ++wordCount;
            }
        }
        else if(1==state)
        {
            if(input[i]<=' ')
            {
                state=0;
                if(maxlen<=wordCount)
                {
                    break;
                }
            }
            else
            {
                ++wordLen[wordCount-1];
            }
        }
    }
    
    return wordCount;
}


StringPaser::StringPaser()
{
    nw=0;
    str=nullptr;
    wTop=nullptr;
    wLen=nullptr;
}

StringPaser::~StringPaser()
{
    CleanUp();
}

void StringPaser::CleanUp(void)
{
    nw=0;
    if(nullptr!=str)
    {
        delete [] str;
        str=nullptr;
    }
    if(nullptr!=wTop)
    {
        delete [] wTop;
        wTop=nullptr;
    }
    if(nullptr!=wLen)
    {
        delete [] wLen;
        wLen=nullptr;
    }
}

int StringPaser::GetString(const int maxn, FILE *fp)
{
    CleanUp();
    
    str=new char [maxn];
    MyFgets(str, maxn, fp);
    int maxlen= (int) (strlen(str)+1)/2;
    
    wTop=new int [maxlen];
    wLen=new int [maxlen];
    
    nw = ParseString(wTop,wLen,maxlen,str);
    return nw;
}

int StringPaser::Parse(const char incoming[])
{
    CleanUp();
    
    int incominglen = (int) (strlen(incoming)+1);
    int maxlen= (int) (incominglen)/2;
    
    str=new char [incominglen];
    strcpy(str,incoming);
    wTop=new int [maxlen];
    wLen=new int [maxlen];
    nw = ParseString(wTop,wLen,maxlen,str);
    return nw;
}

int StringPaser::GetWord(char *wd, const int maxlen, const int idx) const
{
    if(idx < 0 || idx >= nw){
        return -1;
    }
    
    int len = wLen[idx];
    int top = wTop[idx];
    
    int nChar;
    if(maxlen-1>len)
    {
        nChar=len;
    }
    else
    {
        nChar=maxlen-1;
    }
    
    for(int i=0; i<nChar; ++i)
    {
        wd[i]=str[top+i];
    }
    wd[nChar]=0;
    
    return len;
}

int StringPaser::GetInt(const int idx) const
{
    char wd[256];
    int flag_word = GetWord(wd, 256, idx);
    if(flag_word == -1){
        return 0;
    }
    return atoi(wd);
}

double StringPaser::GetDouble(const int idx) const
{
    char wd[256];
    int flag_word = GetWord(wd, 256, idx);
    if(flag_word == -1){
        return 0;
    }
    return atof(wd);
}

void StringPaser::Print() const{
    if(str != nullptr){
        printf("%s", str);
    }
    else{
        printf("");
    }
}

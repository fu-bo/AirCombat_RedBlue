#ifndef STRINGPASER_HPP
#define STRINGPASER_HPP

#include <stdio.h>

class StringPaser
{
protected:
    int nw;
    int *wTop,*wLen;
    char *str;
    
public:
    StringPaser();
    ~StringPaser();
    void CleanUp(void);
    
    int Parse(const char str[]);
    int GetWord(char wd[], const int maxlen, const int idx) const;
    int GetString(const int maxn, FILE *fp);
    int GetInt(const int idx) const;
    double GetDouble(const int idx) const;
    void Print() const;
};

#endif // STRINGPASER_HPP
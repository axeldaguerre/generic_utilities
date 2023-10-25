inline void str_concat(size_t SourceACount, char *SourceA,
                       size_t SourceBCount, char *SourceB,
                       size_t DestCount, char *Dest)
{
    
    for(int Index = 0;
        Index < SourceACount;
        ++Index)
    {
        *Dest++ = *SourceA++;
    }

    for(int Index = 0;
        Index < SourceBCount;
        ++Index)
    {
        *Dest++ = *SourceB++;
    }

    *Dest = 0;
}

inline int str_len(char *String)
{
    int Count = 0;
    while(*String++)
    {
        ++Count;
    }
    return(Count);
}
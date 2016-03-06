#ifndef CNAMEDPIPLE_H
#define CNAMEDPIPLE_H

#ifdef WIN32
#include <Windows.h>
#else

#endif


#include "mpool.h"

class CNamedPiple
{
public:
    CNamedPiple(const char *name);
    ~CNamedPiple();

    bool    ConnectPipe();

    bool    SendData(const char *buf);
    char*   ReadData();
    void    Close()
    {
        CloseHandle(m_pipe);
    }

private:
    HANDLE      m_pipe;

    MemPool       *m_pool;
};

#endif // CNAMEDPIPLE_H

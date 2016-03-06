#ifndef PIPES_H
#define PIPES_H

#ifdef WIN32
#include <Windows.h>
#endif

#include "mpool.h"

class pipes
{
public:
    pipes();
    ~pipes();
    static pipes& Instance()
    {
        static pipes p;
        return p;
    }

    MemPool* pool()
    {
        return m_pool;
    }

    static bool SendData( HANDLE handle, const char *data);
    static char *ReadData(HANDLE handle);

    MemPool     *m_pool;
};

#endif // PIPES_H

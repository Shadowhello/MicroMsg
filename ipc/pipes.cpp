#include "pipes.h"

pipes::pipes()
{
    m_pool = pool_create(512,10);
}

pipes::~pipes()
{
    pool_release(m_pool);
    delete m_pool;
}

bool pipes::SendData(HANDLE handle, const char *data)
{
    int     len = strlen(data);
    DWORD   writen;

    return WriteFile(handle,data,len,&writen,NULL);
}

char *pipes::ReadData(HANDLE handle)
{
    int         maxlen = 1024;
    DWORD       readen;
    MemPool     *pool = pipes::Instance().pool();
    char        *res = (char*)m_malloc(pool);

    if ( ReadFile(handle,res,maxlen,&readen,NULL) )
    {
        return res;
    }else
    {
        m_free(pool,res);
        return NULL;
    }
}

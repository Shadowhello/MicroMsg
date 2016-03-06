#include <iostream>

#include "cnamedpiple.h"
#include "pipes.h"

CNamedPiple::CNamedPiple( const char* name )
{
    m_pipe = CreateNamedPipeA(name,PIPE_ACCESS_DUPLEX , PIPE_READMODE_BYTE | PIPE_TYPE_BYTE,1,0,0,1000,NULL);

    if ( m_pipe == INVALID_HANDLE_VALUE)
    {
        std::cout<<"Create Pipe Error"<<std::endl;
    }

    m_pool = pool_create(512,10);
}

CNamedPiple::~CNamedPiple()
{
    pool_release(m_pool);
}

bool CNamedPiple::ConnectPipe()
{
    return ConnectNamedPipe(m_pipe,NULL);
}

bool CNamedPiple::SendData(const char *buf)
{
    return pipes::Instance().SendData(m_pipe,buf);
}
char * CNamedPiple::ReadData()
{
    return pipes::Instance().ReadData(m_pipe);
}

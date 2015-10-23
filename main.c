#include <iostream>
#include "memb.h"

using std::cout;
using std::endl;

int main(void)
{
    ///创建线程池的存放的基本单元的数据结构
    struct telnetd_line {
        int fd;
       char line[1024];
    };

    ///初始化线程池
    MEMB_POOL_INIT(linemem, struct telnetd_line, 50);
    memb_init(&linemem);

    ///申请空间
    struct telnetd_line *a=(struct telnetd_line *)memb_alloc(&linemem);
    cout<<a<<endl;
    if(a!= NULL)
        memcpy(a->line,"Mem Manager",10);
    if(a != NULL)
      cout<<a->line<<endl;
    memb_free(&linemem,a);

    ///申请一个空间
    struct telnetd_line *b=(struct telnetd_line *)memb_alloc(&linemem);
      cout<<b<<endl;
    if(b!= NULL)
        memcpy(b->line,"Mem Manager",120);
    if(b !=  NULL)
      cout<<b->line<<endl;
    memb_free(&linemem,b);

    ///销毁线程池
    MEMB_POOL_DESTROY(linemem, struct telnetd_line);


    return 0;

}

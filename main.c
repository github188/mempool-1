#include <iostream>
#include "memb.h"

using std::cout;
using std::endl;

int main(void)
{
    ///�����̳߳صĴ�ŵĻ�����Ԫ�����ݽṹ
    struct telnetd_line {
        int fd;
       char line[1024];
    };

    ///��ʼ���̳߳�
    MEMB_POOL_INIT(linemem, struct telnetd_line, 50);
    memb_init(&linemem);

    ///����ռ�
    struct telnetd_line *a=(struct telnetd_line *)memb_alloc(&linemem);
    cout<<a<<endl;
    if(a!= NULL)
        memcpy(a->line,"Mem Manager",10);
    if(a != NULL)
      cout<<a->line<<endl;
    memb_free(&linemem,a);

    ///����һ���ռ�
    struct telnetd_line *b=(struct telnetd_line *)memb_alloc(&linemem);
      cout<<b<<endl;
    if(b!= NULL)
        memcpy(b->line,"Mem Manager",120);
    if(b !=  NULL)
      cout<<b->line<<endl;
    memb_free(&linemem,b);

    ///�����̳߳�
    MEMB_POOL_DESTROY(linemem, struct telnetd_line);


    return 0;

}

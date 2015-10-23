/**
 * \file
 * Memory block allocation routines.
 * \author Adam Dunkels <adam@sics.se>
 */
#include <string.h>
#include "memb.h"

/*---------------------------------------------------------------------------*/
void
memb_init(struct memb_blocks *m)
{
  if(m==NULL)
      return;
  memset(m->count, 0, m->num);
  memset(m->mem, 0, m->size * m->num);
}

/*---------------------------------------------------------------------------*/
void *
memb_alloc(struct memb_blocks *m)
{

  if(m->mem ==NULL)
    return NULL;

  int i;

  for(i = 0; i < m->num; ++i) {
    if(m->count[i] == 0) {
      /* If this block was unused, we increase the reference count to
	 indicate that it now is used and return a pointer to the
	 memory block. */
      ++(m->count[i]); //标记为已经使用
      return (void *)((char *)m->mem + (i * m->size));
    }
  }

  /* No free block was found, so we return NULL to indicate failure to
     allocate block. */
  return NULL;
}
/*---------------------------------------------------------------------------*/

char
memb_free(struct memb_blocks *m, void *ptr)
{
  int i;
  char *ptr2;

  if(m->mem ==NULL||ptr==NULL)
     return -1;
  /* Walk through the list of blocks and try to find the block to
     which the pointer "ptr" points to. */
  ptr2 = (char *)m->mem;
  for(i = 0; i < m->num; ++i) {

    if(ptr2 == (char *)ptr) {
      /* We've found to block to which "ptr" points so we decrease the
	 reference count and return the new value of it. */
      if(m->count[i] > 0) {
	/* Make sure that we don't deallocate free memory. */
            --(m->count[i]);
            memset(ptr2,0,m->size);
      }
      return m->count[i];
    }
    ptr2 += m->size;
  }
  return -1;
}

int  get_free_blocks_size(struct memb_blocks *m)
{
    if(m->mem == NULL)
      return 0;

    int count=0;
    int i=0;
    for(i=0;i<m->num;i++){
        if(m->count[i]==0)
            count++;
    }
    return count;
}

int  get_free_size(struct memb_blocks *m)
{
    if(m->mem == NULL)
      return 0;

    int count=0;
    int i=0;
    char *ptr=m->mem;
    for(i=0;i<m->size*m->num;i++){
        if(ptr[i] == 0)
            count++;
    }
    return count;
}


/*---------------------------------------------------------------------------*/

/** @} */

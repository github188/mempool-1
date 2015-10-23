/**
 * \file
 *         Memory block allocation routines.
 * \author
 *         Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __MEMB_H__
#define __MEMB_H__


#ifdef __cplusplus
    extern "C"{
#endif

#include<malloc.h>

/*
 * Here we define a C preprocessing macro for concatenating to
 * strings. We need use two macros in order to allow concatenation of
 * two #defined macros.
 */
#define MEMB_CONCAT2(s1, s2) s1##s2
#define MEMB_CONCAT(s1, s2) MEMB_CONCAT2(s1, s2)

/**
 * Declare a memory block.
 *
 * This macro is used to staticall declare a block of memory that can
 * be used by the block allocation functions. The macro statically
 * declares a C array with a size that matches the specified number of
 * blocks and their individual sizes.
 *
 * Example:
 \code
MEMB(connections, sizeof(struct connection), 16);
 \endcode
 *
 * \param name The name of the memory block (later used with
 * memb_init(), memb_alloc() and memb_free()).
 *
 * \param size The size of each memory chunk, in bytes.
 *
 * \param num The total number of memory chunks in the block.
 *
 */

#define MEMB_POOL_INIT(name, structure, num) \
        char* MEMB_CONCAT(name,_memb_count)=(char *)malloc(sizeof(char)*num);\
        structure* MEMB_CONCAT(name,_memb_mem)=(structure *)malloc(sizeof(structure)*num); \
        static struct memb_blocks name = {sizeof(structure), num, \
                                          MEMB_CONCAT(name,_memb_count), \
                                          (void *)MEMB_CONCAT(name,_memb_mem)}\

#define MEMB_POOL_DESTROY(name, structure) \
        free(name.count); name.count=NULL; \
        free(name.mem);  name.mem=NULL; \

struct memb_blocks {
  unsigned short size;  //开辟的单元内存块的字节数
  unsigned short num;   //开辟的内存块数量
  char *count;          //用于记录这块内存是否使用
  void *mem;            //内存块内容
};

/**
 * Initialize a memory block that was declared with MEMB().
 *
 * \param m A memory block previosly declared with MEMB().
 */
void  memb_init(struct memb_blocks *m);

/**
 * Allocate a memory block from a block of memory declared with MEMB().
 *
 * \param m A memory block previosly declared with MEMB().
 */
void *memb_alloc(struct memb_blocks *m);

/**
 * Deallocate a memory block from a memory block previously declared
 * with MEMB().
 *
 * \param m m A memory block previosly declared with MEMB().
 *
 * \param ptr A pointer to the memory block that is to be deallocated.
 *
 * \return The new reference count for the memory block (should be 0
 * if successfully deallocated) or -1 if the pointer "ptr" did not
 * point to a legal memory block.
 */
char  memb_free(struct memb_blocks *m, void *ptr);



int   get_free_size(struct memb_blocks *m);

int   get_free_blocks_size(struct memb_blocks *m);

#ifdef __cplusplus
    }
#endif // __cplusplus

#endif /* __MEMB_H__ */

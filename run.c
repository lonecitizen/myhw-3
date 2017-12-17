#include <sys/types.h>
#include <sys/resource.h>
#include <limits.h>

#include "run.h"
#include "util.h"

void *base = 0;

p_meta find_meta(p_meta *last, size_t size) {
  p_meta index = base;
  p_meta result = base;

  switch(fit_flag){
    case FIRST_FIT:
    {
	while(index -> next == 0){
		if(index -> size >= size && index-> free == 1)
		{
			result = index;
		}
		else if(index -> size < size || index-> free == 0){
			index = index -> next;
		}
	}
	*last = index;
      //FIRST FIT CODE
    }
    break;

    case BEST_FIT:
    {
      //BEST_FIT CODE
    }
    break;

    case WORST_FIT:
    {
      //WORST_FIT CODE
    }
    break;

  }
  return result;
}

void *m_malloc(size_t size) {

	struct rlimit rlim;
	p_meta last_meta = 0;
	p_meta next_meta;
	p_meta temp;
	p_meta curr_meta = find_meta(&last_meta, size);

	if(curr_meta == 0){ //no sufficient block to use
//		if(getrlimit(RLIMIT_AS, &rlim) == 0){ //check available space
//			if(rlim.rlim_max < size){
//				return;
//			}
//		}
		curr_meta = last_meta;
		next_meta = sbrk(0);
		curr_meta -> next = next_meta;
		next_meta -> prev = curr_meta;
		next_meta -> next = sbrk(META_SIZE + size);
		next_meta -> free = 0;
		next_meta -> size = size;
		
		return curr_meta + META_SIZE;
		
	}else
	{
		if(curr_meta -> size > size + 2*META_SIZE)
		{
			curr_meta -> next = temp;
			next_meta -> prev = temp;
			temp -> free = 1;
			temp -> prev = curr_meta;
			temp -> next = next_meta;
			temp -> size = curr_meta -> size - size - META_SIZE;
		}
		curr_meta -> free = 0;
		curr_meta -> size = size;
		return curr_meta + META_SIZE;
	}

}

void m_free(void *ptr) {

}

void* m_realloc(void* ptr, size_t size)
{

}

#include <sys/types.h>
#include <limits.h>

#include "run.h"
#include "util.h"

void *base = 0;
p_meta head = 0;
p_meta last = 0;

p_meta find_meta(p_meta *last, size_t size) {
  p_meta index = base;
  p_meta result = base;

  switch(fit_flag){
    case FIRST_FIT:
    {
      if((*last) == 0) //if no metadata
        return 0;
 
      index = (*last)->prev; //reverse order

      while(index){ 
        if(index->free == 0 || index->size < size)
          index = index->prev; //descend
	else{
          result = index; //get result
          break;
        }
      }
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

  p_meta new = base;
  p_meta prev = base;
  p_meta next = base;
  p_meta temp = base;

  if(new = find_meta(&last, size)){ //block found
    if(new->size > size + META_SIZE){ //if found block has more space enough to
      next = new->next;               //save another metadata and data...
      temp->next = next;
      temp->prev = new;
      temp->size = new->size - META_SIZE; //inserting new metadata between
      temp->free = 1;                     
      new->next = temp;
      next->prev = temp;
    }
    new->free = 0;
    return new + META_SIZE;
  }
  else{                             //failed to find suitable block
    new = sbrk(META_SIZE);
    sbrk(size);
    temp = last->prev;
    last = sbrk(0);
    new->prev = temp;
    new->next = last;
    temp->next = new;
    last->prev = new;
    new->size = size;
    new->free = 0;
    return new + META_SIZE;
  }
}

void m_free(void *ptr) {

}

void* m_realloc(void* ptr, size_t size)
{

}


#ifndef __GLOBAL_MEM_HEAP_APIS_H__
#define __GLOBAL_MEM_HEAP_APIS_H__

//MEM_HEAP_LEVEL (0–5)
//Level 0 : mem mgmt overhead 260B
//Level 1 : mem mgmt overhead 364B
//Level 2 : mem mgmt overhead 568B
//Level 3 : mem mgmt overhead 964B
//Level 4 : mem mgmt overhead 1728B
//Level 5 : mem mgmt overhead 3196B

#ifndef MEM_HEAP_LEVEL
#define MEM_HEAP_LEVEL 1
#endif

#if MEM_HEAP_LEVEL > 5
#error "mem heap level unsupport"
#endif

#define PREFIX_PASTE2(a,b) 	a##b
#define PREFIX_PASTE(a,b)  	PREFIX_PASTE2(a,b)
#define PREFIX_HEAP    		PREFIX_PASTE(stack_heap, MEM_HEAP_LEVEL)

#define stack_heap_init          PREFIX_PASTE(PREFIX_HEAP, _init)
#define stack_heap_malloc        PREFIX_PASTE(PREFIX_HEAP, _malloc)
#define stack_heap_free          PREFIX_PASTE(PREFIX_HEAP, _free)
#define stack_heap_realloc       PREFIX_PASTE(PREFIX_HEAP, _realloc)
#define stack_heap_calloc        PREFIX_PASTE(PREFIX_HEAP, _calloc)
#define stack_heap_statistics	 PREFIX_PASTE(PREFIX_HEAP, _statistics)

EmberStatus stack_heap_init(uint8_t* heap, uint32_t heap_size);

void* stack_heap_malloc(size_t size);

void stack_heap_free(void *ptr);

void* stack_heap_realloc(void *ptr, size_t size);

void* stack_heap_calloc(size_t n, size_t size);

void stack_heap_statistics(size_t* out_total, size_t* out_free);

#endif

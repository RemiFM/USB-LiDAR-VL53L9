/**
  ******************************************************************************
  * @file      sysmem.c
  * @brief     System Memory calls file
  *
  *            For more information about which C functions
  *            need which of these lowlevel functions
  *            please consult the newlib libc manual
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes */
#include <errno.h>
#include <stdint.h>

void *_sbrk(ptrdiff_t incr);

/**
  * Pointer to the current high watermark of the heap usage
  */
static uint8_t *__sbrk_heap_end = NULL;

/**
  * @defgroup SYS_MEM Sysmem Interface (newlib/newlib-nano)
  * @brief Minimal allocation stubs required by GCC newlib on bare-metal.
  * @{
  */

/**
  * @brief _sbrk() allocates memory to the newlib heap and is used by malloc
  *        and others from the C library.
  * @param incr Memory size
  * @return Pointer to allocated memory or -1 on failure (errno is set to ENOMEM)
  *
  * @verbatim
  * ############################################################################
  * #  .data  #  .bss  #       newlib heap       #          MSP stack          #
  * #         #        #                         # Reserved by STACK_SIZE      #
  * ############################################################################
  * ^-- RAM start      ^-- __end__                          __stack, RAM end --^
  * @endverbatim
  *
  * @note This implementation starts allocating at the '__end__' linker symbol
  * The 'STACK_SIZE' linker symbol reserves a memory for the MSP stack.
  * The implementation considers '__stack' linker symbol to be RAM end. Note If
  * the MSP stack, at any point during execution, grows larger than the reserved
  * size, please increase the 'STACK_SIZE'.
  */
void *_sbrk(ptrdiff_t incr)
{
  extern uint8_t __end__; /* Symbol defined in the linker script */
  extern uint8_t __stack; /* Symbol defined in the linker script */
  extern uint32_t STACK_SIZE; /* Symbol defined in the linker script */
  const uint32_t stack_limit = (uint32_t)&__stack - (uint32_t)&STACK_SIZE;
  const uint8_t *max_heap = (uint8_t *)stack_limit;
  uint8_t *prev_heap_end;

  /* Initialize heap end at first call */
  if (NULL == __sbrk_heap_end)
  {
    __sbrk_heap_end = &__end__;
  }

  /* Protect heap from growing into the reserved MSP stack */
  if (__sbrk_heap_end + incr > max_heap)
  {
    errno = ENOMEM;
    return (void *) -1;
  }

  prev_heap_end = __sbrk_heap_end;
  __sbrk_heap_end += incr;

  return (void *)prev_heap_end;
}

/**
  * @}
  */

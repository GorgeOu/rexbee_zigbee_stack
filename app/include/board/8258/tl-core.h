#ifndef __TL_CORE_H__
#define __TL_CORE_H__

#define WEAK(__symbol) \
  __weak __symbol

/**
 * @brief The kind of arguments the main function takes
 */
#define MAIN_FUNCTION_PARAMETERS void
#define MAIN_FUNCTION_ARGUMENTS

#if defined(MAIN_FUNCTION_HAS_STANDARD_ARGUMENTS)
  #define APP_FRAMEWORK_MAIN_ARGUMENTS argc, argv
#else
  #define APP_FRAMEWORK_MAIN_ARGUMENTS 0, NULL
#endif

/** interrupt disable. */
#define CORE_ATOMIC_IRQ_DISABLE()   irq_disable()

/** interrupt enable. */
#define CORE_ATOMIC_IRQ_ENABLE()    irq_enable()

#define INTERRUPTS_ON()				irq_enable()

#define INTERRUPTS_OFF()			irq_disable()

#define CORE_ATOMIC_SECTION(yourcode) \
  {                                   \
    CORE_DECLARE_IRQ_STATE;           \
    CORE_ENTER_ATOMIC();              \
    {                                 \
      yourcode                        \
    }                                 \
    CORE_EXIT_ATOMIC();               \
  }

#define CORE_DECLARE_IRQ_STATE 		uint8_t irqState

#define CORE_ENTER_ATOMIC()   		irqState = irq_disable()
#define CORE_EXIT_ATOMIC()    		irq_restore(irqState)

#endif

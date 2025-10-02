/**
 * @file driver_gpio.c
 * @author duong nguyen nguyen (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "Driverheader/Driver_GPIO.h" 
// Pin mapping
#define GPIO_MAX_PINS           32U
#define PIN_IS_AVAILABLE(n)     ((n) < GPIO_MAX_PINS)


/**
 * @brief  Setup GPIO Interface.
 * 
 * @param pin GPIO Pin
 * @param cb_event  Pointer to \ref ARM_GPIO_SignalEvent
 * @return execution_status
 */
static int32_t GPIO_Setup (ARM_GPIO_Pin_t pin, ARM_GPIO_SignalEvent_t cb_event) 
{
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) 
  {
    
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

/**
 * @brief Set GPIO Direction
 * 
 * @param pin 
 * @param direction 
 * @return int32_t 
 */
static int32_t GPIO_SetDirection (ARM_GPIO_Pin_t pin, ARM_GPIO_DIRECTION direction) 
{
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) 
  {
    switch (direction) {
      case ARM_GPIO_INPUT:
          
    /* CODE */

        break;
      case ARM_GPIO_OUTPUT:
          
    /* CODE */

        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

/**
 * @brief Set GPIO Output Mode
 * 
 * @param pin 
 * @param mode 
 * @return int32_t 
 */
static int32_t GPIO_SetOutputMode (ARM_GPIO_Pin_t pin, ARM_GPIO_OUTPUT_MODE mode) 
{
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) 
  {
    switch (mode) {
      case ARM_GPIO_PUSH_PULL:
          
    /* CODE */

        break;
      case ARM_GPIO_OPEN_DRAIN:
          
    /* CODE */

        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

/**
 * @brief Set GPIO Pull Resistor
 * 
 * @param pin 
 * @param resistor 
 * @return int32_t 
 */
static int32_t GPIO_SetPullResistor (ARM_GPIO_Pin_t pin, ARM_GPIO_PULL_RESISTOR resistor) 
{
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) 
  {
    switch (resistor) {
      case ARM_GPIO_PULL_NONE:
          
    /* CODE */

        break;
      case ARM_GPIO_PULL_UP:
          
    /* CODE */

        break;
      case ARM_GPIO_PULL_DOWN:
          
    /* CODE */

        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

/**
 * @brief Set GPIO Event Trigger
 * 
 * @param pin 
 * @param trigger 
 * @return int32_t 
 */
static int32_t GPIO_SetEventTrigger (ARM_GPIO_Pin_t pin, ARM_GPIO_EVENT_TRIGGER trigger) 
{
  int32_t result = ARM_DRIVER_OK;

  if (PIN_IS_AVAILABLE(pin)) 
  {
    switch (trigger) {
      case ARM_GPIO_TRIGGER_NONE:
          
    /* CODE */

        break;
      case ARM_GPIO_TRIGGER_RISING_EDGE:
          
    /* CODE */

        break;
      case ARM_GPIO_TRIGGER_FALLING_EDGE:
          
    /* CODE */

        break;
      case ARM_GPIO_TRIGGER_EITHER_EDGE:
          
    /* CODE */

        break;
      default:
        result = ARM_DRIVER_ERROR_PARAMETER;
        break;
    }
  } else {
    result = ARM_GPIO_ERROR_PIN;
  }

  return result;
}

// Set GPIO Output Level
/**
 * @brief 
 * 
 * @param pin 
 * @param val 
 */
static void GPIO_SetOutput (ARM_GPIO_Pin_t pin, uint32_t val) 
{

  if (PIN_IS_AVAILABLE(pin)) 
  {
        
    /* CODE */

  }
}

/**
 * @brief Get GPIO Input Level
 * 
 * @param pin 
 * @return uint32_t 
 */
static uint32_t GPIO_GetInput (ARM_GPIO_Pin_t pin) 
{
  uint32_t val = 0U;

  if (PIN_IS_AVAILABLE(pin)) 
  {
    
    /* CODE */

  }
  return val;
}


// GPIO Driver access structure
ARM_DRIVER_GPIO Driver_GPIO0 = {
  GPIO_Setup,
  GPIO_SetDirection,
  GPIO_SetOutputMode,
  GPIO_SetPullResistor,
  GPIO_SetEventTrigger,
  GPIO_SetOutput,
  GPIO_GetInput
};



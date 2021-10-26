// ======================================================================
// \title  LinuxGpioDriverImpl.cpp
// \author tcanham
// \brief  cpp file for LinuxGpioDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================


#include <Drv/STM32GpioDriver/STM32GpioDriverComponentImpl.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Os/TaskString.hpp>

// TODO make proper static constants for these
#include <gpio.h>



namespace Drv {


// Code modified from https://developer.ridgerun.com/wiki/index.php?title=Gpio-int-test.c
    /****************************************************************
    * gpio_export
    ****************************************************************/
    

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void STM32GpioDriverComponentImpl ::
    gpioRead_handler(
        const NATIVE_INT_TYPE portNum,
        bool &state
    )
  {
      

  }

  void STM32GpioDriverComponentImpl ::
    gpioWrite_handler(
        const NATIVE_INT_TYPE portNum,
        bool state
    )
  {
      HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, state);
  }

  bool STM32GpioDriverComponentImpl ::
    open(void) {
      MX_GPIO_Init();
      return true;
  }

  //! Entry point for task waiting for RTI
  


  STM32GpioDriverComponentImpl ::
    ~STM32GpioDriverComponentImpl(void)
  {
      
  }


} // end namespace Drv

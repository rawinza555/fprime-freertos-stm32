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

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  STM32GpioDriverComponentImpl ::
    STM32GpioDriverComponentImpl(
        const char *const compName
    ) : LinuxGpioDriverComponentBase(compName),
  {

  }

  void STM32GpioDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
    STM32GpioDriverComponentBase::init(instance);
  }

} // end namespace Drv

// ======================================================================
// \title  STM32SerialDriverImpl.hpp
// \author tcanham
// \brief  hpp file for STM32SerialDriver component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
//
// ======================================================================

#ifndef STM32SerialDriver_HPP
#define STM32SerialDriver_HPP

#include <Drv/STM32SerialDriver/STM32SerialDriverComponentAc.hpp>
#include <STM32SerialDriverComponentImplCfg.hpp>
#include <Os/Mutex.hpp>

namespace Drv {

  class STM32SerialDriverComponentImpl :
    public STM32SerialDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object STM32SerialDriver
      //!
      STM32SerialDriverComponentImpl(
          const char *const compName /*!< The component name*/
      );

      //! Initialize object STM32SerialDriver
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Configure UART parameters


      // Open device with specified baud and flow control.
      bool open();

      //! start the serial poll thread.
      //! buffSize is the max receive buffer size
      //!

      //! Destroy object STM32SerialDriver
      //!
      ~STM32SerialDriverComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for serialSend
      //!
      void write_handler(
              NATIVE_INT_TYPE portNum, /*!< The port number*/
              Fw::Buffer &serBuffer
          );

      //! Handler implementation for readBufferSend
      //!
      void readPoll_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer& fwBuffer
      );

      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          Fw::Buffer& fwBuffer
      );


    };

} // end namespace Drv

#endif

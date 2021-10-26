// ====================================================================== 
// \title  SerialDriverImpl.cpp
// \author lestarch
// \brief  cpp file for SerialDriver component implementation class
// ====================================================================== 


#include <Drv/STM32SerialDriver/STM32SerialDriver.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------
  void STM32SerialDriverComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    )
  {
      MX_USART3_UART_Init();
  }

  STM32SerialDriverComponentImpl ::
    SerialDriverComponentImpl(
        const char *const compName,
        NATIVE_UINT_TYPE portNum
    ) :
      
  {
    
  }

  STM32SerialDriverComponentImpl ::
    ~STM32SerialDriverComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void STM32SerialDriverComponentImpl ::
    write_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
      HAL_UART_Transmit(&huart3, fwBuffer.getData(), fwBuffer.getSize(), HAL_MAX_DELAY);
  }

  void STM32SerialDriverComponentImpl ::
    readPoll_handler(
        const NATIVE_INT_TYPE portNum,
        Fw::Buffer &fwBuffer
    )
  {
      HAL_UART_Receive(&huart3, fwBuffer.getData(), fwBuffer.getSize(),150);
  }

  void STM32SerialDriverComponentImpl ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum, /*!< The port number*/
        NATIVE_UINT_TYPE context /*!< The call order*/
    )
  {
      Fw::Buffer rx;
      U8 rxData[50];

      HAL_UART_Receive(&huart3, rxData, 50,150);

  }

} // end namespace Svc
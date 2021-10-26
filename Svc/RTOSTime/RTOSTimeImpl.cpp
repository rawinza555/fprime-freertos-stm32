/*
 * TestCommand1Impl.cpp
 *
 *  Created on: Mar 28, 2014
 *      Author: tcanham
 */

#include <Svc/RTOSTime/RTOSTimeImpl.hpp>
#include <Fw/Time/Time.hpp>
#include <cmsis_os.h>

namespace Svc {

    RTOSTimeImpl::RTOSTimeImpl(const char* name) : TimeComponentBase(name)
    {
    }

    RTOSTimeImpl::~RTOSTimeImpl() {
    }

    void LinuxTimeImpl::timeGetPort_handler(
            NATIVE_INT_TYPE portNum, /*!< The port number*/
            Fw::Time &time /*!< The U32 cmd argument*/
        ) {
        TickType_t t = xTaskGetTickCount();

        time.upper = t/1000;
        time.lower = t*1000;
    }

    void LinuxTimeImpl::init(NATIVE_INT_TYPE instance) {
        TimeComponentBase::init(instance);
    }

}

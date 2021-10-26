#include <Components.hpp>
#include <Fw/Types/Assert.hpp>
#include <Os/Task.hpp>
#include <Fw/Logger/Logger.hpp>
#include <Os/Log.hpp>
#include <Fw/Types/MallocAllocator.hpp>



#if defined TGT_OS_TYPE_LINUX || TGT_OS_TYPE_DARWIN
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>
#endif

// List of context IDs


Os::Log osLogger;

// Registry
#if FW_OBJECT_REGISTRATION == 1
static Fw::SimpleObjRegistry simpleReg;
#endif

// Component instance pointers
static NATIVE_INT_TYPE rgDivs[Svc::RateGroupDriverImpl::DIVIDER_SIZE] = {1,2,4};
Svc::RateGroupDriverImpl rateGroupDriverComp(FW_OPTIONAL_NAME("RGDvr"),rgDivs,FW_NUM_ARRAY_ELEMENTS(rgDivs));

static NATIVE_UINT_TYPE rg1Context[] = {0,0,0,0,0,0,0,0,0,0};
Svc::ActiveRateGroupImpl rateGroup1Comp(FW_OPTIONAL_NAME("RG1"),rg1Context,FW_NUM_ARRAY_ELEMENTS(rg1Context));

static NATIVE_UINT_TYPE rg2Context[] = {0,0,0,0,0,0,0,0,0,0};
Svc::ActiveRateGroupImpl rateGroup2Comp(FW_OPTIONAL_NAME("RG2"),rg2Context,FW_NUM_ARRAY_ELEMENTS(rg2Context));

static NATIVE_UINT_TYPE rg3Context[] = {0,0,0,0,0,0,0,0,0,0};
Svc::ActiveRateGroupImpl rateGroup3Comp(FW_OPTIONAL_NAME("RG3"),rg3Context,FW_NUM_ARRAY_ELEMENTS(rg3Context));

// Driver Component
Drv::BlockDriverImpl blockDrv(FW_OPTIONAL_NAME("BDRV"));

// Reference Implementation Components


Svc::ActiveLoggerImpl eventLogger(FW_OPTIONAL_NAME("ELOG"));

Svc::LinuxTimeImpl linuxTime(FW_OPTIONAL_NAME("LTIME"));

Svc::TlmChanImpl chanTlm(FW_OPTIONAL_NAME("TLM"));

Svc::CommandDispatcherImpl cmdDisp(FW_OPTIONAL_NAME("CMDDISP"));

Fw::MallocAllocator mallocator;

Svc::HealthImpl health(FW_OPTIONAL_NAME("health"));

Svc::AssertFatalAdapterComponentImpl fatalAdapter(FW_OPTIONAL_NAME("fatalAdapter"));

Svc::FatalHandlerComponentImpl fatalHandler(FW_OPTIONAL_NAME("fatalHandler"));

Svc::GroundInterfaceComponentImpl ground(FW_OPTIONAL_NAME("ground"));

Drv::STM32SerialDriverComponentImpl serial(FW_OPTIONAL_NAME("serial"));

Drv::STM32GpioDriverComponentImpl ledDrv(FW_OPTIONAL_NAME("ledDrv"));

Svc::RTOSTimeImpl RTOSTime(FW_OPTIONAL_NAME("RTOSTime"));

STM32Blink::LEDBlinkerComponentImpl blinker(FW_OPTIONAL_NAME("blinker"));

const char* getHealthName(Fw::ObjBase& comp) {
   #if FW_OBJECT_NAMES == 1
       return comp.getObjName();
   #else
      return "[no object name]"
   #endif
}

void constructApp() {

    rateGroupDriverComp.init();

    // Initialize the rate groups
    rateGroup1Comp.init(10,0);
    
    rateGroup2Comp.init(10,1);
    
    rateGroup3Comp.init(10,2);

    // Initialize block driver
    blockDrv.init(10);

    // Send/Receive example hardware components

    eventLogger.init(10,0);
    
    RTOSTime.init(0);

    chanTlm.init(10,0);

    cmdDisp.init(20,0);

    fatalAdapter.init(0);
    fatalHandler.init(0);
    health.init(25,0);
    ground.init(0);
    blinker.init(0);
    serial.init(0);
    ledDrv.init(0);


    // Connect rate groups to rate group driver
    constructSTM32BlinkArchitecture();

    // dump topology if requested

    /* Register commands */
    cmdDisp.regCommands();
    eventLogger.regCommands();
    health.regCommands();

    // read parameters
    prmDb.readParamFile();
    // set up BufferManager instances
    
    // set health ping entries

    Svc::HealthImpl::PingEntry pingEntries[] = {
        {3,5,getHealthName(rateGroup1Comp)}, // 0
        {3,5,getHealthName(rateGroup2Comp)}, // 1
        {3,5,getHealthName(rateGroup3Comp)}, // 2
        {3,5,getHealthName(cmdDisp)}, // 3
        {3,5,getHealthName(eventLogger)}, // 4
        {3,5,getHealthName(chanTlm)}, // 6
        {3,5,getHealthName(blockDrv)}, // 10
    };

    // register ping table
    health.setPingEntries(pingEntries,FW_NUM_ARRAY_ELEMENTS(pingEntries),0x123);

    // Active component startup
    // start rate groups
    rateGroup1Comp.start(0, 120,10 * 1024);
    rateGroup2Comp.start(0, 119,10 * 1024);
    rateGroup3Comp.start(0, 118,10 * 1024);
    // start driver
    blockDrv.start(0,140,10*1024);
    // start dispatcher
    cmdDisp.start(0,101,10*1024);
    // start sequencer
    cmdSeq.start(0,100,10*1024);
    // start telemetry
    eventLogger.start(0,98,10*1024);
    chanTlm.start(0,97,10*1024);
    prmDb.start(0,96,10*1024);

    fileDownlink.start(0, 100, 10*1024);
    fileUplink.start(0, 100, 10*1024);
    fileManager.start(0, 100, 10*1024);
    ioTest.start(0, 100, 10*1024);
    ledDrv.open();
    serial.open();

}

void exitTasks(void) {
    rateGroup1Comp.exit();
    rateGroup2Comp.exit();
    rateGroup3Comp.exit();
    ioTest.exit();
    blockDrv.exit();
    cmdDisp.exit();
    eventLogger.exit();
    chanTlm.exit();
    prmDb.exit();
    fileUplink.exit();
    fileDownlink.exit();
    fileManager.exit();
    cmdSeq.exit();
    // join the component threads with NULL pointers to free them
    (void) rateGroup1Comp.ActiveComponentBase::join(NULL);
    (void) rateGroup2Comp.ActiveComponentBase::join(NULL);
    (void) rateGroup3Comp.ActiveComponentBase::join(NULL);
    (void) blockDrv.ActiveComponentBase::join(NULL);
    (void) cmdDisp.ActiveComponentBase::join(NULL);
    (void) eventLogger.ActiveComponentBase::join(NULL);
    (void) chanTlm.ActiveComponentBase::join(NULL);
    (void) prmDb.ActiveComponentBase::join(NULL);
    (void) fileUplink.ActiveComponentBase::join(NULL);
    (void) fileDownlink.ActiveComponentBase::join(NULL);
    (void) fileManager.ActiveComponentBase::join(NULL);
    (void) cmdSeq.ActiveComponentBase::join(NULL);
    comm.stopSocketTask();
    (void) comm.joinSocketTask(NULL);
    cmdSeq.deallocateBuffer(mallocator);
    fileUplinkBufferManager.cleanup();
}


####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponentAi.xml"
    "${CMAKE_CURRENT_LIST_DIR}/LedBlinkerComponentImpl.cpp"
)
set(MOD_DEPS
  STM32Blink/NucleoH7_freeRTOS
  )
register_fprime_module()

####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
####

if(${CMAKE_SYSTEM_NAME} STREQUAL "freertos")
    set(SOURCE_FILES
        "${CMAKE_CURRENT_LIST_DIR}/STM32SerialDriverComponentAi.xml"
        "${CMAKE_CURRENT_LIST_DIR}/STM32SerialDriverComponentImpl.cpp"
    )
    register_fprime_module()
else()
    message(STATUS "Cannot use ${CMAKE_CURRENT_LIST_DIR} with platform ${CMAKE_SYSTEM_NAME}. Skipping.")
endif()


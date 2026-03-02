
cmake_minimum_required(VERSION 3.10)
project(rex_zigbee_stack_library LANGUAGES ASM C)

# Target list
set(demos
  hal_mfglib_demo
  rex_stack_api_usage
  rex_stack_router_demo
  rex_stack_zed_demo
  rex_stack_transparent_demo
  rex_stack_uart_demo
  rex_stack_non_sleepy_zed_demo
)

# Target C macro defines
set(hal_mfglib_demo_C_DEFINES 			  	APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 RZ_STACK_MFG_LIB_DEMO)
set(rex_stack_api_usage_C_DEFINES 			APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 RZ_STACK_API_USAGE)
set(rex_stack_router_demo_C_DEFINES       	APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 RZ_STACK_ROUTER_DEMO)
set(rex_stack_zed_demo_C_DEFINES          	APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 RZ_STACK_ZED_DEMO)
set(rex_stack_transparent_demo_C_DEFINES  	APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 RZ_STACK_TRANSPARENT_DEMO)
set(rex_stack_uart_demo_C_DEFINES 		  	APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 RZ_STACK_UART_DEMO)
set(rex_stack_non_sleepy_zed_demo_C_DEFINES APP_UART_TX_PIN=PORTB_PIN\(1\) APP_UART_RX_PIN=PORTC_PIN\(3\) APP_UART_BAUDRATE=115200 APP_SW_TX_PIN=PORTD_PIN\(2\) APP_SW_BAUDRATE=1000000 STACK_NON_SLEEPY_END_DEVICE RZ_STACK_ZED_DEMO)

# Target library list
set(hal_mfglib_demo_LIBS               		hal-mfg-lib)
set(rex_stack_api_usage_LIBS               	zigbee_stack_router_debug_none)
set(rex_stack_router_demo_LIBS         		zigbee_stack_router_debug_none)
set(rex_stack_zed_demo_LIBS            		zigbee_stack_end_device)
set(rex_stack_transparent_demo_LIBS    		zigbee_stack_router_debug_none)
set(rex_stack_uart_demo_LIBS           		zigbee_stack_router_debug_none)
set(rex_stack_non_sleepy_zed_demo_LIBS 		zigbee_stack_end_device)

# Target output name list
set(hal_mfglib_demo_OUTPUT_NAME               REX_ZB_Mfglib_Demo)
set(rex_stack_api_usage_OUTPUT_NAME           REX_ZB_API_Usage)
set(rex_stack_router_demo_OUTPUT_NAME         REX_ZB_ROT_On_Off_Demo)
set(rex_stack_zed_demo_OUTPUT_NAME            REX_ZB_ZED_Door_Sensor_Demo)
set(rex_stack_transparent_demo_OUTPUT_NAME    REX_ZB_ROT_Transparent_Demo)
set(rex_stack_uart_demo_OUTPUT_NAME           REX_ZB_ROT_Uart_Demo)
set(rex_stack_non_sleepy_zed_demo_OUTPUT_NAME REX_ZB_Non_Sleepy_ZED_Door_Sensor_Demo)

# Project path
set(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

# Toolchain Settings
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PATH}/bin/tc32-elf-gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/bin/tc32-elf-gcc)
set(CMAKE_LINKER       ${TOOLCHAIN_PATH}/bin/tc32-elf-ld)
set(CMAKE_OBJDUMP      ${TOOLCHAIN_PATH}/bin/tc32-elf-objdump)
set(CMAKE_OBJCOPY      ${TOOLCHAIN_PATH}/bin/tc32-elf-objcopy)
set(CMAKE_PRINTSIZE    ${TOOLCHAIN_PATH}/bin/tc32-elf-size)
set(CMAKE_SKIP_RPATH   TRUE)

# Compiler options
set(C_INCLUDE_OPTS -I${ProjDirPath}/app/include)
set(C_OPTS         -fpack-struct -fshort-enums -Os -std=gnu99 -fshort-wchar -fms-extensions -finline-small-functions -ffunction-sections -fdata-sections -Wall)

set(CMAKE_C_LINK_EXECUTABLE
    "${CMAKE_LINKER} --gc-sections <LINK_FLAGS> <FLAGS> -T ${ProjDirPath}/boot.link -o <TARGET> <OBJECTS> <LINK_LIBRARIES>"
)

set(ASM_DEFINE_OPTS MCU_STARTUP_8258)
set(GENERIC_LIBS soft-fp hal_xtal hal_radio_pm)

# collect_app_sources(<folder> <outVar>)
function(collect_app_sources folder outVar)
  file(GLOB_RECURSE _srcs RELATIVE ${folder}
    ${folder}/*.c
    ${folder}/*.S
  )
  set(_full_srcs)
  foreach(_f IN LISTS _srcs)
    list(APPEND _full_srcs ${folder}/${_f})
  endforeach()
  set(${outVar} ${_full_srcs} PARENT_SCOPE)
endfunction()


# Generate targets
foreach(tgt IN LISTS demos)
  collect_app_sources(${ProjDirPath}/app srcs)
  list(FILTER srcs EXCLUDE REGEX ".*/${tgt}/.*")

  add_executable(${tgt} ${srcs})
  set_target_properties(${tgt} PROPERTIES
  					    SUFFIX ".elf"
						RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  )

  #add_library(${tgt} ${srcs})
  #set_target_properties(${tgt} PROPERTIES
  #						 SUFFIX ".a"
  #	    				 RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
  #)

  target_compile_options(${tgt} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:${C_INCLUDE_OPTS}>
    $<$<COMPILE_LANGUAGE:C>:${C_OPTS}>
  )

  target_compile_definitions(${tgt} PRIVATE
    $<$<COMPILE_LANGUAGE:C>:${${tgt}_C_DEFINES}>
    $<$<COMPILE_LANGUAGE:ASM>:${ASM_DEFINE_OPTS}>
  )

  target_link_directories(${tgt} PRIVATE ${ProjDirPath}/library)

  target_link_libraries(${tgt} PRIVATE ${${tgt}_LIBS} ${GENERIC_LIBS})

  set(PRE_BUILD_SCRIPT ${ProjDirPath}/tools/rex_global_pre_build.sh)
  foreach(_lib IN LISTS ${tgt}_LIBS)
    if(_lib MATCHES "router" OR _lib MATCHES "mfg-lib")
      set(PRE_BUILD_SCRIPT ${ProjDirPath}/tools/rex_global_router_pre_build.sh)
      break()
    elseif(_lib MATCHES "coo")
      set(PRE_BUILD_SCRIPT ${ProjDirPath}/tools/rex_global_coo_pre_build.sh)
      break()
    endif()
  endforeach()
  message("${tgt} pre build script ${PRE_BUILD_SCRIPT}")
  add_custom_command(TARGET ${tgt} PRE_BUILD
    COMMAND bash ${PRE_BUILD_SCRIPT} ${ProjDirPath}
  )
  add_custom_command(TARGET ${tgt} POST_BUILD
    COMMAND bash ${ProjDirPath}/tools/rex_global_post_build.sh ${${tgt}_OUTPUT_NAME} ${ProjDirPath} ${tgt} ${TOOLCHAIN_PATH}
    #COMMAND ${CMAKE_OBJDUMP} -x -D -l -S $<TARGET_FILE:${tgt}> > $<TARGET_FILE_DIR:${tgt}>/${tgt}.lst
    #COMMAND ${CMAKE_PRINTSIZE} -t $<TARGET_FILE:${tgt}>
  )
endforeach()

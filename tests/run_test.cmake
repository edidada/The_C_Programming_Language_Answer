# 跨平台测试包装：cmake -DEXE=<exe> [-DARGS=<空格分隔参数>] -DINPUT=<输入文件> -P run_test.cmake
# 用 execute_process 的 INPUT_FILE 模拟 stdin 重定向，避免依赖 sh。

if(DEFINED ARGS AND NOT ARGS STREQUAL "")
    separate_arguments(ARGS NATIVE_COMMAND "${ARGS}")
else()
    set(ARGS "")
endif()

execute_process(COMMAND ${EXE} ${ARGS}
    INPUT_FILE ${INPUT}
    OUTPUT_QUIET ERROR_QUIET
    RESULT_VARIABLE rc
    TIMEOUT 10)

if(NOT rc EQUAL 0)
    message(FATAL_ERROR "program exited with: ${rc}")
endif()

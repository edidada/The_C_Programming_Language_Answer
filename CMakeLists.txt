cmake_minimum_required(VERSION 3.16)
project(the_c_programming_language_answers C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-w)

enable_testing()

# 依赖 K&R 书中 Chapter 8 内部头文件（_stdio.h / _alloc.h 等）或本身是代码片段，
# 无法用系统 libc 头直接编译，不参与构建。
set(NON_COMPILABLE
    ${CMAKE_SOURCE_DIR}/Chapter_2/2-2.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-2.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-3.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-4.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-5.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-6.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-7.c
    ${CMAKE_SOURCE_DIR}/Chapter_8/8-8.c
)

# 需要交互终端输入、在 CI 中无法非交互跑完的程序，不注册为可运行测试
set(NO_CI_RUN
)

# 统一喂给各练习程序的测试输入（避免依赖交互式 stdin）
set(test_input ${CMAKE_SOURCE_DIR}/tests/ci_input.txt)

# 个别程序需要命令行参数或专用输入
set(TEST_ARGS_Chapter_7_7_6 "${CMAKE_SOURCE_DIR}/tests/ci_input.txt ${CMAKE_SOURCE_DIR}/tests/ci_input.txt")
set(TEST_ARGS_Chapter_7_7_7 "hello ${CMAKE_SOURCE_DIR}/tests/ci_input.txt")
set(TEST_INPUT_Chapter_5_5_19 "dcl_input.txt")

file(GLOB exercise_sources CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/Chapter_*/*.c)

foreach(src ${exercise_sources})
    if(src IN_LIST NON_COMPILABLE)
        continue()
    endif()

    file(RELATIVE_PATH name ${CMAKE_SOURCE_DIR} ${src})
    string(REGEX REPLACE "[/.-]" "_" name ${name})
    string(REGEX REPLACE "_c$" "" name ${name})

    file(READ ${src} code)
    if(code MATCHES "[^a-zA-Z0-9_]main\\s*\\(")
        add_executable(${name} ${src})
        # 部分计算类练习使用 sin/cos/exp/pow/fmod
        target_link_libraries(${name} m)
        if(NOT src IN_LIST NO_CI_RUN)
            set(run_input ${test_input})
            if(DEFINED TEST_INPUT_${name})
                set(run_input ${CMAKE_SOURCE_DIR}/tests/${TEST_INPUT_${name}})
            endif()
            add_test(NAME ${name} COMMAND sh -c "$<TARGET_FILE:${name}> ${TEST_ARGS_${name}} < ${run_input}")
            set_tests_properties(${name} PROPERTIES TIMEOUT 10)
        endif()
    else()
        add_library(${name} OBJECT ${src})
    endif()
endforeach()

# 部分练习的 main 依赖其他练习文件/支撑文件中的函数，这里显式接线。
function(link_extra target)
    foreach(lib ${ARGN})
        target_link_libraries(${target} ${lib})
    endforeach()
endfunction()

link_extra(Chapter_4_4_6  Chapter_4_support_calc)
link_extra(Chapter_5_5_10 Chapter_4_support_calc Chapter_4_4_7)
link_extra(Chapter_5_5_12 Chapter_5_support_entab)
link_extra(Chapter_5_5_14 Chapter_5_support_sort_readlines Chapter_5_support_sort_numcmp)
link_extra(Chapter_5_5_15 Chapter_5_support_sort_readlines Chapter_5_support_sort_numcmp Chapter_5_support_sort_writelines)
link_extra(Chapter_5_5_16 Chapter_5_support_sort_readlines Chapter_5_support_sort_numcmp Chapter_5_support_sort_writelines)
link_extra(Chapter_5_5_17 Chapter_5_support_sort_readlines Chapter_5_support_sort_writelines Chapter_5_support_sort_error)
link_extra(Chapter_5_5_13 Chapter_5_support_getline)
link_extra(Chapter_5_5_19 Chapter_5_5_18 Chapter_4_support_calc)
link_extra(Chapter_6_6_2  Chapter_6_6_1 Chapter_4_support_calc)
link_extra(Chapter_6_6_3  Chapter_6_6_1 Chapter_4_support_calc)
link_extra(Chapter_6_6_6  Chapter_6_6_1 Chapter_4_support_calc Chapter_4_4_7 Chapter_6_support_define)
link_extra(Chapter_8_8_1  Chapter_8_support_error)

# macOS SDK 的 stdio.h 无条件声明 POSIX getline，与练习中的 int getline(char*, int) 冲突；
# Linux (glibc + -std=c99) 无此问题。本地 macOS 构建时用 _ANSI_SOURCE 隐藏 POSIX 扩展。
if(APPLE)
    foreach(t Chapter_5_5_6 Chapter_5_5_13 Chapter_5_support_getline)
        if(TARGET ${t})
            target_compile_definitions(${t} PRIVATE _ANSI_SOURCE)
        endif()
    endforeach()
endif()

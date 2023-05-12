cmake_minimum_required (VERSION 3.8)

project(GeneralCFLDog)


SET(LIB_NAME GeneralCFLDog)
add_definitions("-DGeneralDOG_EXPORTS")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    add_compile_options(/MTd)
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    add_compile_options(/MT)
endif()


SET(COMMON_SOURCE_FILES
	GenerateDog.cpp
)

SET(COMMON_HEADER_FILES
	cflMD5.h
	../include/cflTime.hpp
	../include/GenerateDog.h
)
include_directories(
	..
	../include
	../third
)

if (0)
#add_executable(${PROJECT_NAME}
#	${COMMON_HEADER_FILES}
#	${COMMON_SOURCE_FILES}
#)

#if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
#    set_target_properties(${PROJECT_NAME}
#        PROPERTIES
#    OUTPUT_NAME ${PROJECT_NAME}D
#    )
#endif()
else()
#add_library(${LIB_NAME} SHARED
add_library(${LIB_NAME} STATIC 
	${COMMON_HEADER_FILES}
	${COMMON_SOURCE_FILES}
)
endif()


#cryptlib.lib
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
target_link_libraries(${PROJECT_NAME} ${prj_dir}/lib/Debug/cryptlib.lib )
else()
target_link_libraries(${PROJECT_NAME} ${prj_dir}/lib/Release/cryptlib.lib )
endif()

source_group(${CFL_HEADER_FILES} FILES ${COMMON_HEADER_FILES})
source_group(${CFL_SOURCE_FILES} FILES ${COMMON_SOURCE_FILES})
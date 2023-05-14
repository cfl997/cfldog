cmake_minimum_required (VERSION 3.8)

#project(GeneralDogKey)
project(GeneralDogKey)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(LIB_NAME GeneralDogKey)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    add_compile_options(/MTd)
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    add_compile_options(/MT)
endif()

SET(COMMON_SOURCE_FILES
	GeneralKey.cpp
)

SET(COMMON_HEADER_FILES
	#cflMD5.h
	#../include/GenerateDog.h
)
include_directories(
	..
	../include
)

if (1)
add_executable(${PROJECT_NAME}
	#${COMMON_HEADER_FILES}
	${COMMON_SOURCE_FILES}
)

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}D
    )
endif()
else()
add_library(${LIB_NAME} SHARED
	${COMMON_HEADER_FILES}
	${COMMON_SOURCE_FILES}
)
endif()


link_directories(
	${prj_dir}/lib
)

target_link_libraries(${PROJECT_NAME} ${prj_dir}/lib/GeneralCFLDog${CMAKE_DEBUG_POSTFIX}.lib )
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
target_link_libraries(${PROJECT_NAME} ${prj_dir}/lib/Debug/cryptlib.lib )
else()
target_link_libraries(${PROJECT_NAME} ${prj_dir}/lib/Release/cryptlib.lib )
endif()


source_group(${CFL_HEADER_FILES} FILES ${COMMON_HEADER_FILES})
source_group(${CFL_SOURCE_FILES} FILES ${COMMON_SOURCE_FILES})

add_dependencies(${PROJECT_NAME} 
GeneralCFLDog
)
cmake_minimum_required (VERSION 3.8)

project(cfldog)


set(prj_dir ${PROJECT_SOURCE_DIR})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY				"${prj_dir}/bin64/")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG		"${prj_dir}/bin64/")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE		"${prj_dir}/bin64/")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY				"${prj_dir}/lib/")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG		"${prj_dir}/lib/")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE		"${prj_dir}/lib/")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY				"${prj_dir}/lib/") #for .lib
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG		"${prj_dir}/lib/") #for .lib
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE		"${prj_dir}/lib/") #for .lib
 

list(APPEND CMAKE_MODULE_PATH "${prj_dir}/cmake/")


if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_DEBUG_POSTFIX "D")
    set(XCG_MODULE_SUFFIX ${CMAKE_DEBUG_POSTFIX})
    add_definitions("-D_DEBUG")
else()
    set(CMAKE_DEBUG_POSTFIX "")
    set(XCG_MODULE_SUFFIX "")
endif()


SET(CFL_HEADER_FILES "HeaderFiles")
SET(CFL_SOURCE_FILES "SourceFiles")


add_subdirectory ("Src")
add_subdirectory ("Test")

#ÎÄ¼þ¼Ð
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)




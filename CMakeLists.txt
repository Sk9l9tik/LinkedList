#general info
cmake_minimum_required(VERSION 3.12) #cmake minimum version

set(proj_name list)
project(${proj_name})
message("------------ Project files genertion for ${proj_name} ------------")


#common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message("Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if(MCVS)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${proj_name})
endif(MCVS)
                                                            

#cpp options
set(CMAKE_CXX_STANDART 17)



#app options
set(INC
	"inc/List.h"
	"inc/Subj.hpp"
)

set(SRC 
	"src/List.cc"
	"src/main.cc"
	"src/Subj.cc"
)


source_group("Header Files" FILES "src/List.h")

source_group("Source Files" FILES "src/List.cc" "src/main.cc")


add_executable(${proj_name} ${SRC} ${INC})

#includes
target_include_directories(${proj_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
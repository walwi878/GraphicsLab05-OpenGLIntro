# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (COSC_Lab_OpenGL1)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP




include_directories(
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# OpenGL Part 1
add_executable(Part01
	Part01/simpleWindow.cpp
)
target_link_libraries(Part01
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(Part01 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Part01/")
create_target_launcher(Part01 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Part01/")
create_default_target_launcher(Part01 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Part01/")

# OpenGL Lab 2
add_executable(Part02
	Part02/redTriangle.cpp
	common/Shader.cpp
	common/Shader.hpp
    common/ColorShader.hpp
    common/ColorShader.cpp
    common/Camera.hpp
    common/Camera.cpp
    common/Scene.hpp
    common/Scene.cpp
    common/Quad.hpp
    common/Quad.cpp
    common/Object.hpp
    common/Object.cpp
    common/Triangle.hpp
    common/Triangle.cpp
    common/Shader.hpp
    common/Shader.cpp
	Part02/basicShader.frag
	Part02/basicShader.vert
   	
)
target_link_libraries(Part02
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(Part02 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Part02/")
create_target_launcher(Part02 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Part02/")

# OpenGL Lab03
add_executable(Part03
	Part03/texturedCube.cpp
	common/Shader.cpp
	common/Shader.hpp
	common/Texture.cpp
	common/Texture.hpp
    common/Camera.hpp
    common/Camera.cpp
    common/Scene.hpp
    common/Scene.cpp
    common/Object.hpp
    common/Object.cpp
    common/Triangle.hpp
    common/Triangle.cpp
    common/Shader.hpp
    common/Shader.cpp
    common/Shader.hpp
    common/TextureShader.hpp
    common/TextureShader.cpp
    common/Mesh.hpp
    common/Mesh.cpp

	Part03/textureShader.frag
	Part03/textureShader.vert
)
target_link_libraries(Part03
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(Part03 PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Part03/")
create_target_launcher(Part03 WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Part03/")


SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET Part01 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Part01${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Part01/"
)
add_custom_command(
   TARGET Part02 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Part02${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Part02/"
)

add_custom_command(
   TARGET Part03 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Part03${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Part03/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )


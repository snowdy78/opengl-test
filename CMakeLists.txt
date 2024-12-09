cmake_minimum_required(VERSION 3.25)
project(OpenGLTest LANGUAGES CXX)
set(MY_PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(MY_PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MY_PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MY_PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MY_PROJECT_SOURCE_DIR}/bin)

include(FetchContent)
include(ExternalProject)

fetchcontent_declare(GLFW
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4)

fetchcontent_makeavailable(GLFW)

fetchcontent_declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

fetchcontent_makeavailable(glm)

fetchcontent_declare(
  glew
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG origin/master
)
fetchcontent_getproperties(glew)
if(NOT glew_POPULATED)
  fetchcontent_populate(glew)

  add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
externalproject_add(glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
  CMAKE_ARGS
  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
  -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
  -DGLAD_PROFILE= "core"
  -DGLAD_GENERATOR= "c"
  SOURCE_DIR "${CMAKE_BINARY_DIR}/install/glad"
  CONFIGURE_COMMAND "" #do not configure
  BUILD_COMMAND "" #do not buld
  INSTALL_COMMAND "" #installer for now is empty
)
set(GL_VERSION "4.3")
set(GLAD_LIB "glad_gl_core_43")

file(
  GLOB_RECURSE
  PROJECT_SOURCE_FILES
  ${MY_PROJECT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE
  PROJECT_INCLUDE_FILES
  ${MY_PROJECT_SOURCE_DIR}/include/*.hpp
)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_INSTALL OFF)
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${PROJECT_INCLUDE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin)

target_include_directories(${PROJECT_NAME} PRIVATE "${MY_PROJECT_SOURCE_DIR}/include")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE libglew_static)
add_subdirectory(external/glad)

target_link_libraries(${PROJECT_NAME} PUBLIC Glad)

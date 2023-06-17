cmake_minimum_required(VERSION 3.11)
include(FetchContent)
project(LuaTest LANGUAGES C CXX)

set(LUA_VERSION "5.4.6")
set(LUA_HASH "SHA256=7d5ea1b9cb6aa0b59ca3dde1c6adcb57ef83a1ba8e5432c0ecd06bf439b3ad88")

FetchContent_Declare(
	lua
	URL https://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz
	URL_HASH ${LUA_HASH}
)

FetchContent_GetProperties(lua)
if(NOT lua_POPULATED)
	FetchContent_Populate(lua)
endif()

set(LUA_SRC ${lua_SOURCE_DIR}/src)
file(GLOB ${PROJECT_NAME}_SRC ${LUA_SRC}/*.c ${LUA_SRC}/*.h *.cpp *.h *.def)
list(REMOVE_ITEM ${PROJECT_NAME}_SRC ${LUA_SRC}/lua.c ${LUA_SRC}/luac.c)
message("SRC: ${${PROJECT_NAME}_SRC}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) #Eg. -std=c++17 instead of -std=gnu++17

# IDE configuration
set_property(GLOBAL PROPERTY USE_FOLDERS ON) #allows the creation of solution folders

if(UNIX)
	add_definitions(-DLUA_USE_POSIX)
endif()

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE BOGUS_HASH_DEF)
target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_SRC})
target_link_libraries(${PROJECT_NAME} ${LIBCXX})


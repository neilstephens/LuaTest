 
extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include <iostream>

int main(int argc, char** argv)
{
	lua_State* L = luaL_newstate(); // Create a new state.
	luaL_dostring(L, " x = 42"); // Execute lua code.
	// Get global variable called 'x' and push it to the start of the Lua stack.
	lua_getglobal(L, "x");
	lua_Number x = lua_tonumber(L, 1); // Get the value at the top of the stack.
	std::cout << "Lua says "<< x << std::endl;
	lua_close(L); // Deallocate the LUA state.
	return 0;
}

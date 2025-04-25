#pragma once
#include <sol/sol.hpp>
struct Lua {
	sol::state runtime;

	void init_lua();
	Lua();
};

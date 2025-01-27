#include <lua.h>
#include <lauxlib.h>

// 인수에 50을 곱해서 반환하는 함수
static int l_mult50(lua_State* L) {
    double number = luaL_checknumber(L, 1);
    lua_pushnumber(L, number * 50);
    return 1;
}

int luaopen_libnativefunc(lua_State* L) {
    static const struct luaL_Reg nativeFuncLib[] = {
        { "mult50", l_mult50 },
        { NULL, NULL }
    };

    luaL_register(L, "nativelib", nativeFuncLib);
    return 1;
}

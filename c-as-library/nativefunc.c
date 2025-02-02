#include <lua.h>
#include <lauxlib.h>

// 인수에 50을 곱해서 반환하는 함수
static int l_mult50(lua_State* L) {
    double number = luaL_checknumber(L, 1); // 스택에서 인수를 가져온다
    lua_pushnumber(L, number * 50); // 결과를 스택에 푸시한다
    return 1; // 반환값의 개수를 반환한다
}

int luaopen_libnativefunc(lua_State* L) {
    static const struct luaL_Reg nativeFuncLib[] = {
        { "mult50", l_mult50 },
        { NULL, NULL } // sentinel
    };

    // register 함수는 package.loaded table에 두 번째 인수를 등록 시킨다
    luaL_register(L, "nativelib", nativeFuncLib);
    /*
     register 함수는 스택에 table을 남겨놓기 때문에
     이를 반환하기 위해서 반환값의 개수인 1을 반환한다
     라이브러리가 이미 전역 변수에 할당 되었기 때문에
     이 반환은 선택 사항이다
    */
    return 1;
}

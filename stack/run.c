#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>

void print_stack(lua_State* L) {
    printf("{ ");
    int sz = lua_gettop(L);

    for (int i = 1; i <= sz; ++i) {
        switch (lua_type(L, i)) {
            case LUA_TNIL:
                printf("nil");
                break;
            case LUA_TBOOLEAN:
                printf("%s", lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                printf("%g", lua_tonumber(L, i));
                break;
            case LUA_TSTRING:
                // null까지만 출력하는 것에 주의
                printf("\"%s\"", lua_tostring(L, i));
                break;
            default:
                printf("%s", lua_typename(L, lua_type(L, i)));
        }
        if (i != sz) printf(", ");
    }

    printf(" }\n");
}

int main() {
// open state
    lua_State* L = lua_open();
    if (L == NULL) {
        fprintf(stderr, "%s\n", "Failed to create Lua state.");
        return 1;
    }

    print_stack(L);

// push element
    lua_pushnil(L);
    lua_pushboolean(L, 1);
    lua_pushnumber(L, 3.14);
    lua_pushlstring(L, "hello", 5);
    lua_pushstring(L, "1234");

    print_stack(L);

// check stack
    printf("LUA_MINSTACK: %d\n", LUA_MINSTACK);
    printf("check stack: %d\n", lua_checkstack(L, 50));

// querying element
    /* lua_is* */ {
        printf("is nil 1: %d\n", lua_isnil(L, 1));
        printf("is nil 2: %d\n", lua_isnil(L, 2));
        printf("is string 3: %d\n", lua_isstring(L, 3)); // number는 string으로 암시적 변환이 가능하다
        printf("is number -1: %d\n", lua_isnumber(L, -1)); // 수는 number로 변환 가능하다
    }

    /* lua_type */
    for (int i = 1; i <= 5; ++i) {
        printf("element %d: %s\n", i, lua_typename(L, lua_type(L, i)));
    }

    /* lua_to* */
    printf("toboolean 2: %d\n", lua_toboolean(L, 2));
    printf("tonumber 3: %g\n", lua_tonumber(L, 3));
    printf("tostring 4: %s\n", lua_tostring(L, 4));
    printf("strlen 4: %zu\n", lua_strlen(L, 4));

// others
    printf("gettop: %d\n", lua_gettop(L));

    printf("settop: -2\n");
    lua_settop(L, -2);
    print_stack(L);

    printf("pushvalue 3\n");
    lua_pushvalue(L, 3);
    print_stack(L);

    printf("remove 3\n");
    lua_remove(L, 3);
    print_stack(L);

    printf("insert 1\n");
    lua_insert(L, 1);
    print_stack(L);

    printf("replace 2\n");
    lua_replace(L, 2);
    print_stack(L);

// close state
    lua_close(L);
    return 0;
}

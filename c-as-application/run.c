#include <lua.h>
#include <lauxlib.h> // 이걸 include하지 않으면 seg fault를 경험할 수 있다
#include <stdio.h>

int main() {

    lua_State* L = lua_open();

    if (L == NULL) {
        fprintf(stderr, "%s\n", "Failed to create Lua state.");
        return 1;
    }

    printf("Lua state created: %p\n", (void*)L);

    lua_pushnil(L);
    puts("lua_pushnil executed successfully.");

    lua_close(L);
    puts("Lua state closed successfully.");

    return 0;
}

/*
 * 참고 https://www.lua.org/pil/28.html
 */

#include <lua.h>
#include <lauxlib.h>


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

typedef struct Matrix {
    int row, col;
    double arr[];
} Matrix;

static Matrix* checkmatrix(lua_State* L, int index) {
    void* ud = luaL_checkudata(L, index, "matrix");
    luaL_argcheck(L, ud != NULL, index, "`matrix` expected");
    return (Matrix*)ud;
}

static double* getelem(lua_State*L, Matrix* mat, int index_row, int index_col) {
    int row = luaL_checkint(L, index_row);
    int col = luaL_checkint(L, index_col);

    luaL_argcheck(L, row < mat->row, index_row, "index out of range");
    luaL_argcheck(L, col < mat->col, index_col, "index out of range");

    return &mat->arr[row * mat->col + col];
}

static int l_new(lua_State* L) {
    int row = luaL_checkint(L, 1);
    int col = luaL_checkint(L, 2);

    luaL_argcheck(L, row > 0, 1, "row <= 0");
    luaL_argcheck(L, col > 0, 2, "col <= 0");

    size_t nbytes = sizeof(Matrix) + row * col * sizeof(double);
    Matrix* mat = (Matrix*)lua_newuserdata(L, nbytes);

    luaL_getmetatable(L, "matrix");
    lua_setmetatable(L, -2);

    mat->row = row;
    mat->col = col;

    return 1;
}

static int l_from_table(lua_State* L) {
}

static int l_set(lua_State* L) {
    Matrix* mat = checkmatrix(L, 1);
    double v = luaL_checknumber(L, 4);
    *getelem(L, mat, 2, 3) = v;
    return 0;
}

static int l_get(lua_State* L) {
    Matrix* mat = checkmatrix(L, 1);
    lua_pushnumber(L, *getelem(L, mat, 2, 3));
    return 1;
}

static int l_row(lua_State* L) {
    Matrix* mat = checkmatrix(L, 1);
    lua_pushnumber(L, mat->row);
    return 1;
}

static int l_col(lua_State* L) {
    Matrix* mat = checkmatrix(L, 1);
    lua_pushnumber(L, mat->col);
    return 1;
}

static int l_tostring(lua_State* L) {
    Matrix* mat = checkmatrix(L, 1);

    luaL_Buffer b;
    luaL_buffinit(L, &b);

    luaL_addstring(&b, "{\n");
    for (int r = 0; r < mat->row; ++r) {
        luaL_addstring(&b, "  { ");
        for (int c = 0; c < mat->col; ++c) {
            lua_pushnumber(L, mat->arr[r * mat->col + c]);
            luaL_addvalue(&b);
            if (c + 1 != mat-> col) {
                luaL_addstring(&b, ", ");
            }
        }
        luaL_addstring(&b, " },\n");
    }
    luaL_addstring(&b, "}\n");

    luaL_pushresult(&b);
    return 1;
}

int luaopen_libmatrix(lua_State* L) {
    static const struct luaL_Reg matrix_funcs[] = {
        { "new", l_new },
        { NULL, NULL } // sentinel
    };

    static const struct luaL_Reg matrix_methods[] = {
        { "set", l_set },
        { "get", l_get },
        { "row", l_row },
        { "col", l_col },
        { "__tostring", l_tostring },
        { NULL, NULL} // sentinel
    };

    luaL_newmetatable(L, "matrix");
    luaL_register(L, NULL, matrix_methods);
    lua_setfield(L, -1, "__index");

    luaL_register(L, "matrix", matrix_funcs);
    return 1;
}

/***
Utility for generating UUIDs by wrapping libuuid's generate().

@license MIT
@module lua_uuid
*/
#include <lua.h>
#include <lauxlib.h>
#ifndef __MINGW32__
#include <uuid/uuid.h>
#else
#include <objbase.h>
#include <string.h>
#endif

/// Generate a UUID
// @return uuid_str
// @function generate()
static int generate(lua_State *L) {
#ifndef __MINGW32__
    uuid_t uuid;
    char uuid_str[37];

    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_str);

    lua_pushstring(L, uuid_str);
    return 1;
#else
    GUID guid;
    CoCreateGuid(&guid);
    char uuid_str[40];

    snprintf(uuid_str, 40,"%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    
    lua_pushstring(L, uuid_str);
    return 1;
#endif
}

int luaopen_lua_uuid(lua_State *L) {
    lua_pushcfunction(L, generate);
    return 1;
}

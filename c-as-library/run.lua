--[[
require "libnativefunc"
print(nativelib.mult50(50))
--]]
-------------------------------------------------------------------------
---[[
mylib = assert(package.loadlib("./libnativefunc.so", "luaopen_libnativefunc"))
t = mylib()
assert(t == nativelib)
print(nativelib.mult50(50))
--]]

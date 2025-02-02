require "libmatrix"

mat = matrix.new(3, 4)
print(("row: %d, col: %d"):format(mat:row(), mat:col()))
mat:set(0, 0, 3)
print(mat:get(0, 0))
print(mat)

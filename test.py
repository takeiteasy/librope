from pyrope import PyRope as Rope

rope = Rope("test")
string = str(rope)
print(string)
# > test
length = len(rope)
print(length)
# > 4
print(rope.insert(0, "test"))
# > True
print(rope)
# > testtest
rope.delete(0, 4)
print(rope)
# > test
del rope

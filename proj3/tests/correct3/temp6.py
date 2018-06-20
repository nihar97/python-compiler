r = [1]
print r
d = {1: r}
d[1][0] = 2
print r

def f(x::list of [int]): x[0] = 123
f(r)
print r

def g(x): x = [45]
f(r)
print r

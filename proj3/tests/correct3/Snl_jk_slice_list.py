
x = [1, 2, 3, 4, 5]

print x[:2]

print x[:]

x[:] = [20]

print x

x[:] = [1, 2, 3, 4, 5]

x[0:1] = [20, 30]

x[3:4] = [-1, -2, -3]

print x

print x[:-1]

x[:-1] = [3, 4, 5, 6]

print x

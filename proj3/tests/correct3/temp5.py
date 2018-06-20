x, y = [0, 0, 0], [0, 0, 0]
print x, y
i = 0
while i < len(x):
 x[i], y[i] = i, i + 1
 i = i + 1
print x, y

r, s = [1, 5], [2, 3]
print r, s
r[1:1], s[2:] = [2, 3, 4], [4, 5, 6, 7, 8]
print r, s

d = {1: '3', 4: '5'}
print d
d[1], d[7] = 'Nikhil', 'Athreya'
print d

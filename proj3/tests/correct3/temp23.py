L = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
print L
L[1:3], L[3:5] = L[5:7], L[7:9] = [13, 14, 15, 16], [17, 18, 19, 20]
print L

r = (1, 2)
x = y, z = r
print x, y, z, r

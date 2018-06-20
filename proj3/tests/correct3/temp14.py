def append(l::list of [$T], r):
 l[len(l):] = [r]

def assign(l, r):
 l = r

l::list of int = []
print l
append(l, 1)
print l
append(l, 2)
print l
assign(l, [3])
print l

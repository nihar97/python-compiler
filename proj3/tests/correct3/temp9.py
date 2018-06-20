class x:
 i = [1]
 def __init__(self, i): self.i = i

 def get(self): return self.i

t, s = x([1]), x([1])

print t.i
print s.i
t.get()[0] = 2
print t.i
print s.i

g = x.get
print g(s)

class m of [$T]:
 l::list of [$T] = []
 def __init__(self, e): self.l = [e]
 def get(self): return self.l
 def nest(self, e): return [self.l, [e]]

print '-----------------'
r = m of int(2)
print r.get()
print r.nest(3)

q = m of str('n')
for st in 'ikhil athreya':
 print q.nest(st)

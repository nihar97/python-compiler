def f(y):
 def g(x):
  return x + 5
 def h(x):
  return x + 7
 if y < 5:
  t = g
 else:
  t = h
 return t

a, b = f(3), f(6)

print(a(4))
print(b(7))

print(f(3)(4))
print(f(6)(7))

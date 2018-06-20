def f():
 x = 2
 def g():
  y = x, x
  def h():
   z = y, y
   return z
  return h
 x = 1
 return g	

print f()()()

def gen_counter(x::int):
 y = [0]
 def increment():
  __setitem__(y, 0, y[0] + x)
  return y[0]
 return increment

c1, c2 = r1, r2 = gen_counter(1), gen_counter(2)
print c1(), c2(), r1(), r2()
print 1 > 2 < 3
print 1 < 3
print 1 > 3
print 1 < 2 > 3 < 4
print 1 < 2 < 3 < 4 < 5 < 6 < 7 > 8 < 9 < 10
print 1 < 2 < 3 < 4
print 1 == 1 != 2 < 3

def incr(n):
 def p(k::int):
  return k + n
 v = [p, p]
 n = n + 1
 return v
w = incr(3)
print w[0](5)

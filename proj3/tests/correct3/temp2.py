a = 0 or 1
b = ' ' and '4s'
print a, b,

print '0' if False else 'Yes'

c = 2 and 5 or None
d = '3'
print c if True else toint(d)

print [1, 2, None]
#print { None: 'sdf', 5: 'sd', 6: None }

print (), (1,), (2, [3]), ({4: 5}, [6], ['4d', '6']), ('"',)

temp = (3, '3d')
x, y = r, s = temp
print x, r, y, s

def f(): return 2
g = f
h = g

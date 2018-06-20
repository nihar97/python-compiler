def id(x): return x

def pass_through(f, x): return f(x)

print pass_through(id, 23)
print pass_through(id, 'sdfsdf')

def fact(n):
	if n <= 0:
		return 1
	else:
		return n * fact(n - 1)

def fib(n):
	if n <= 0:
		return 0
	elif n == 1:
		return 1
	else:
		return fib(n - 1) + fib(n - 2)

def id(n): return n

math_funcs = [ ('fib', fib), ('id', id), ('fact', fact) ]

def apply(f, n): return f(n)

print(len(math_funcs))

def apply_all(n):
	for m, f in math_funcs:
		print m, ':', apply(f, n) 

apply_all(10)

d = {1: 2, 3: 4, 5: 6}

for f in d:
 print f

def f(x):
    def g():
        return x
    return g

x = "dynamic"
print f("lexical")()

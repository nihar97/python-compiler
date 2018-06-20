class Test of [$A, $B]:
 def __init__(self): pass

def func(x::Test of [int, str]): print 5
def func(x::Test of [str, int]): print 7

a = Test of [int,str]()
b = Test of [str,int]()

func(a)
func(b)

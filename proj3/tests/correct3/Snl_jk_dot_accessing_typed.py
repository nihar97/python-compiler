class TestClass:
    none :: int = None
    true::TestClass = None
    false = False

    def __init__(self):
        print 5
        self.true = self.get_self()

    def get_false(self,     a)::bool:
        return self.false

    def get_self(self)::TestClass:
        return self

    def get_true(self, abcdefghijklmnopqrstuvwxyz12345678991::int)::bool:
        print abcdefghijklmnopqrstuvwxyz12345678991
        return self.true.get_false('a')

# Yes, this is allowed: https://piazza.com/class/jciv781qjxs6f5?cid=131
t::TestClass = TestClass()
print t.get_false(7)
print t.get_self().get_self().get_false('"\'nothing"\'"')
print t.true.get_true(2)

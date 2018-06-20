class TestClass:
    true::TestClass = None
    false = False

    def __init__(self):
        print 5
        self.true = self.get_self()

    def get_false(self,     a):
        return self.false

    def get_self(self):
        return self

    def get_true(self, abcdefghijklmnopqrstuvwxyz12345678991):
        print abcdefghijklmnopqrstuvwxyz12345678991
        return self.true.get_false('a')

t = TestClass()
print t.get_false(7)
print t.get_self().get_self().get_false('"\'nothing"\'"')
print t.true.get_true(2)

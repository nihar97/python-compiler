class StringWrap:
 value = ''
 def __init__(self, x): self.value = x
 def setValue(self, x):
  self.value = x
  return self

a = StringWrap("a")
print a.value

a.setValue('a - updated')
print a.value

StringWrap.setValue(a, 'a - updated - static')
print a.value

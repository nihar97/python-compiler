def func():
    for i in []:
        print('should not print')
    else:
        print('should print')

func()
j = 0

while j > 10:
    print('nope')
else:
    print('yep')

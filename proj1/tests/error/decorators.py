def decorate(func):
    def func_return(name):
        return func(name)
    return func_return

@decorate
def print_name(name):
    return print(name)
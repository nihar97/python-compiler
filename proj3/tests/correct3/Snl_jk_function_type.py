def max(a::int, b::int)::int:
    if a > b:
        return a
    return b

fn::(int, int)->int = max

print(fn(1,2))

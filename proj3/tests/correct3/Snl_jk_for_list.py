nums:: list of [int] = [1, 2, 4, 8, 0, 16]

sum = 0

for n in nums:
    if n == 0:
        break
    sum = sum + n

print sum

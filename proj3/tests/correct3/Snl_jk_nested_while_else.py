i = 10

while i > 0:
	print(i)
	if i == 4:
		break
	i = i - 1

	j = 3
	while j > 0:
		print(j)
		if j == 2:
			break					# compare
		j = j - 1
	else:
		print("j loop broke")
else:
	print("i loop broke")

i = 10
while i > 0:
	print(i)
	if i == 4:
		break
	i = i - 1

	j = 3
	while j > 0:
		print(j)
		if j == 2:
			pass					# compare
		j = j - 1
	else:
		print("j loop broke")
else:
	print("i loop broke")


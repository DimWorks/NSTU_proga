from array import *

def reduction(text):
	print(text)
	# Добиваем строку, до кратности 8-ми
	while ((len(text) % 8) != 0):
		text += "#"
	
	output = ['\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0']
	length = len(text) // 8

	for i in range(0, 9):
		res = 0
		for j in range(0, (length * i)):
			res += ord(text[j]) * ord(text[j]) * j

		res %= 1000
		resulto = 0

		while (res > 0):
			resulto += res % 10
			res //= 10

		resulto += 60
		output[i - 1] = chr(resulto)

	#output[8] = '\0'
	return ''.join(output)


print(reduction("https://www.youtube.com/watch?v=GFq6wH5JRA2"))

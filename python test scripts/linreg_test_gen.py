from random import randint, uniform

x = []
y = []
dct_x = dict()

test_x = []

N = 3000000
NT = 100;
L1 = 2000000
L2 = 5000

for i in range(N):
	nr = randint(-L1, L1)
	while nr in dct_x:
		nr = randint(-L1, L1)
	x.append(nr)
	dct_x[nr] = 1
	
	nr = uniform(-L2, L2)
	y.append(nr)

for i in range(NT):
	nr = randint(-L1, L1)
	while nr in dct_x:
		nr = randint(-L1, L1)
	test_x.append(nr)
	dct_x[nr] = 1

for w in x:
	print(w, end=' ')
print()

for w in y:
	print(w, end=' ')
print()

for w in test_x:
	print(w, end=' ')

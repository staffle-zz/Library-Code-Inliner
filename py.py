n = int(input())
ans = 1
last = 1
gap = 2
for i in range(n//2):
	for j in range(4):
		last += gap
		ans += last
	gap += 2

print(ans)
import sys

def go(k, used):
	if(memo[k][used] >= 0):
		return memo[k][used]
	ret = T + 1
	if(used == (1 << k)):
		need = dist[n][k] + t[k]
		if(need <= d[k]):
			ret = need
	else:
		for i in range(0,n):
			if(i != k and ((1 << i) & used)):
				need = dist[i][k] + t[k] + go(i, used ^ (1 << k))
				if(need <= d[k] and need < ret):
					ret = need
	memo[k][used] = ret
	return ret
	
def comp(a, b):
	while(a&b):
		if((a^b)&1):
			if(a&1):
				return -1
			else:
				return 1
		a = a / 2
		b = b / 2
	if(a):
		return 1
	if(b):
		return -1
	return 0

n, T = raw_input().split()
n, T = int(n), int(T)

p=[]
t=[]
d=[]
for i in range(n):
	line = map(int, raw_input().split())
	p.append(line[0])
	t.append(line[1])
	if(line[2] < 0):
		d.append(T + 1)
	else:
		d.append(line[2])

dist=[]
for i in range(n+2):
	dist.append(map(int,raw_input().split()))

	
psum=[]
for i in range(0, 1 << n):
	x=0
	for j in range(0, n):
		if((1<<j)&i):
			x = x + p[j]
	psum.append(x)

memo=[[-1 for y in range(0, 1<<n)] for x in range(0, n)]

res = 0, 0
for i in range(0, 1 << n):
	for j in range(0, n):
		if((1<<j)&i):
			if (go(j, i) + dist[j][n + 1] <= T):
				if (psum[i] > res[0] or (psum[i] == res and comp(i, best) < 0)):
					res = psum[i], i

print res[0]
for i in range(0, n):
	if(((1<<i)&res[1])!=0):
		print i + 1,
print
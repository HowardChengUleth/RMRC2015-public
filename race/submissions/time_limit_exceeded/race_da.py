import sys
	
def smaller(a, b):
	while(a&b):
		if((a^b)&1):
			if(a&1):
				return True
			else:
				return False
		a = a / 2
		b = b / 2
	return b > 0

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

dp=[[(T+1) for y in range(n+2)] for x in range(1<<n)]
dp[0][n]=0
if(dist[n][n+1] <= T):
	dp[0][n+1]=dist[n][n+1]

for i in range(n):
	done=dp[0][n] + dist[n][i] + t[i]
	if(done <= d[i]):
		dp[1<<i][i] = done

for i in range(1, 1 << n):
	for j in range(n):
		if((1<<j)&i and dp[i][j] <= T):
			for k in range(n):
				if(((1<<k)&i)==0):
					done=dp[i][j] + dist[j][k] + t[k]
					if(done <= d[k] and done < dp[i|(1<<k)][k]):
						dp[i|(1<<k)][k] = done
			if(dp[i][j] + dist[j][n+1] < dp[i][n+1]):
				dp[i][n+1] = dp[i][j] + dist[j][n+1]						

res=0,0
for i in range(1<<n):
	if(dp[i][n+1]<=T):
		val=0
		for j in range(n):
			if((1<<j)&i):
				val = val + p[j]
		if(val > res[0] or (val == res[0] and smaller(i, res[1]))):
			res = val, i

print res[0]
for i in range(0, n):
	if(((1<<i)&res[1])!=0):
		print i + 1,
print

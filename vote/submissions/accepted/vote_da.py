import sys

nc=int(raw_input())
while(nc>0):
	nc=nc-1
	n=int(raw_input())
	votes=[]
	for i in range(1,n+1):
		votes.append((int(raw_input()),i))
	votes = sorted(votes,reverse=True)
	s=sum([v[0] for v in votes])
	if(2*votes[0][0] > s):
		print 'majority winner',votes[0][1]
	elif(votes[0][0] == votes[1][0]):
		print 'no winner'
	else:
		print 'minority winner',votes[0][1]

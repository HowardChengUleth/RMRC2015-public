import sys

nc = int(raw_input())
while(nc > 0):
	nc = nc - 1
	s = set()
	for i in range(int(raw_input())):
		s.add(raw_input())
	print len(s)
	
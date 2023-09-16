#!/usr/bin/python3
import sys

if len(sys.argv) < 3:
	print("Add files to check")
	exit(1)

verbose = False
if len(sys.argv) == 4 and sys.argv[3] == "-v":
	verbose = True

tot = 0
totdiff = 0
absdiff = 0
totval1 = 0
totval2 = 0
skips = 0
loss = 0
with open(sys.argv[1], 'r') as file1:
	with open(sys.argv[2], 'r') as file2:
		while True:
			l1 = file1.readline().rstrip('\n')
			l2 = file2.readline().rstrip('\n')
			if not l1 or not l2:
				break
			try:
				f1 = float(l1)
				f2 = float(l2)
				if f1 < 0.005 or f2 < 0.005:
					skips += 1
					continue
			except:
				skips = skips + 1
				continue
			tot += 1
			diff = f1 - f2
			totdiff += diff
			totval1 += f1
			totval2 += f2
			win = True
			if diff < 0:
				loss += 1
				win = False
			diff = abs(diff)
			absdiff = absdiff + diff
			diffsign = ' > ' if win else ' < '
			sdiff = f" ~{diff:.6f}"
			col="\033[31m" if win else "\033[36m"
			reset="\033[0;m"
			if verbose:
				print(f"{col}{l1}{diffsign}{l2}:{sdiff}{reset}")
print(f"{tot} benchs")
avgval1 = totval1 / tot
temp = avgval1
avgfps1 = 0
while temp < 1:
    temp += avgval1
    avgfps1 += 1
avgval2 = totval2 / tot
temp = avgval2
avgfps2 = 0
while temp < 1:
    temp += avgval2
    avgfps2 += 1
print(f"\033[36m name:{sys.argv[1]}	tot:{loss}	tot sec:{totval1:.6f}	avg sec: {avgval1:.6f}	avg fps: {avgfps1}")
print(f"\033[31m name:{sys.argv[2]}	tot:{tot - loss}	tot sec:{totval2:.6f}	avg sec: {totval2 / tot:.6f}	avg fps: {avgfps2}\033[0m")
print(f"abs difference (+):  {absdiff}")
print(f"tot difference (+-): {totdiff}")
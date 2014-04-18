import sys

n = 25
if len(sys.argv) > 1:
  n = int( sys.argv[1] )

for x in range(-n,n):
  for y in range(-n,n):
    if x != y:
      for k in range(1,n):
        print ((x**k - y**k)/(x - y))

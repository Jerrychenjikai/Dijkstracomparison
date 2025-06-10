import random

n=1000000
m=2000000
max_weight=10000

nodes=[]
connected=[]
sides=[]

for i in range(n):
    nodes.append(i+1)

root=random.randint(1,n)
connected.append(root)

for i in range(n):
    if i+1==root:
        continue
    start=connected[random.randint(0,len(connected)-1)]

    sides.append((start,i+1,random.randint(1,max_weight)))
    connected.append(i+1)

for i in range(m-n+1):
    sides.append((nodes[random.randint(0,len(nodes)-1)],nodes[random.randint(0,len(nodes)-1)],random.randint(1,max_weight)))

with open(str(n)+".in",'w') as fo:
    fo.write(f"{n} {m} {root}\n")
    for i in sides:
        fo.write(f"{i[0]} {i[1]} {i[2]}\n")
    fo.close()

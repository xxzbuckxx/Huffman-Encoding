
last = (0, 0);
interval = set();
test = {}
maxs = []
letters = ['A', 'B', 'C', 'D']
k = 0
output = open(r"/tmp/asin_diff_full.dat","w+");

for l in open("/tmp/asin.dat"):
    l = l.strip().split() 
    l = (float(l[0]), float(l[1]))
    if l[1] < last[1]:
        interval = last[0] -l[0]
        output.write(("%3.10f %3.20f\n" % (l[0], interval)))

    last = l




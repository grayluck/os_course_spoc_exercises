
pages = set();
lastHit = {};

fi = open('input.txt', 'r');
l = fi.readlines();
fi.close();

threshold = int(l[0]);
for i in l[1].split(' '):
	pages.add(int(i));
	lastHit[int(i)] = 0;

print pages;

now = last = hit = miss = 0;
for i in l[2].split(' '):
	now += 1;
	p = int(i);
	if p in pages:
		print "Page ", p, " : hit";
		hit += 1;
	else:
		print "Page ", p, " : miss";
		miss += 1;
		if now - last > threshold:
			for i in set(pages):
				if lastHit[i] < last:
					pages.remove(i);
		last = now;
	lastHit[p] = now;
	pages.add(p);
	print pages;
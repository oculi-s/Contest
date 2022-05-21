# https://programmers.co.kr/learn/courses/30/lessons/92341

def solution(f, records):
    t = [0] * 10000
    c = [0] * 10000
    for r in records:
        x, y, z = r.split()
        x = x.split(':')
        x = int(x[0])*60+int(x[1])
        y = int(y)
        z = z == 'OUT' or -1

        c[y] += z
        t[y] += x * z
    for i in range(10000):
        if c[i] == -1:
            t[i] += 23*60+59
    a = []
    for i in range(10000):
        if t[i]:
            v = f[1]
            if (t[i] > f[0]):
                v += (t[i] - f[0] + f[2] - 1) // f[2] * f[3]
            a.append(v)
    return a

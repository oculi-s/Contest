# https://programmers.co.kr/learn/courses/30/lessons/92342

def _s(x, y):
    a, b = 0, 0
    for i in range(11):
        if x[i] or y[i]:
            if x[i] < y[i]:
                b += 11-i-1
            else:
                a += 11-i-1
    return b - a

def solution(n, info):
    s = [[[0]*11, n, 0]]
    m = [[-1], 0, 0]
    for t, n, e in s:
        d = _s(info, t)
        if d > 0:
            if d > m[2]:
                tt = list(t)
                if n:
                    for i in range(10, e-1, -1):
                        if tt[i] == 0:
                            tt[i] = n
                            break
                m = [tt, e, d]
            elif d == m[2]:
                if m[1] < e:
                    m = [t, e, d]
                elif m[1] == e:
                    if m[0][e] < t[e]:
                        m = [t, e, d]
        if n:
            for i in range(e, 11):
                if n-info[i]-1 >= 0:
                    s.append([t[:i]+[info[i]+1]+t[i+1:], n-info[i]-1, i+1])
    return m[0]

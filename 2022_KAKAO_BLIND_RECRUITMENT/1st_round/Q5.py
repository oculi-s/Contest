# https://programmers.co.kr/learn/courses/30/lessons/92343

def solution(info, edges):
    info = [x == 0 or -1 for x in info]
    n = len(info)
    g = [[0 for _ in range(n)] for _ in range(n)]
    for x, y in edges:
        g[x][y], g[y][x] = 1, 1
    s = [[[0], 1]]
    m = 0
    for r, v in s:
        print(r, v)
        if v:
            for i in range(n):
                if g[r[-1]][i] and i not in r:
                    s.append([r+[i], v+info[i]])
            if not sum(g[r[-1]]):
                for i in range(n):
                    if g[r[-2]][i] and i not in r:
                        s.append([r+[i], v+info[i]])
        else:
            m = max(len(r), m)
    return m // 2
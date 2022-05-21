# https://programmers.co.kr/learn/courses/30/lessons/92345

def _move(b, y, x):
    tb = list(list(r) for r in b)
    tb[y][x] = 0
    return tb

def _r(b, y, x):
    return b[y+1][x]+b[y-1][x]+b[y][x+1]+b[y][x-1]

def solution(b, al, bl):
    b = [[0]*len(b[0])]+b+[[0]*len(b[0])]
    b = [[0]+r+[0] for r in b]
    s = [[b, al[0]+1, al[1]+1, bl[0]+1, bl[1]+1, 0, 0, 1]]
    c = [100, 100]
    for b, ay, ax, by, bx, p, q, d in s:
        if not _r(b, ay, ax):
            if p+q < c[0]:
                c[0] = p+q
        if not _r(b, by, bx):
            if p+q < c[1]:
                c[1] = p+q
        if d:
            b = _move(b, ay, ax)
            if b[ay-1][ax]:
                s.append([b, ay-1, ax, by, bx, p+1, q, 0])
            if b[ay+1][ax]:
                s.append([b, ay+1, ax, by, bx, p+1, q, 0])
            if b[ay][ax-1]:
                s.append([b, ay, ax-1, by, bx, p+1, q, 0])
            if b[ay][ax+1]:
                s.append([b, ay, ax+1, by, bx, p+1, q, 0])
        else:
            b = _move(b, by, bx)
            if b[by-1][bx]:
                s.append([b, ay, ax, by-1, bx, p, q+1, 1])
            if b[by+1][bx]:
                s.append([b, ay, ax, by+1, bx, p, q+1, 1])
            if b[by][bx-1]:
                s.append([b, ay, ax, by, bx-1, p, q+1, 1])
            if b[by][bx+1]:
                s.append([b, ay, ax, by, bx+1, p, q+1, 1])
    return min(c)

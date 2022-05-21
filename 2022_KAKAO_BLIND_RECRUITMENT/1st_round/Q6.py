# https://programmers.co.kr/learn/courses/30/lessons/92344

def solution(b, skill):
    for s in skill:
        s[5] *= s[0] == 2 or -1
    d = [dict() for _ in range(len(b))]
    for s in skill:
        p = (s[2], s[4])
        for y in range(s[1], s[3]+1):
            if p not in d[y]:
                d[y][p] = s[5]
            else:
                d[y][p] += s[5]
    for y in range(len(b)):
        for x in range(len(b[0])):
            for s in d[y]:
                if s[0] <= x and x <= s[1]:
                    b[y][x] += d[y][s]
    c = sum(sum(x>0 for x in y) for y in b)
    return c


# def sign(a):
#     return a>0

# def solution(b, skill):
#     for s in skill:
#         s[5] *= s[0] == 2 or -1
#     d = dict()
#     for s in skill:
#         p = (s[1], s[2], s[3], s[4])
#         if p not in d:
#             d[p] = s[5]
#         else:
#             d[p] += s[5]
#     a = [b]
#     m, n = len(b[0]), len(b)
#     z = [0]*m
#     for s in d:
#         a.append([z]*s[0]+[[0]*s[1]+[d[s]]*(s[3]-s[1]+1)+[0]*(m-s[3]-1)]*(s[2]-s[0]+1)+[z]*(n-s[2]-1))
#     s = 0
#     for x in zip(*a):
#         s += sum(map(sign, (map(sum, zip(*x)))))
#     return s

# B = [[100]*100]*100
# S = []
# for i in range(99):
#     for j in range(i, 99):
#         S.append([1, i, j, i+1, j+1, 1])
# print(solution(B,S))

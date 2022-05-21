# https://programmers.co.kr/learn/courses/30/lessons/92334

def solution(id_list, report, k):
    d = {x:set() for x in id_list}
    e = {x:set() for x in id_list}
    for r in report:
        x, y = r.split(' ')
        d[y].add(x), e[x].add(y)
    for x in d:
        if len(d[x]) >= k:
            d[x] = 1
        else:
            d[x] = 0
    for x in e:
        e[x] = sum(d[y] for y in e[x])
    return list(e.values())
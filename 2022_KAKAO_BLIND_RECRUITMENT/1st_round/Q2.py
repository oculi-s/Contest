# https://programmers.co.kr/learn/courses/30/lessons/92335

import math

def _b(n, k):
    r = ''
    while(n):
        r = str(n % k) + r
        n //= k
    return [int(x) for x in r.split('0') if x]

def _p(n):
    for i in range(2, int(math.sqrt(n))+1):
        if n % i == 0:
            return 0
    return 1

def solution(n, k):
    d = _b(n, k)
    return sum(_p(x) for x in d if x > 1)

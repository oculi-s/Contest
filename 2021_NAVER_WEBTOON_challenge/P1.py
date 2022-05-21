# from time import time

# from bisect import insort
# def solution(S, pattern):
#     P = sorted(pattern)
#     L = len(pattern)
#     T = sorted(S[:L])
#     a = P == T
#     for i in range(L,len(S)):
#         T.remove(S[i-L])
#         insort(T,S[i])
#         a += P == T
#     return int(a)

# N = 100
# s = time()
# for i in range(N):
#     solution("tegsornamwaresomran"*1000,"ransomee")
# print(time()-s)

# def solution(S, pattern):
#     T = [[0]*26 for _ in range(2)]
#     A = {x:i for i,x in enumerate("abcdefghijklmnopqrstuvwxyz")}
#     L = len(pattern)
#     for i in range(L):
#         T[0][A[S[i]]] += 1
#         T[1][A[pattern[i]]] += 1
#     a = T[0] == T[1]
#     for i in range(L,len(S)):
#         T[0][A[S[i-L]]] -= 1
#         T[0][A[S[i]]] += 1
#         a += T[0] == T[1]
#     return int(a)

# N = 100
# s = time()
# for i in range(N):
#     solution("tegsornamwaresomran"*1000,"ransomee")
# print(time()-s)

def solution(S, pattern):
    P, Q = [0]*26, [0]*26
    A = {x: i for i, x in enumerate("abcdefghijklmnopqrstuvwxyz")}
    L = len(pattern)
    for i in range(L):
        P[A[S[i]]] += 1
        Q[A[pattern[i]]] += 1
    a = P == Q
    for i in range(L, len(S)):
        P[A[S[i-L]]] -= 1
        P[A[S[i]]] += 1
        a += P == Q
    return int(a)

# N = 100
# s = time()
# for i in range(N):
#     solution("tegsornamwaresomran"*1000,"ransomee")
# print(time()-s)

# def solution(S, pattern):
#     P = sorted(pattern)
#     L = len(pattern)
#     a = 0
#     for i in range(len(S)):
#         if P == sorted(S[i:i+L]):
#             a += 1
#     return a

# s = time()
# for i in range(N):
#     solution("tegsornamwaresomran"*1000,"ransomee")
# print(time()-s)

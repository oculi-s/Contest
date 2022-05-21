def solution(letters, k):
    s = ''
    for k in reversed(range(k)):
        i = letters[k:].index(max(letters[k:]))
        s = letters[k+i]+s
        letters = letters[:k+i+1]
    return s

print(solution("zbjaj", 3))
# print(solution("abcdefghijklm", 3))
# print(solution("aaaaaaaa", 3))

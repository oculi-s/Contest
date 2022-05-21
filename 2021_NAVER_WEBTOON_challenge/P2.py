def solution(word):
    a = len(word)
    t = [625+125+25+5+1, 125+25+5+1, 25+5+1, 5+1, 1]
    for i in range(len(word)):
        a += "AEIOU".index(word[i])*t[i]
    return a

print(solution("AAAAE"))
print(solution("AAAE"))
print(solution("I"))
print(solution("EIO"))

# 5개 이내의 AEIOU로 이루어진 문자열 word가 있다
# word의 사전적 순서를 출력하는 함수를 작성하시오
# ex) solution(AAAAE) = 6 (A,AA,AAA,AAAA,AAAAA,AAAAE)
# ex) solution(AAAE) = 6 (A,AA,AAA,AAAA,AAAAA,AAAAE,AAAAI,AAAAO,AAAAU,AAAE)
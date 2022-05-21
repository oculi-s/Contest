#1
import requests
import random

class DD(dict):
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__

BASE, DATA = DD(), DD()

BASE.URL = 'https://huqeyhi95c.execute-api.ap-northeast-2.amazonaws.com/prod'
BASE.head = DD({'X-Auth-Token': 'abfb8c332a2c2eef8e7d07037775ddd5', 'Content-Type': 'application/json'})
BASE.param = {'problem': 2}

BASE.start = DD(requests.post(BASE.URL+'/start', headers=BASE.head, params=BASE.param).json())
BASE.head.Authorization = BASE.start.auth_key

#2
DATA.user = DD(requests.get(BASE.URL+'/user_info', headers=BASE.head).json())
N = len(DATA.user.user_info) + 1
waiting_from = [0] * N
grade = [0] * N
pairs = []
DATA.match = DD(requests.put(BASE.URL+'/match', headers=BASE.head, json=pairs).json())
htime, time = 0, 1

#3
stack = []
while 1:
    pairs = []
    DATA.waiting = DD(requests.get(BASE.URL+'/waiting_line', headers=BASE.head).json())
    for m in DATA.waiting.waiting_line:
        waiting_from[m['id']] = m['from']
    match = []
    for t in range(time, max(0, time-16), -1):
        for i in range(1, N):
            if waiting_from[i] == t:
                waiting_from[i] = 0
                if len(stack) == 2:
                    pairs.append(stack)
                    stack = [i]
                else:
                    stack.append(i)
    DATA.match = DD(requests.put(BASE.URL+'/match',headers=BASE.head, json={'pairs':pairs}).json())
    DATA.result = DD(requests.get(BASE.URL+'/game_result', headers=BASE.head).json())
    for r in DATA.result.game_result:
        e = random.randint(-5, 5)
        grade[r['win']] += ((40+e)-r['taken'])
    htime, time = time, DATA.match.time
    if htime == 594:
        rank = {i+1:v for i, v in enumerate(grade)}
        rank = sorted(rank.items(), key=lambda x:x[1], reverse=True)
        new_grade = []
        for i, v in enumerate(rank):
            new_grade += [{"id":v[0], "grade":i}]
        requests.put(BASE.URL+'/change_grade',headers=BASE.head,json={'commands':new_grade}).json()
    if htime == 595:
        break

#4
DATA.score = requests.get(BASE.URL+'/score', headers=BASE.head).json()
print(DATA.score)
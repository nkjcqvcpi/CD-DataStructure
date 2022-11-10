import os
from subprocess import Popen, PIPE, STDOUT


IN = 'highway/in'
judge = '/Users/houtonglei/OneDrive - stu.hqu.edu.cn/【4】数据结构/课设/2/cpp/highway'

result = {1: {}, 2: {}, 3: {}, 4: {}, 5: {}, 6: {}, 'sample':{}}
in_files = os.listdir(IN)
in_files.sort()

for i in in_files:
    try:
        result[int(i.split('-')[0])][i] = ''
    except ValueError:
        result['sample'][i] = ''


with open('result.txt', 'w') as fo:
    for sub in result.items():
        for data in sub[1].keys():
            with open(os.path.join(IN, data), 'r') as fi:
                inp = fi.readlines()
            command = ''
            p = Popen(judge, stdout=PIPE, stdin=PIPE, stderr=STDOUT)
            for i in inp:
                command += i
            output = p.communicate(input=command.encode())
            result[sub[0]][data] = output[0].decode().rstrip()
            fo.write(str(data) + ' ' + str(result[sub[0]][data]) + '\n')
            print(data, result[sub[0]][data])
            t = 0


P = {1: 5, 2: 7, 3: 6, 4: 33, 5: 18, 6: 31}

for i in result[1].values():
    if i.split(':')[0] == 'Accepted':
        P[1] = min(P[1], 5)
    else:
        P[1] = 0
        break

for i in result[2].values():
    status, score = i.split(': ')
    if status == 'Accepted' and int(score) <= 60:
        P[2] = 7
    else:
        P[2] = 0
        break

for i in result[3].values():
    status, score = i.split(': ')
    if status == 'Accepted' and int(score) <= 60:
        P[3] = 6
    else:
        P[3] = 0
        break

for i in result[4].values():
    status, score = i.split(': ')
    if status == 'Accepted' and int(score) <= 60:
        P[4] = 33
    else:
        P[4] = 0
        break

for i in result[5].values():
    status, score = i.split(': ')
    if status == 'Accepted' and int(score) <= 52:
        P[5] = 18
    else:
        P[5] = 0
        break

for i in result[6].values():
    status, score = i.split(': ')
    if status != 'Accepted' or int(score) >= 53:
        P[6] = 0
        break
    elif 51 <= int(score) <= 52:
        P[6] = min(P[6], 21)
    elif int(score) <= 50:
        P[6] = min(P[6], 31)

total_score = sum(P.values())

print(P)
print(total_score)

with open('score.txt', 'w') as fo:
    for i in P.items():
        fo.write(str(i[0]) + str(i[1]) + '\n')
    fo.write(str(total_score))

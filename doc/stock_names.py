import os

fn = open("./nasdaq.csv", "r")

cont = fn.readlines()
words = []

for ii in range(1, len(cont)):
    line = cont[ii]
    separatorInd = line.index(',') + 1
    name = line[separatorInd:]
    name = name.replace('"', '')
    name = name.replace('.', '')
    name = name.replace(',', '')
    name = name.replace("'", '')
    name = name.replace('\n', '')
    name = name.replace('\r', '')
    name = name.replace('\t', '')

    for word in name.split(' '):
        if word not in words:
            words.append(word)

print("{")
for word in words:
    print('\t"', end='')
    print(word, end='')
    print('",')

print("}")
print(len(words))

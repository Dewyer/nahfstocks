import os

fn = open("./firstNames.txt", "r")

cont = fn.readlines()
words = []

for ii in range(0, len(cont)):
    line = cont[ii]
    name = line
    name = name.replace('"', '')
    name = name.replace('.', '')
    name = name.replace(',', '')
    name = name.replace("'", '')
    name = name.replace('\n', '')
    name = name.replace('\r', '')
    name = name.replace('\t', '')

    words.append(name)

print("""#pragma once
#include "../../lib/string/String.h"
#include "../../lib/types.h"
constexpr usize FIRST_NAME_WORD_LIST_LENGTH = """+str(len(words))+";"
)
print(
"""
constexpr char first_name_word_list[COMPANY_NAME_WORD_LIST_LENGTH][80] = {
""")
for word in words:
    print('\t"', end='')
    print(word, end='')
    print('",')

print("};")

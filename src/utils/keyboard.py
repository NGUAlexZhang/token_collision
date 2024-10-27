import sys

keyboard_adjacency = {
    '1': ['2', 'q'],
    '2': ['1', '3', 'q', 'w'],
    '3': ['2', '4', 'w', 'e'],
    '4': ['3', '5', 'e', 'r'],
    '5': ['4', '6', 'r', 't'],
    '6': ['5', '7', 't', 'y'],
    '7': ['6', '8', 'y', 'u'],
    '8': ['7', '9', 'u', 'i'],
    '9': ['8', '0', 'i', 'o'],
    '0': ['9', 'o', 'p'],
    'q': ['1', '2', 'w', 'a'],
    'w': ['q', 'e', 's', 'a', '2', '3'],
    'e': ['w', 'r', 'd', 's', '3', '4'],
    'r': ['e', 't', 'f', 'd', '4', '5'],
    't': ['r', 'y', 'g', 'f', '5', '6'],
    'y': ['t', 'u', 'h', 'g', '6', '7'],
    'u': ['y', 'i', 'j', 'h', '7', '8'],
    'i': ['u', 'o', 'k', 'j', '8', '9'],
    'o': ['i', 'p', 'l', 'k', '9', '0'],
    'p': ['o', 'l', '0'],
    'a': ['q', 'w', 's', 'z'],
    's': ['a', 'w', 'e', 'd', 'x', 'z'],
    'd': ['s', 'e', 'r', 'f', 'c', 'x'],
    'f': ['d', 'r', 't', 'g', 'v', 'c'],
    'g': ['f', 't', 'y', 'h', 'b', 'v'],
    'h': ['g', 'y', 'u', 'j', 'n', 'b'],
    'j': ['h', 'u', 'i', 'k', 'm', 'n'],
    'k': ['j', 'i', 'o', 'l', 'm'],
    'l': ['k', 'o', 'p'],
    'z': ['a', 's', 'x'],
    'x': ['z', 's', 'd', 'c'],
    'c': ['x', 'd', 'f', 'v'],
    'v': ['c', 'f', 'g', 'b'],
    'b': ['v', 'g', 'h', 'n'],
    'n': ['b', 'h', 'j', 'm'],
    'm': ['n', 'j', 'k']
}

def getLenOfKA(idx, s):
    length = 1
    for i in range(idx + 1, len(s)):
        if s[i] in keyboard_adjacency.get(s[i - 1], []):
            length += 1
        else:
            break
    return length

def getKA(s): #KA is key adjacent
    s = s.lower()
    res = []
    i = 0
    while i < len(s) - 1:
        if not(s[i].isalpha() or s[i].isdigit()):
            i += 1
            continue
        length = getLenOfKA(i, s)
        if length >= 3:
            res.append(s[i : i + length])
        i += length
    return res

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Usage:python keyboard.py <filename> <frequency>")
        exit(1)    
    if not sys.argv[2].isdigit():
        print("the frequency must be a digit")
        exit(1)
    KACount = {}
    with open(sys.argv[1]) as file_handler:
        for line in file_handler:
            KAs = getKA(line) 
            for substr in KAs:
                if substr not in KACount.keys():
                    KACount[substr] = 0
                KACount[substr] += 1
    for key, value in KACount.items():
        if value >= int(sys.argv[2]):
            print("%s %d" % (key, value))
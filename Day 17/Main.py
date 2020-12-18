def readFile():
    f = open("data.txt")
    l = f.readlines()
    l = [i.strip() for i in l]

    active = {}

    for x in range(0, len(l[0])):
        for y in range(0, len(l)):
            active[(x, y, 0)] = l[x][y]

    return active

def part1():
    active = readFile()
    for i in range(6):
        active = nextGen(active)

    counter = 0
    for _, v in active.items():
        if v == '#':
            counter += 1

    print("Part 1 = ", counter)

def nextGen(active):
    newActive = {}
    #+2 since range is < MAX not <= MAX
    #generate ranges to check. since it cannot be no more than 1 away from the cube, just get the min and max of the active ones
    x1, x2 = (min([i[0] for i in active.keys()]) - 1), (max([i[0] for i in active.keys()]) + 2)
    y1, y2 = (min([i[1] for i in active.keys()]) - 1), (max([i[1] for i in active.keys()]) + 2)
    z1, z2 = (min([i[2] for i in active.keys()]) - 1), (max([i[2] for i in active.keys()]) + 2)

    for x in range(x1, x2):
        for y in range(y1, y2):
            for z in range(z1, z2):
                #do .get(...) since we can return a default value if it doesnt exist
                curr = active.get((x, y, z), '.')
                nC = neighbours(active, x, y, z)
                if (curr == '#' and nC in (2, 3)) or (curr == '.' and nC == 3):
                    newActive[(x, y, z)] = '#'

    return newActive

def neighbours(active, x, y, z):
    counter = 0
    for dx in (-1, 0, 1):
        for dy in (-1, 0, 1):
            for dz in (-1, 0, 1):
                #dx == dy == dx == 0: originally, caused big errors
                if dx == dy == dz == 0:
                    continue
                else:
                    c = active.get((x + dx, y + dy, z + dz), '.') 
                    if c == '#':
                        counter += 1
    return counter

def readFile2():
    f = open("data.txt")
    l = f.readlines()
    l = [i.strip() for i in l]

    active = {}

    for x in range(0, len(l[0])):
        for y in range(0, len(l)):
            active[(x, y, 0, 0)] = l[x][y]

    return active

def part2():
    active = readFile2()

    for i in range(6):
        active = nextGen2(active)

    counter = 0
    for _, v in active.items():
        if v == '#':
            counter += 1

    print("Part 2 = ", counter)

def nextGen2(active):
    newActive = {}
    #+2 since range is < MAX not <= MAX
    #generate ranges to check. since it cannot be no more than 1 away from the cube, just get the min and max of the active ones
    x1, x2 = (min([i[0] for i in active.keys()]) - 1), (max([i[0] for i in active.keys()]) + 2)
    y1, y2 = (min([i[1] for i in active.keys()]) - 1), (max([i[1] for i in active.keys()]) + 2)
    z1, z2 = (min([i[2] for i in active.keys()]) - 1), (max([i[2] for i in active.keys()]) + 2)
    w1, w2 = (min([i[3] for i in active.keys()]) - 1), (max([i[3] for i in active.keys()]) + 2)

    for x in range(x1, x2):
        for y in range(y1, y2):
            for z in range(z1, z2):
                for w in range(w1, w2):
                    #do .get(...) since we can return a default value if it doesnt exist
                    curr = active.get((x, y, z, w), '.')
                    nC = neighbours2(active, x, y, z, w)
                    if (curr == '#' and nC in (2, 3)) or (curr == '.' and nC == 3):
                        newActive[(x, y, z, w)] = '#'

    return newActive

def neighbours2(active, x, y, z, w):
    counter = 0
    for dx in (-1, 0, 1):
        for dy in (-1, 0, 1):
            for dz in (-1, 0, 1):
                for dw in (-1, 0, 1):
                    if dx == dy == dz == dw == 0:
                        continue
                    else:
                        c = active.get((x + dx, y + dy, z + dz, w + dw), '.') 
                        if c == '#':
                            counter += 1
    return counter

part1()
part2()

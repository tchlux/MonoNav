def equals(s1, s2):
    i = s2.index(".")
    if len(s2[:i])%2 == 1:
        s1 = s1[:i//2+1]+s1[:i//2+1]
    else:
        s1 = s1[:i//2]+s1[:i//2]
    s2 = s2[:i]
    print("String 1:", s1)
    print("String 2:", s2)
    print()
    return s1 == s2

i = 316.3
done = False
while not equals(str(i),str(i*2)):
    i += .1




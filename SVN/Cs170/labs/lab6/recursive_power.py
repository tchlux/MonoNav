
def power_recursive(base, exponent):
    assert(exponent>0)
    if exponent == 1:
        return base
    else:
        return base * power_recursive(base,exponent-1)


if __name__ == "__main__":
    b = int(input("An integer greater than 0: "))
    e = int(input("An exponent to raise that integer to: "))
    print(power_recursive(b,e))

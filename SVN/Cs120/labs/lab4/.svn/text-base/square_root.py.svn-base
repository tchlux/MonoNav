# THIS COMPUTES the babylonian squrt
# pre : itenger and dtiigs msut be psotovie itengres
# psot : sarque root
def compute_square_root(integer, digits):
    s = 4 * (10 ** ((digits-1) / 2))
    for i in range(10 ** 6):
        s_prime = (1 / 2) * (s + (integer / s))
        s = s_prime
    return s_prime

print(compute_square_root(2345, 4))
print("GAME OVER. ROVER.")

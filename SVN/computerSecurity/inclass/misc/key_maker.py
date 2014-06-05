def make_key(encrypted, decrypted):
    key = ""
    for i in range(len(encrypted)):
        shift = (ord(encrypted[i]) - ord(decrypted[i]))%26
        print("Shift produced: ",shift)
        key += chr(shift+ord("a"))
    return key


if __name__ == "__main__":
    print(make_key(input("Encrypted: "), input("Decrypted: ")))

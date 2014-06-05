KEY = 1
RANGE = [0,255]
MOD = RANGE[1] - RANGE[0] + 1
COMPLEX_KEY = [ord(char) for char in "hello"]
# COMPLEX_KEY = [3]

#Function:Rotates a character by a key
#Pre:     Character is given
#Post:    The rotated character is returned
def rotate(char, key):
    ord_value = ord(char) - RANGE[0]
    rotated = (ord_value+key)%MOD + RANGE[0]
    return chr(rotated)

#Function:Encrypts a given string
#Pre:     String given
#Post:    The encrypted string is returned
def encrypt_message(string, key_list=COMPLEX_KEY):
    encrypted = ''
    for i,char in enumerate(string):
        key = key_list[i%len(key_list)]
        encrypted += rotate(char, key)
    return encrypted

#Function:Decrypts a given string
#Pre:     String given
#Post:    The decrypted string is returned
def decrypt_message(string, key_list=COMPLEX_KEY):
    decrypted = ''
    for i,char in enumerate(string):
        key = -key_list[i%len(key_list)]
        decrypted += rotate(char, key)
    return decrypted

#Function:This function
#Pre:     
#Post:    
def find_patterns(cipher, size):
    possible_solutions = {}
    spacing_counts = []
    start = 0
    end = start+size
    while end <= len(cipher):
        current = cipher[start:end]
        if current in possible_solutions.keys():
            spacing_counts.append(start-possible_solutions[current])
        possible_solutions[current] = start
        start += 1
        end += 1
    return spacing_counts


#This tests the encryption function
if __name__ == "__main__":
    response = ""
    key = [KEY]#[ord(char)-ord('a')+1 for char in input("Key? ")]
    while response != "quit":
        response = input("Encrypt it: ")
        print("The encrypted version:")
        print(encrypt_message(response, key))

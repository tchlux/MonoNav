import os
import sys
import random

S0 = [[1,0,3,2],[3,2,1,0],[0,2,1,3],[3,1,3,2]]
S1 = [[0,1,2,3],[2,0,1,3],[3,0,1,0],[2,1,0,3]]

#Pre:  Four bit string
#Post: Results of P4 swap
def P4(fb):
    return fb[1]+fb[3]+fb[2]+fb[0]

#Pre:  10 bits in a string
#Post: Results of the p8 swap
def P8(tb):
    return tb[5]+tb[2]+tb[6]+tb[3]+tb[7]+tb[4]+tb[9]+tb[8]

#Pre:  10 bits as a string
#Post: Results of the p10 swap
def P10(tb):
    return tb[2]+tb[4]+tb[1]+tb[6]+tb[3]+tb[9]+tb[0]+tb[8]+tb[7]+tb[5]

#Pre:  One byte as a string
#Post: The newly rearranged byte is returned split into left and right
def IP(byte):
    return byte[1]+byte[5]+byte[2]+byte[0], byte[3]+byte[7]+byte[4]+byte[6]

#Pre:  One byte is given that consists of 8 bits as a string
#Post: The byte that was sent through the inverse perm is returned
def IIP(byte):
    return byte[3]+byte[0]+byte[2]+byte[4], byte[6]+byte[1]+byte[7]+byte[5]

#Pre:  left & right are strings, shift is an integer
#Post: The strings are both shifted the given amount cyclically,
#      negative numbers result in left shifts, positive right
def cyclic_shift(left, right, shift):
    new_left = left[-shift:] + left[:-shift]
    new_right = right[-shift:] + right[:-shift]
    return new_left, new_right

#Pre:  A 10 bit binary string
#Post: The two 8 bit binary keys as strings
def generate_two_keys(ten_bit_key):
    key = P10(ten_bit_key)
    l1, r1 = key[:5], key[5:] #5 is half of 10
    l1, r1 = cyclic_shift(l1, r1, -1) #-1 is amount being shifted
                                      # (- for left)
    l2, r2 = cyclic_shift(l1, r1, -2) #-2 is amount being shifted
                                      # (- for left)
    return P8(l1+r1), P8(l2+r2) #return the reassembled halves after
                                #being run through Permutation 8

#Pre:  four_bit sequence as string
#Post: 8 bit sequence produced by given function
def expand_four(fb):
    return fb[3]+fb[0]+fb[1]+fb[2]+fb[1]+fb[2]+fb[3]+fb[0]

#Pre:  Four binary bits are given in a string
#Post: RV: The integer version of the swapped bits
def get_row_col(fourbits):
    row = int(fourbits[0] + fourbits[3], 2)
    col = int(fourbits[1] + fourbits[2], 2)
    return row, col

#Pre:  Four bits as string, and an 8 bit key
#Post: Four bits that result from the mapping
def map_bits(four_bit, key):
    new_8 = expand_four(four_bit)
    final_8 = xor(new_8, key)
    r1, c1 = get_row_col(final_8[:4])
    r2, c2 = get_row_col(final_8[4:])
    left = num_to_byte(S0[r1][c1], 2)
    right = num_to_byte(S1[r2][c2], 2)
    return P4(left+right)

#Pre:  Two binary representations of integers as strings
#Post: new binary representation exor'd
def xor(n1,n2):
    final = ""
    for i in range(len(n1)):
        if n1[i] == n2[i]:
            final += "0"
        elif n1[i] == "1" or n2[i] == "1":
            final += "1"
        else:
            final += "0"
    return final

#Pre:  The left and right four bits of a byte are given along with a
#      key, data (a list for storing pieces of information)
#Post: The new 4 bits produced by the given key and mapping
def xor_map(left_four, right_four, key, data):
    mapped_right = map_bits(right_four, key)
    data.append(["F(right_four, key):", mapped_right])
    return xor(left_four, mapped_right)

#Pre:  A byte is given as a string of 8 0's and 1's
#      data (a list for storing pieces of information)
#Post: The encrypted form of the byte is returned
def encrypt_it(byte, key0, key1, data):
    l1, r1 = IP(byte) #do initial perm
    data.append(["Left and Right after IP:", l1, r1])
    r2, l2 = xor_map(l1, r1, key0, data), r1 #generate encrypted left,
                                       #normal right and swap
    data.append(["L, R after first run & swap:", r2, l2])
    l3, r3 = xor_map(l2, r2, key1, data), r2 #generate encrypted left,
                                       #normal right
    data.append(["L, R after second run:", r2, l2])
    l_final, r_final = IIP(l3+r3) #do final perm on full byte
    data.append(["Left and Right after IIP:", l_final, r_final])
    return l_final+r_final

#Pre:  A byte is given as a string of 8 0's and 1's
#      data (a list for storing pieces of information)
#Post: The decrypted form of the byte is returned
def decrypt_it(byte, key0, key1, data):
    l1, r1 = IP(byte) #do initial perm inversed
    data.append(["Left and Right after IP:", l1, r1])
    r2, l2 = xor_map(l1, r1, key1, data), r1 #generate encrypted left,
                                       #normal right and swap
    data.append(["L, R after first run & swap;", r2, l2])
    l3, r3 = xor_map(l2, r2, key0, data), r2 #generate encrypted left,
                                       #normal right
    data.append(["L, R after second run:", r2, l2])
    l_final, r_final = IIP(l3+r3) #do final perm regular
    data.append(["Left and Right after IIP:", l_final, r_final])
    return l_final+r_final

#Pre:  An integer is given
#Post: The binary form of the integer is returned in a string
def num_to_byte(num, size=8):
    binary = ""
    while num != 0:
        binary = str(num%2) + binary
        num = num // 2
    while len(binary) < size:
        binary = "0" + binary
    return binary

#Pre:  A string is given at input prompt
#      data (a list for storing pieces of information)
#Post: The encrypted version of the string is returned as the
#      encrypted ascii characters
def DES_encrypt(ten_bit, string, data):
    key0,key1 = generate_two_keys(ten_bit) #generate the two keys
    encrypted_string = "" #initialize the final encrypted string
    for char in string:
        byte = num_to_byte(ord(char)) #get the string of the binary
        data.append(["Encrypt Byte:", byte])
        encrypted_byte = int(encrypt_it(byte, key0, key1, data),2)
               #enctrypt the byte, then turn it back into an integer
        encrypted_string += chr(encrypted_byte)
               #add to current encrypted message
    return encrypted_string

#Pre:  An encrypted string, two keys to use for decrypting the message
#      data (a list for storing pieces of information)
#Post: The string is decrypted and returned
def DES_decrypt(ten_bit, encrypted_message, data):
    key0,key1 = generate_two_keys(ten_bit) #generate the two keys
    decrypted_string = ""
    for char in encrypted_message:
        byte = num_to_byte(ord(char))
        data.append(["Decrypt Byte:", byte])
        decrypted_byte = int(decrypt_it(byte, key0, key1, data),2)
        decrypted_string += chr(decrypted_byte)
    return decrypted_string

#Pre:  data (a list for storing pieces of information)
#Post: A string of ascii characters and 10 0's and 1's in another string
def get_input(data):
    ten_bit = ""
    if len(sys.argv) > 1: #if there is a second CLA (command line argument)
        string, ten_bit = command_line()
    else: #No command line args
        string = input("Tell me and I will encrypt: ")
    if ten_bit == "": #The ten bit was not 
        ten_bit = input("10 Bit binary key? (only 1's and 0's please) ")
    ## ^^ retrieve user input
    for char in ten_bit:
        if char != "0" and char != "1": #check ten_bit key
            raise(Exception("The ten bit key can only contain 0's and 1's"))
    if string == "": #if no user input
        print("\nNo string given.  Message being randomly generated")
        for i in range(random.randint(10,100)):
            string += chr(random.randint(48,122))
    if ten_bit == "": #if no user input
        print("No key given, Key being randomly generated\n")
        for i in range(10):
            ten_bit += str(random.randint(0,1))
    data.append(["String:", string])
    data.append(["10 bit key:", ten_bit])
    return string, ten_bit

#Pre:  Command line arguments were given
#Post: The arguments are used as input output files
def command_line():
    string = ""
    input_file = sys.argv[1] #get input file
    if os.path.exists(input_file): #if path exists
        with open(input_file) as f:
            string = f.read() #read in the file
            f.close()
    else:
        raise(Exception("The input filename given does not exist."))
    if len(sys.argv) > 3: #if a third CLA was given
        ten_bit = sys.argv[3]
    else: #if not, ask user for key
        ten_bit = ""
    return string, ten_bit

#Pre:  File executed directly
#Post: Program runs
if __name__ == "__main__":
    print("If you would rather not give responses just press enter.")
    data = []
    string, ten_bit = get_input(data)
    print("String is: \n",string, "\n")
    print("Key is: ",ten_bit, "\n")
    encrypted = DES_encrypt(ten_bit, string, data)
    print("\nEncrypted message: \n\n", encrypted, "\n")
    string = DES_decrypt(ten_bit, encrypted, data)
    print("Decrypted message: \n\n", string, "\n")
    if len(sys.argv) > 2: #if output file was given
        f = open(sys.argv[2], "w")
        f.write(encrypted)
        f.write("\n\n")
        f.write(string)
        f.close()
    if len(string) == 1: #print data if only one character was given
        print("Data from the trip:")
        for item in data: 
            for piece in item: print(piece, end=" ")
            print()
#    command_line = sys.argv
 

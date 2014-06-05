ord_value_A = ord("A")
ord_value_Z = ord("Z")
new_ord_value_A = ord_value_A - ord_value_A + 1
new_ord_value_Z = ord_value_Z - ord_value_A + 1



def rotate_thirteen(text):
    number_in_string = len(text)
    string = ''
    for i in range (0, number_in_string):
        char = text[i]
        character = ord(char)
        character = character + 13
        temp_char = chr(character)
        string = string + temp_char
    return string


def rotate_thirteen_back(text):
    number_in_string = len(text)
    string = ''
    for i in range (0, number_in_string):
        char = text[i]
        character = ord(char)
        character = character - 13
        temp_char = chr(character)
        string = string + temp_char
    return string


print(rotate_thirteen(input("some form of text brah: ")))
print((rotate_thirteen_back(input("some form of text gurr: "))))
print(' turn it out!!! ! ! ! ! !  !  !  !   !   !    !    !     !')

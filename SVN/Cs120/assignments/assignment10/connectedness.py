import os
import friend_circle

#this function turns the name list into a two dimensional list of names
#pre: a one dimensional list of strings
#post: a two dimensional list of strings with thier pairs (friends)
def create_list_of_lists_with_strings(ugly_list):
        names_list = []
        for i in range(len(ugly_list)):
            if ugly_list[i] == "":
                break
            temp_list = []
            string = ''
            string = ugly_list[i]
            temp_list = string.split(',')
            names_list.append(temp_list)
            temp_list = []
        return names_list

#this function returns the a_file as it was last saved
#pre: nothing needs to go into this function
#post: returns the a_file
def return_a_file(a_file):
    if os.path.exists(a_file):
        a_file = open(a_file, 'r')
        names = a_file.read()
        a_file.close()
        ugly_list = names.split('\n')
        names_list = create_list_of_lists_with_strings(ugly_list)
    else:
        print('file not found, names_list will contain None')
    return names_list

#this function returns the location of a value in a 2 dimensional list
#pre: the value to find and the 2 dimensional list
#post: the index location in the big list of the list with the value in it
def find_value_in_list_of_lists(value, big_list):
    big_length = len(big_list)
    for i in range(big_length):
        if value in big_list[i]:
            return i
#this function finds all strings associated(friends) with a 'user' string and returns a single list of the users friends
#pre: the two dimensional list of all names
#post: a one dimensional list of strings(names) associated(friends) with the user
def create_friends_list_for_user(user, name_list):
    user_friends_list = []
    for lst in name_list:
        if user in lst:
            index = lst.index(user)
            person = lst[1 - index]
            user_friends_list.append(person)
    return user_friends_list

#this function cycles every friend in the user's friend list and checks to see if they have any friends in the user's friend list
#pre: the full list of names and connections, the user's friend list, the user
#post: a list of friends that are friends with the user but none of the user's other friends
def calc_conect_score(name_list, user_friends_list, user):
    mutual_friends_list = []
    for friend in user_friends_list:
        for tup in name_list:
            if friend in tup:
                index = (1-tup.index(friend))
                if tup[index] in user_friends_list:
                    mutual_friends_list.append(tup[0])
                    mutual_friends_list.append(tup[1])
    exclusive_friends = []
    for friend in user_friends_list:
        if friend not in mutual_friends_list:
            exclusive_friends.append(friend)
    return (exclusive_friends, mutual_friends_list)

#this function finds a connectivity score for a specified user, then draws a circle with the friends around the border and draws lines connecting every two strings that are related
#pre: nothing, inputs shouls be accurate
#post: a connectedness score for a user, and a circle drawn on the turtle graphics window
def connectedness_main():
    a_file = input('A file name that contains a list \nDefault is friends.txt:  ')
    user = ('"'+input("The user name: ")+'"')
    name_list = return_a_file(a_file)
#    name_list = [['"a"','"b"'],['"a"','"c"'],['"a"','"d"'],['"a"','"e"'],['"a"','"f"'],['"b"','"c"'],['"b"','"e"'],['"d"','"f"'],['"d"','"g"'],['"d"','"h"']]
    user_friends_list = create_friends_list_for_user(user, name_list)
    print('number of friends for user', len(user_friends_list))
    (exclusive_friends, mutual_friends_list) = calc_conect_score(name_list, user_friends_list, user)
    print('connect score for',user,'is: ',len(exclusive_friends))
    print('The super individual people the user is friends with are:\n', exclusive_friends)
    circle = friend_circle.Friend_circle()
    circle.draw_friend_circle(user_friends_list, name_list)
    

connectedness_main()






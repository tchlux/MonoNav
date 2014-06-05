

#this function takes the first two lines of input and builds lists without punctuation or capitalization
#pre: the function will work with any input, as long as you want it to match
#post:  two lists, each containing all the words, excluding punctuation, in a line
def two_strings_to_lists():
    first_person_string = input()
    second_person_string = input()
    first_person_string = rebuild_string_without_unwanted_characters(first_person_string)
    second_person_string = rebuild_string_without_unwanted_characters(second_person_string)
    first_person_string = first_person_string.lower()
    second_person_string = second_person_string.lower()
    first_list = first_person_string.split(" ")
    second_list = second_person_string.split(" ")
    return (first_list, second_list)


#this function rebuilds an input string without punctuation and leaves spaces between words
#pre: this function will remove all non alpha characters except spaces
#post: the input string with only alpha characters and spaces seperating words
def rebuild_string_without_unwanted_characters(string):
    new_string = ""
    for i in range(len(string)):
        if string[i].isalpha() or string[i] == " ":
            new_string += string[i]
    return new_string


#this function makes a dictionary of all words that exist between two lists
#pre: this function requires two lists containing values
#post: this function creates one dictionary with a list of keys, one for each word existing in the lists and the value associated with it is the number of occurances of that word(key)
def for_loop_dictionary_maker(first_list, second_list):
    length_of_list_one = len(first_list)
    length_of_list_two = len(second_list)
    dictionary_of_words = {}
    for i in range(length_of_list_one):
        key = first_list[i]
        if key in dictionary_of_words:
            dictionary_of_words[key] += 1
        else:
            dictionary_of_words[key] = 1
    for i in range(length_of_list_two):
        key = second_list[i]
        if key in dictionary_of_words:
            dictionary_of_words[key] += 1
        else:
            dictionary_of_words[key] = 1
    return (dictionary_of_words)


#this function creates dictionaries of words that do not exist in one list (finds unique words)
#pre: there is no input for this function, it relies entirely on other functions return
#post: this function prints the unique words for each line and the number of occurances
def sentence_compare():
    gangsta_dictionary = {"homie":0 , "stackin":0 , "bling":0 , "ridin":0 , "busted":0 , "hustlin":0 , "rolled":0 , "roll":0 , "trippin":0 , "holla":0 , "peace":0 , "chains":0 , "yo":0 , "dolla":0 , "bill":0 , "yall":0 , "popo":0 }
    business_man = {"intermediate":0 , "populous":0 , "submitted":0 , "hello":0 , "goals":0 , "surplus":0 , "understand":0 , "pr":0 , "criminal":0 , "police":0 , "profit":0 , "gain":0 , "department":0 , "chair":0 , "balance":0}
    (first_list, second_list) = two_strings_to_lists()
    (dictionary_of_words) = for_loop_dictionary_maker(first_list, second_list)
    dictionary_not_two = {}
    dictionary_not_one = {}
    for key in dictionary_of_words:
        if key in second_list:
            pass
        else:
            dictionary_not_two[key] = dictionary_of_words[key]
    for key in dictionary_of_words:
        if key in first_list:
            pass
        else:
            dictionary_not_one[key] = dictionary_of_words[key]
    list_of_order_first = find_max_and_order(dictionary_not_two)
    list_of_order_second = find_max_and_order(dictionary_not_one)
    first_category = determine_category(gangsta_dictionary, business_man, list_of_order_first)
    second_category = determine_category(gangsta_dictionary, business_man, list_of_order_second)
    print('')
    print('Words in one but not in two.', list_of_order_first)
    print('Words in two but not in one.', list_of_order_second)
    print('')
    print('The category of the first line is..', first_category)
    print('The category of the second line is..', second_category)
    print('')
#this function takes a dictionary and returns it as a list with the keys in order from most occurances to least occurances, the number remains one place to the right of the "key"
#pre: this function takes a dictionary full of keys(strings) and values(ints)
#post: a list of the same dictionary in order from most occurances to least with words(keys) to the left of their values(occurances/ints)
def find_max_and_order(dictionary_with_number):
    list_of_items = list(dictionary_with_number.items())
    list_of_values_unsorted = list(dictionary_with_number.values())
    list_of_order = []
    for i in range (len(list_of_values_unsorted)):
        max_value = max(list_of_values_unsorted)
        max_location = list_of_values_unsorted.index(max_value)
        list_of_order.append(list_of_items[max_location][0])
        list_of_order.append(max_value)
        del list_of_values_unsorted[max_location]
        del list_of_items[max_location]
    return(list_of_order)


#this function determines which of two categories an input line falls into gangsta or business man
#pre: the input to this function must be two dictionaries and one list of words
#post: a statement of which type of person is speaking based off of the list provided
def determine_category(gangsta, business, list_order):
    gangsta_count = 0
    business_count = 0
    for item in list_order:
         if item in gangsta:
             gangsta_count += 1
         elif item in business:
             business_count += 1
    if business_count > gangsta_count:
        returner = 'Business man speaking'
    elif gangsta_count > business_count:
        returner = 'Gangsta in da house'
    else:
        returner = "I'm sorry, it is too close to tell."
    return returner


sentence_compare()

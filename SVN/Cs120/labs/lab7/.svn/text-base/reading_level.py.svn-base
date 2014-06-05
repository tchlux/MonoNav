# squidwarrddd!


# this function determines the number of sentences in the sentence
# pre: the whole sentence as a string
# post: the number of sentences
def number_of_sentences(whole_sentence):
    number_of_periods = 0
    for char in whole_sentence:
        if char == ".":
            number_of_periods += 1
    return number_of_periods

# this function determines the number of words in the sentence
# pre: the whole sentence as a string
# post: the number of words
def number_of_words(whole_sentence):
    number_of_spaces = 0
    for char in whole_sentence:
        if char == " ":
            number_of_spaces += 1
    number_of_words = number_of_spaces + 1
    return number_of_words


# this function determines the number of letters in the sentence
# pre: the whole sentence as a string
# post: the number of letters
def number_of_letters(whole_sentence):
    number_of_letters = 0
    for char in whole_sentence:
        if char != " " and char != "." and char != ",":
            number_of_letters += 1
    return number_of_letters


# this function does the business stuff, it earns its way through life
# pre: nada bro
# post: the grade level, and the number of each variable
def fresch_and_kinki():
    whole_sentence = input("Write a sentence please ")
    sentence = number_of_sentences(whole_sentence)
    word = number_of_words(whole_sentence)
    letter = number_of_letters(whole_sentence)
    print("number of sentences, words, letters: ", sentence,",",word,",",letter)
    grade_level = (0.39 * (word / sentence) + 11.8 * ((letter / 3) / word) - 15.59)
    print("grade level = ", grade_level)

fresch_and_kinki()

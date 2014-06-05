import random

# for this definition
##  t = try again response
##  c = chapter selection
# for this function the final statement is displayed, options for try again 
# or no are provided

def else_end_statement():
    print('')
    print(' Well that concludes our session if Im not mistaken!')
    print('  Type "yes" if you want another run!')
    print('')
    t = input('Try again?? ')
    if t == 'yes':
        opening_choice_options()
    else:
        print("Good Bye!")
    exit

# for this function
## d = given meaning or definition
# this function is what compares the imput word to the actual word and definition, it
# passes whether or not it was correct

def vocab_word_and_meaning_enter_english(word,meaning):
    print('')
    d = input(word + '.. como se dice en ingles? ')
    print('')
    if meaning == d:
        print('Correcto!  Estas incredible! Bueno trabajo ')
    else:
        print('Weeelll...')
        print("You were close.")
    print('')
    print('       ', word, 'es', meaning, 'en ingles')
    print('')

def vocab_word_and_meaning_enter_spanish(meaning,word):
    print('')
    d = input(word + '.. como se dice en espanol? ')
    print('')
    if meaning == d:
        print('Correcto!  Estas incredible! Bueno trabajo ')
    else:
        print('Weeelll...')
        print("But that's okay!  You were close.")
    print('')
    print('       ', word, 'es', meaning, 'en espanol')
    print('')



#this function provides the initial welcome and has the if statements that send it to the
#  corresponding chapters
def opening_choice_options():
    for i in range (40):
        print('')
    print(" Welcome to Thomas' own Spanish 150 help tutorial!")
    print('      my goal here is to help you learn, so work with me if')
    print('          I make little mistakes :D')
    print('')
    print("Your options of what to type (exactly) are preliminar, capitulo 1, capitulo 2")
    print("  y finalmente, capitulo 3")
    print('')
    c = input('What chapter do you want to learn? ')
    print("")
    if c == "preliminar":
        capitulo_preliminar_study_vocab()
        else_end_statement()
    if c == "capitulo 1":
        capitulo_1_study_vocab()
        else_end_statement()
    if c == "capitulo 2":
        capitulo_2_study_vocab()
        else_end_statement()
    if c == "capitulo 3":
        capitulo_3_study_vocab()
        else_end_statement()
    else:
        else_end_statement()


# this is the chapter one study function, it has all the words and definitions listed
# for chapter one vocabulary

def capitulo_preliminar_study_vocab():
    print(" You chose chapter preliminar!!")
    print('')
    print('   The first section is on Greetings')
    print(" Let's get started!")
    vocab_word_and_meaning_enter_english('bastante bien', 'just fine')
    vocab_word_and_meaning_enter_english('bien, gracias', 'fine, thanks')
    vocab_word_and_meaning_enter_english('buenos dias', 'good morning')
    print(" don't forget the accent on the i in dias!")
    vocab_word_and_meaning_enter_english('buenas tardes', 'good afternoon')
    vocab_word_and_meaning_enter_english('como esta usted?', 'how are you?')
    print(" there's an accent on that last a in esta")
    vocab_word_and_meaning_enter_english('hola!', 'hi! hello!')
    vocab_word_and_meaning_enter_english('mas o menos', 'so-so')
    vocab_word_and_meaning_enter_english('muy bien', 'really well')
    vocab_word_and_meaning_enter_english('que tal?', "how's it going?")
    vocab_word_and_meaning_enter_english('regular', 'okay')
    vocab_word_and_meaning_enter_spanish('y tu?', 'and you? informal')
    print(" accent on the u in tu!")
    vocab_word_and_meaning_enter_english('y usted?', 'and you? formal')

    pass

def capitulo_1_study_vocab():
    print(" You chose chapter 1!!")
    pass

def capitulo_2_study_vocab():
    print(" You chose chapter 2!!")
    pass

def capitulo_3_study_vocab():
    print(" You chose chapter 3!!")
    pass

##############################################################################
##  THIS IS WHERE THE PROGRAM IS INITIALLY CALLED FOR THE FIRST TIME ##

opening_choice_options()







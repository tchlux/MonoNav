import spell_checker

spch1 = spell_checker.SpellChecker("test_dict1.txt")
spch2 = spell_checker.SpellChecker("test_dict2.txt")
spch3 = spell_checker.SpellChecker("test_dict3.txt")



##Test 1
print(spch1)
print("Expected out: cat, cow, baby, boom")

##Test 2
print(spch2)
print("Expected out: i")
spch2.add_word("idiot")
print(spch2)
print("Expected out: i, idiot")


##Test 3
print(spch3)
print("Expected out: lost, looking")

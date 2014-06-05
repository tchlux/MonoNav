# Roanoke College: Team 35
# prob7.py
tweets = int(input())
hashtag = []
for index in range(2*tweets-1):
    tweet = input().split()
    for index in range(len(tweet)):
        if tweet[index][0] == "#":
            hashtag.append(tweet[index].lower().strip('.').strip(','))
dictionary = {}
set_hashtag = list(set(hashtag))
for index in range(len(set_hashtag)):
    val = hashtag.count(set_hashtag[index])
    dictionary_keys = list(dictionary.keys())
    if val in dictionary_keys:
        dictionary[val].append(set_hashtag[index])
    else:
        dictionary[val] = [set_hashtag[index]]

dictionary_keys = list(dictionary.keys())
dictionary_keys.reverse()
for key in dictionary_keys:
    dictionary[key].sort()
    for index in range(len(dictionary[key])):
        print(str(key), dictionary[key][index][1:])


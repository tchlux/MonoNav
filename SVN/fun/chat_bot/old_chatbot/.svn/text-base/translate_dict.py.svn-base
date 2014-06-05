import pickle

def create_new_dict():
    input_file = open("big_dictionary.txt", "rb")
    old_dict =  pickle.load(input_file)
    input_file.close()
    new_dict = {}
    for key in old_dict:
        new_dict[key] = {}
        if ((key != "") and (key != " ") and (type(old_dict[key][0] == list))):
            for response in old_dict[key]:
                new_dict[key][response[0]] = response[1]
        else:
            print("Broken key: " , key)
            print("Response to that: ", old_dict[key])
    output_file = open("big_dictionary.pkl", "wb")
    pickle.dump(new_dict, output_file)
    print("New dictionary:\n", new_dict)
    output_file.close()


create_new_dict()

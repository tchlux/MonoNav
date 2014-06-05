# def: This function is for testing
def test_button_com(event=None):
    print("Test button command called")

# Pre:  For packing all of the buttons appropriately
# Post: 
def pack_all(base):
    for i,f in enumerate(base.frames):
        for b in base.buttons[i]:
            print(b.master.)
            b.pack()
        for l in base.labels[i]:
            l.pack()
        for e in base.entries[i]:
            e.pack()
        f.pack()

def add_word_to_dict(event=None):
    word = ##stopped here

# Pre:  
# Post: 
def build_buttons(base, words):
    base.frame() #add a new frame
    base.button("Build Connections",words.build_connections) 
    base.button("Add Word", add_word_to_dict)
    base.label("Label! yay")
    base.entry()

    pack_all(base)


#button for initiating the building of connections
#entry box for adding a connection, labels for current connections

#labels for a word and all of it's connections

#labels for words currently in the dictionary

from timeit import Timer
from timeit import timeit
import random

NUM_EXECUTIONS = 10

class DictTimer:

    def __init__(self, num_elements):
        self.a_list = []
        self.a_dictionary = {}
        self.num_elements = num_elements

    def setup_structures(self):
        self.a_list = []
        self.a_dictionary = {}
        for data in range(self.num_elements):
            word = chr(data)
            self.a_dictionary[data] = word
            self.a_list.append(word)
    
    def do_dictionary_lookup(self):
        for word in self.a_dictionary:
            self.a_dictionary[word]

    def do_list_lookup(self):
        for i in range(self.num_elements):
            self.a_list.index(chr(i))

    def time_search(self):
        dict_timer = Timer(self.do_dictionary_lookup, self.setup_structures)
        dict_ms_elapsed = dict_timer.timeit(NUM_EXECUTIONS)

        list_timer = Timer(self.do_list_lookup, self.setup_structures)
        list_ms_elapsed = list_timer.timeit(NUM_EXECUTIONS)

        return dict_ms_elapsed, list_ms_elapsed

if __name__ == "__main__":
    for i in range(100, 5000, 100):
        dT = DictTimer(i)
        d_time, l_time = dT.time_search()
        print(i,":", d_time, l_time)

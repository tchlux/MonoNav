import timeit
import sys

INIT_LENGTH = 10000
LOOP_LENGTH = 1000000
FIVEPERCENT = LOOP_LENGTH//20
TIMER_LENGTH = 100

class Testtimes():
    def __init__(self):
        #Percent status bar
        print("\n10%                    100%\n   ", end="")

        self.list = [None for i in range(INIT_LENGTH)]
        self.time_list = []
        self.timer = timeit.Timer(self.append_list)
        for i in range(LOOP_LENGTH):
            self.status_bar(i)
            self.time_list.append(self.timer.timeit(TIMER_LENGTH))

    def append_list(self):
        self.list.append(None)

    def status_bar(self, i):
        if i % FIVEPERCENT == 0:
            print("l", end="")
            sys.stdout.flush()

    def __str__(self):
        print("\nNumber of times recorded: "+str(len(self.time_list)) +'\nFinal length of list: '+ str(len(self.list)))
        temp = [self.time_list[i] for i in range(0,LOOP_LENGTH,FIVEPERCENT*2)]
        for value in temp:
            print(str(value))
        return ""


t = Testtimes()
print(t)

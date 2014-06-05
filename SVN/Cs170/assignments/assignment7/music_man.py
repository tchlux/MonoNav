import random
import sound
from linked_list import LinkedList
import sys

SAMPLE_FREQ = 44100 #This is the number of samples a second
DECAY = .996        #This is the decay factor of a note over time

class Music:

    #Method:Constructor, this method will initialize necessary attributes
    #Pre:   A file name is given (this is temporary)
    #Att's: All are created here
    #Post:  The Music class is ready to create some music
    def __init__(self, fil):
        text_file = fil
#        text_file = sys.argv
        f = open(text_file, "r")
        self.line_list = f.readlines()
        f.close()
        header = self.line_list.pop(0).split()
        print(header)
        self.bpm, self.total_beats = int(header[0]), int(header[1])
        self.song = []
        self.sound = sound.Sound(SAMPLE_FREQ)

    #Method:This method creates the song from a text file
    #Pre:   The method is called
    #Att's: self.line_list (type=List)
    #       self.numb_to_frequency (type=Method)
    #       self.sound (type=Sound class instance)
    #Post:  The whole song is writen to a file named Song.wav
    def create_song(self):
        note_list = []
        for line in self.line_list:
            values = line.split()
            note = self.numb_to_frequency(int(values[0]))
            note_list.append(note)
            duration = float(values[1])
            if duration == 0:
                pass
            else:
                print("Duration:",duration)
                print("Note list:",note_list)
                self.create_note(duration,
                                 note_list)
                note_list = []
        self.sound.write("Song.wav")

    #Method:This method converts an integer to a frequency assuming
    #       the number is the number of steps from concert A
    #Pre:   An integer is given
    #Att's: None
    #Post:  The frequency of that note is returned
    def numb_to_frequency(self,num):
        return 440 * 2 ** (num/12)

    #Method:This method initializes the necessary linked list for a
    #       frequency
    #Pre:   The frequency is given as a float
    #Att's: LinkedList has been imported
    #Post:  the linked list is returned
    def create_linked_list(self, freq):
        length = int(SAMPLE_FREQ / freq)
        print(length)
        lst = LinkedList()
        for i in range(length):
            lst.add_last(random.random()*2 -1)
        return lst

    #Method:This method creates one note of the song given a frequency
    #       and a duration
    #Pre:   The frequency and duration are given as Floating points
    #       numbers
    #Att's: self.create_linked_list (type=Method)
    #       self.bpm (type=Integer)
    #       self.sound (type=Sound class instance)
    #Post:  The note is created and added to self.sound's sample list
    def create_note(self, duration, freqs):
        lst = []
        for frequency in freqs:
            lst.append(self.create_linked_list(frequency))
        beats_per_second = self.bpm/60
        seconds = duration/beats_per_second
        samples = seconds*SAMPLE_FREQ
        for i in range(int(samples)):
            summ = 0
            for linked_list in lst:
                node = linked_list.get_first()
                summ += node.object
                linked_list.remove_first()
                linked_list.add_last(((node.object +
                                       node.next.object)/2)*DECAY)
            if summ > 1:
                summ = 1
            if summ < -1:
                summ = -1
            self.sound.add_sample(summ)




if __name__ == "__main__":
    m = Music("test_song_2")
#    m = Music("somebody_that_i_used_to_know")
    m.create_song()

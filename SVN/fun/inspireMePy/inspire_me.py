from WordDict import * #WordDict
from inspireMeTk import * #BaseFrame, Canvas
import imButtons as bs

# Pre:  
# Post: The WordDict is operated on appropriately for the connections
# to be created
def inspire_me():
    base = BaseFrame()
    main_dict = WordDict()
    bs.build_buttons(base)
    # response = input(PROMPT)
    # while response != "__STOP__":
    #     WordDict.run()

    
if __name__ == "__main__":
    inspire_me()
    tk.mainloop()

HEX_KEYS = {0:"0",1:"1",2:"2",3:"3",4:"4",5:"5",6:"6",7:"7",8:"8",9:"9",10:"A",11:"B",12:"C",13:"D",14:"E",15:"F"}
HEX_LENGTH = 6 +1
HEX = 16

def convert(rgb,final="#"):
    for i in rgb: final=final+HEX_KEYS[i//HEX]+HEX_KEYS[i%HEX]
    return final

if __name__ == "__main__":
    test = (0,0,0)
    print(convert(test))
    test = (75, 150, 215)
    print(convert(test))
    test = (255,255,255)
    print(convert(test))

    #How to do it in one line of code!!
    # def convert(rgb):
    # return str([[HEX_KEYS[i//HEX],
    #              HEX_KEYS[i%HEX]] for i in rgb]).replace("[","#",1).replace("[","").replace("]","").replace(",","").replace("'","").replace(" ","")


##  STANDALONE FUNCTION  ##

#Function:This function converts an rgb tuple (in range 0-255) into a
#         hexidecimal string
def to_hex(rgb,final="#"):
    hex_keys = {0:"0",1:"1",2:"2",3:"3",4:"4",5:"5",6:"6",7:"7",8:"8",9:"9",10:"A",11:"B",12:"C",13:"D",14:"E",15:"F"}
    for i in rgb: final=final+hex_keys[i//16]+hex_keys[i%16]
    return final

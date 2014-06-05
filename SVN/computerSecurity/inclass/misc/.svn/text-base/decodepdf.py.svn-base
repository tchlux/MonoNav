## fix the pdf document!
import struct

NEWFILE = "fixed_syllabus.pdf"

def return_pdf(filename):
    a = open(filename, "rb")
    new = open(NEWFILE, "wb")
    for line in a:
        for char in line:
            replacement = struct.pack("B", (int(char)-3)%256)
            new.write(replacement)
    a.close()
    new.close()

return_pdf("CPSC310_Syllabus.pdf")

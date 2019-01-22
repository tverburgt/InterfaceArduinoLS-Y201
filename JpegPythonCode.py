import binascii

f = open ("outputData5.txt","r")
nf = open("binaryData5.jpg","wb")


#Read whole file into data
while 1:
    c = f.readline()
    d = c.strip()
    if not c:
        break
    nf.write(binascii.a2b_hex(d))


# Close the file
f.close()
nf.close()

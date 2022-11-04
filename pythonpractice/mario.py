import cs50

height = cs50.get_int("height: ")
while(0 > height > 9):
    height = cs50.get_int("height: ")
blocks = 1
for i in range(0, height):
    for i in range(0, height - blocks):
        print(" ", end = "")
    for i in range(0, blocks):
            print("#", end = "")
    print(" ", end = "")
    for i in range(0, blocks):
        print("#", end = "")
    print(" ")
    blocks += 1
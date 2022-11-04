import cs50

#get card num
card_num = cs50.get_int("card number: ")

#split each digit to a list
nums = [int(x) for x in str(card_num)]

#check start for card type and length for type and validity
if (nums[0] == 4) and (len(nums) == 13 or len(nums) == 16):
    c_type = "Visa"
elif (len(nums) == 15) and (nums[0] == 3) and (nums[1] == 4 or nums[1] == 7):
    c_type = "American Express"
elif (len(nums) == 16) and (nums[0] == 5) and (1 <= nums[1] <= 5):
    c_type = "Mastercard"
else:
    c_type = "Invalid"

#for loop multiply every other by 2 starting with 2nd last and add each digit
sum1 = 0
for i in range(len(nums) - 2, -1, -2):
    if 2*nums[i] >= 10:
        split = [int(x) for x in str(2*nums[i])]
        split_total = split[0] + split[1]
        sum1 += split_total
    else:
        sum1 += 2*nums[i]

#add not multiplied to each other
sum2 = 0
for i in range(len(nums) - 1, -1, -2):
    sum2 += nums[i]

#sum the 2
total = sum1 + sum2
total_list = [int(x) for x in str(total)]
if (total_list[len(total_list) - 1] == 0) and (c_type != "Invalid"):
    print(f"Valid {c_type}")
else:
    print("Invalid card :(")
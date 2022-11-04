from cs50 import get_string

#index = 0.0588 * L - 0.296 * S - 15.8
#L is the average number of letters per 100 words in the text broken up by spaces -> letters/words * 100
#S is the average number of sentences per 100 words in the text. broken up by ., !, or ? -> words/sentences * 100
#get input for sentence
phrase = get_string("phrase: ")
#count sentences, letters, and words
letters = 0
words = 0
sentences = 0
other = 0
phrase_list = [c for c in phrase]
for i in range(0, len(phrase_list)):
    if (91 > ord(phrase_list[i]) > 64) or (123 > ord(phrase_list[i]) > 96):
        letters += 1
    elif (ord(phrase_list[i]) == 32):
        words += 1
    elif (ord(phrase_list[i]) == 46) or (ord(phrase_list[i]) == 33) or (ord(phrase_list[i]) == 63):
        sentences += 1
    else:
        other += 1
words += 1
#print(letters)
#print(words)
#print(sentences)
#find L and S
L = (letters/words) * 100
#print(L)
S = (sentences/words) * 100
#print(S)
# calc index and print grade level
index = (0.0588 * L) - (0.296 * S) - 15.8
#print(index)
grade_level = round(index)
if grade_level > 16:
    print("16+ grade reading level.")
elif grade_level < 1:
    print("Before 1st grade reading level.")
elif grade_level == 2:
    print("2nd grade reading level.")
elif grade_level == 3:
    print("3rd grade reading level.")
else:
    print(f"{grade_level}th grade reading level.")
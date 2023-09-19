import palindrome_module

for word in ["racecar", "taco cat", "abba", "a", " ", ""]:
    print(word, palindrome_module.is_palindrome(word))

for word in ["not a palindrome", "abc", "a b c", "123"]:
    print(word, palindrome_module.is_palindrome(word))

for x in [123, None, True, [], {}, lambda x: 1]:
    try:
        palindrome_module.is_palindrome(x)
        print("Exception should have been thrown for item", x)
    except TypeError:
        print("Correct exception thrown for item", x)

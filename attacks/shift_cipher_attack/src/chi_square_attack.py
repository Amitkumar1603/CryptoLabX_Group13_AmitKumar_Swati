

from shift_cipher import decrypt
frequency = [
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23,
    2.02, 6.09, 6.97, 0.15, 0.77, 4.03,
    2.41, 6.75, 7.51, 1.93, 0.10, 5.99,
    6.33, 9.06, 2.76, 0.98, 2.36, 0.15,
    1.97, 0.07
]


def chi_square(text):

    letters = ""

    for ch in text:
        if ch.isalpha():
            letters+=ch.upper()

    total = len(letters)

    if total == 0:
        return 999999

    score=0

    for i in range(26):

        count = letters.count(chr(65 + i))

        expected = total*frequency[i]/100

        score += (count - expected) ** 2/expected

    return score


def attack(ciphertext):

    best_key = 0
    best_score = 999999
    best_text = ""

    for key in range(26):

        plaintext = decrypt(ciphertext, key)

        score = chi_square(plaintext)

        if score < best_score:
            best_score = score
            best_key = key
            best_text = plaintext

    return best_key, best_text, best_score

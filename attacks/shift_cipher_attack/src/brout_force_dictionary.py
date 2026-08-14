from shift_cipher import decrypt

def attack(text):

    dictionary = ["THE", "IS", "A", "HELLO", "WORLD", "THIS", "TEST"]

    best_key = 0
    best_score = 0

    for key in range(26):

        plain=decrypt(text, key)

        score=0

        for word in plain.split():
            if word in dictionary:
                score+=1

        print("Key:", key, "Score:", score, "Text:", plain)

        if(score > best_score):
            best_score = score
            best_key = key

    print("Best Key:", best_key)
    print("Best Score:", best_score)

    return best_key

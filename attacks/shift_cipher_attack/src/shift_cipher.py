def encrypt(text, key):
    result = ""

    for c in text:
   	 result += chr((ord(c) - 65 + key) % 26 + 65)

    return result


def decrypt(text, key):
    return encrypt(text, -key)

def encrypt(text, key):
    result = ""

    for c in text:
        if c == " ":
            result+=" "
        else:
            result+=chr((ord(c) - 65 + key) % 26 + 65)

    return result


def decrypt(text, key):
    return encrypt(text, -key)

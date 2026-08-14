from shift_cipher import encrypt

text ="HELLO WORLD"
key = 3

cipher = encrypt(text, key)

print("Original:", text)
print("Cipher:", cipher)


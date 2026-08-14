from shift_cipher import encrypt
from brout_force_dictionary import attack
#from chi_square_attack import attack as chi_attack

text = "HELLO WORLD"
key = 3

cipher = encrypt(text, key)

print("Original:", text)
print("Cipher:", cipher)

print("\nBrute Force:")
attack(cipher)

#print("\nChi Square:")
#print("Key:", chi_attack(cipher))

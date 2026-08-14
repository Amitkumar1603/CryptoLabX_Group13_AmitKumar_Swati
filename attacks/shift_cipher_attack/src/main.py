from shift_cipher import encrypt
from brout_force_dictionary import attack
from chi_square_attack import attack as chi_attack

text = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG AND THIS IS A TEST MESSAGE FOR CRYPTANALYSIS"
key = 3

cipher = encrypt(text, key)

print("Original:", text)
print("Cipher:", cipher)

print("\n")

print("Brute Force:")
attack(cipher)



print("Chi Square:")
print("Key:", chi_attack(cipher))

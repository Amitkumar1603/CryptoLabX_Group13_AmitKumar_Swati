from Crypto.Cipher import AES

BLOCK_SIZE = 16
KEY = b"0123456789abcdef"


def pkcs7_pad(data):
    padding = BLOCK_SIZE - (len(data) % BLOCK_SIZE)
    return data + bytes([padding]) * padding


def pkcs7_unpad(data):
    if not data or len(data) % BLOCK_SIZE != 0:
        raise ValueError("Invalid padding")

    padding = data[-1]

    if padding < 1 or padding > BLOCK_SIZE:
        raise ValueError("Invalid padding")

    if data[-padding:] != bytes([padding]) * padding:
        raise ValueError("Invalid padding")

    return data[:-padding]


def encrypt(plaintext, iv):
    cipher = AES.new(KEY, AES.MODE_CBC, iv)
    return cipher.encrypt(pkcs7_pad(plaintext))


def oracle(ciphertext, iv):
    cipher = AES.new(KEY, AES.MODE_CBC, iv)

    try:
        plaintext = cipher.decrypt(ciphertext)
        pkcs7_unpad(plaintext)
        return True
    except ValueError:
        return False


def padding_oracle_attack(ciphertext, iv):
    blocks = [
        ciphertext[i:i + BLOCK_SIZE]
        for i in range(0, len(ciphertext), BLOCK_SIZE)
    ]

    previous_blocks = [iv] + blocks[:-1]

    recovered = bytearray()
    total_queries = 0

    for block_number in range(len(blocks)):
        original_previous = previous_blocks[block_number]
        target_block = blocks[block_number]

        modified_previous = bytearray(original_previous)
        intermediate = bytearray(BLOCK_SIZE)
        plaintext_block = bytearray(BLOCK_SIZE)

        for position in range(BLOCK_SIZE - 1, -1, -1):
            padding_value = BLOCK_SIZE - position

            for j in range(position + 1, BLOCK_SIZE):
                modified_previous[j] = (
                    intermediate[j] ^ padding_value
                )

            found = False

            for guess in range(256):
                modified_previous[position] = guess

                test_ciphertext = (
                    bytes(modified_previous) + target_block
                )

                total_queries += 1

                if oracle(test_ciphertext, bytes(16)):
                    intermediate[position] = (
                        guess ^ padding_value
                    )

                    plaintext_block[position] = (
                        intermediate[position]
                        ^ original_previous[position]
                    )

                    found = True
                    break

            if not found:
                raise RuntimeError(
                    f"Could not recover byte {position}"
                )

        recovered.extend(plaintext_block)

    plaintext = pkcs7_unpad(bytes(recovered))

    return plaintext, total_queries


def main():
    plaintext = b"This is a secret AES CBC message."

    iv = b"1234567890abcdef"

    ciphertext = encrypt(plaintext, iv)

    print("Ciphertext:", ciphertext.hex())
    print("IV:", iv.hex())

    recovered_plaintext, queries = padding_oracle_attack(
        ciphertext,
        iv
    )

    print("Recovered plaintext:", recovered_plaintext.decode())
    print("Total oracle queries:", queries)


if __name__ == "__main__":
    main()


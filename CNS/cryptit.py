#!/bin/python

def xenc(ch, key):
    cd = (key ^ ch) + key
    return cd

def xdec(cd, key):
    ch = (cd - key) ^ key
    return ch

def encrypt(msg, key):
    cph = ""
    for ch in msg:
        cph += chr(xenc(ord(ch), key) % 0x110000)
    return cph

def decrypt(cph, key):
    ans = ""
    for cd in cph:
        ans += chr(xdec(ord(cd), key) % 0x110000)
    return ans

def main():
    msg = input("Enter Message: ")
    key = int(input("Enter Key (Integer): "))

    cph = encrypt(msg, key)
    ans = decrypt(cph, key)

    print("Encrypted Plaintext:", msg)
    print("Ciphertext:", cph)
    print("Decrypted Plaintext:", ans)

if __name__ == "__main__":
    main()

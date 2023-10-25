#!/bin/python
alph = "ABCDEFGHIKLMNOPQRSTUVWXYZ"
def genmat(key):
    key = key.upper().replace('J', 'I')
    matrix = [['' for _ in range(5)] for _ in range(5)]
    used_chars = set()
    row, col = 0, 0
    
    for char in key + alph:
        if char not in used_chars:
            matrix[row][col] = char
            used_chars.add(char)
            col += 1
            if col == 5:
                col = 0
                row += 1
    
    return matrix


def getpos(matrix, char):
    for row in range(5):
        for col in range(5):
            if matrix[row][col] == char:
                return row, col


def encrypt(plain_text, key):
    matrix = genmat(key)
    
    plain_text = plain_text.upper().replace('J', 'I').replace(' ', '')
    
    if len(plain_text) % 2 != 0:
        plain_text += 'X'
    
    cipher_text = ''
    for i in range(0, len(plain_text), 2):
        char1, char2 = plain_text[i], plain_text[i + 1]
        row1, col1 = getpos(matrix, char1)
        row2, col2 = getpos(matrix, char2)
        
        if row1 == row2:
            cipher_text += matrix[row1][(col1 + 1) % 5] + matrix[row2][(col2 + 1) % 5]
        elif col1 == col2:
            cipher_text += matrix[(row1 + 1) % 5][col1] + matrix[(row2 + 1) % 5][col2]
        else:
            cipher_text += matrix[row1][col2] + matrix[row2][col1]
    
    return cipher_text


def decrypt(cipher_text, key):
    matrix = genmat(key)
    
    plain_text = ''
    for i in range(0, len(cipher_text), 2):
        char1, char2 = cipher_text[i], cipher_text[i + 1]
        row1, col1 = getpos(matrix, char1)
        row2, col2 = getpos(matrix, char2)
        
        if row1 == row2:
            plain_text += matrix[row1][(col1 - 1) % 5] + matrix[row2][(col2 - 1) % 5]
        elif col1 == col2:
            plain_text += matrix[(row1 - 1) % 5][col1] + matrix[(row2 - 1) % 5][col2]
        else:
            plain_text += matrix[row1][col2] + matrix[row2][col1]
    
    return plain_text



key = "XHIDDEN"
plain_text = "SECRET"
cipher_text = encrypt(plain_text, key)
print("ciphertext :", cipher_text)

decrypted_text = decrypt(cipher_text, key)
print("plaintext :", decrypted_text)

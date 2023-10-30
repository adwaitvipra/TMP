'''
p is large prime
q is primitve root of p

a:
xa: private key
ya: public key (q^xa)mod(p)

b:
xb: private key
yb: public key (q^xb)mod(p)

ka = (yb^xa)mod(p)
kb = (ya^xb)mod(p)
'''

def isvalid (p,xa):
    if xa < p:
        return True
    return False

def rsa ():
    p = int(input("p ="))
    q = int(input("q ="))

    xa = int(input("a ="))
    xb = int(input("b ="))

    if isvalid (p, xa) and isvalid (p, xb):
        ya = pow(q, xa) % p
        yb = pow(q, xb) % p

        print("ya =", ya)
        print("yb =", yb)

        ka = pow(yb, xa) % p
        kb = pow(ya, xb) % p

        print ("ka =", ka,"kb =", kb)
    else:
        print("Invalid private keys!\n")

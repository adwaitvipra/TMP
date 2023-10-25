'''
p = prime
q = primitve root of p

A:
Xa: private key
Ya: public key (q^Xa)mod(p)

B:
Xb: private key
Yb: public key (q^Xb)mod(p)


Ka = (Yb^Xa)mod(p)
Kb = (Ya^Xb)mod(p)
'''
def check_validity(p,Xa):
    if Xa < p:
        return True
    else:
        return False


p = int(input("Enter prime number, p:"))
q = int(input("Enter primitive root:"))

Xa = int(input("Enter private key of A:"))
Xb = int(input("Enter private key of B:"))

if check_validity(p,Xa) and check_validity(p,Xb):
    Ya = pow(q,Xa)%p
    Yb = pow(q,Xb)%p

    print("Public key of A: ",Ya)
    print("Public key of B: ",Yb)

    print("Shared Private Key:\n")

    Ka = pow(Yb,Xa)%p
    Kb = pow(Ya,Xb)%p

    print("Ka = ",Ka," Kb = ",Kb,"\n")
else:
    print("Check your private keys! Cant be greater than p!\n")

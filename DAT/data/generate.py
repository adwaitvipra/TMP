import csv
import json

climit = 100000
ctype = ("ADM", "ORG", "IND")
crange = {'ADM': tuple(range(1, 11)),
          'ORG': tuple(range(11, 411)),
          'IND': tuple(range(411, 15011))}

loaddata = True;
if (loaddata):
    fpadm = open("admin.json", "r")
    fporg = open("organization/organization.json", "r")
    fporgprf = open("organization/preference.json", "r")
    fporgreq = open("organization/preference.json", "r")

if (fpadm and fporg):
    admins = json.load(fpadm)
    organizations = json.load(fporg)
    fpadm.close()
    fporg.close()
else:
    admins = {}
    organizations = {}

if (fporgprf and fporgreq):
    orgprfs = json.load(fporgprf)
    orgreqs = json.load(fporgreq)
    fporgprf.close()
    fporgreq.close();
else:
    orgprfs = {}
    orgreqs = {}

def generate_clients(climit, crange, filename = "client.csv"):
    features = ("CID", "PWD")
    fill = len(str(climit))
    fh = open(filename, "w")

    if (fh):
        writer = csv.DictWriter(fh, features, delimiter = ';')
        writer.writeheader()

        for ctype in crange:
            for uid in crange[ctype]:
                cid = ctype + str(uid).zfill(fill)
                pwd = cid
                client = {'CID': cid, 'PWD': pwd}
                writer.writerow(client)

        fh.close()

def populate_admins(admins, climit, ctype, crange, filename = "admin.csv"):
    features = ("CID", "NAME", "GENDER", "DOB", "ROLE")
    fill = len(str(climit))
    fh = open(filename, "w")

    if (fh):
        writer = csv.DictWriter(fh, features, delimiter = ";")
        writer.writeheader()

        itr = 0
        for uid in crange[ctype]:
            admin = admins[itr]

            cid = ctype + str(uid).zfill(fill)
            admin[features[0]] = cid
            writer.writerow(admin)

            itr += 1


        fh.close()

def generate_organization(organizations, climit, ctype, crange, )

def populate_organizations(organizations, climit, ctype, crange, filename = "organization.csv")

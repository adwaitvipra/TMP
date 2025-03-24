import csv
import json
from random import sample
from faker import Faker as fk

climit = 1000000
txnlimit = 1000000
ctype = ("ADM", "ORG", "IND")
crange = {'ADM': tuple(range(1, 11)),
          'ORG': tuple(range(11, 411)),
          'IND': tuple(range(411, 100411))}

fake = fk()

loaddata = True
if (loaddata):
    fpadm = open("./admin.json", "r")
    fporg = open("./organization/organization.json", "r")
    fporgprf = open("./organization/preference.json", "r")
    fporgreq = open("./organization/preference.json", "r")
    fpname = open("./individual/name.json", "r")
    fpeducation = open("./individual/education.json", "r")
    fpoccupation = open("./individual/occupation.json", "r")
    fpindprf = open("./individual/preference.json", "r")
    fpindreq = open("./individual/requirement.json", "r")
    fpcity = open("./individual/city.json", "r")
    fpcountry = open("./individual/country.json", "r")
    fptxnorg = open("./transaction/organization.json", "r")
    fptxnind = open("./transaction/individual.json", "r")
    fptxnmode = open("./transaction/mode.json", "r")

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
    fporgreq.close()
else:
    orgprfs = {}
    orgreqs = {}

if (fpname and fpeducation and fpoccupation and fpindprf and fpindreq and fpcity and fpcountry):
    names = json.load(fpname)
    educations = json.load(fpeducation)
    occupations = json.load(fpoccupation)
    cities = json.load(fpcity)
    countries = json.load(fpcountry)
    indprfs = json.load(fpindprf)
    indreqs = json.load(fpindreq)
else:
    names = {}
    locations = {}
    educations = {}
    occupations = {}
    cities = {}
    countries = {}
    indprfs = {}
    indreqs = {}

if (fptxnorg and fptxnorg and fptxnmode):
    txnorg = json.load(fptxnorg)
    txnind = json.load(fptxnind)
    txnmode = json.load(fptxnmode)
else:
    txnorg = {}
    txnind = {}
    txnmode = {}

def generate_customers(climit = climit, crange = crange, filename = "customer.json"):
    features = ("CID", "TYPE")
    custtype = {"ORG": "ORGANIZATION", "IND": "INDIVIDUAL"}

    fill = len(str(climit))
    fh = open(filename, "w")

    if (fh):
        writer = csv.DictWriter(fh, features, delimiter = ';')
        writer.writeheader()

        crange.pop("ADM")
        for ctype in crange:
            for uid in crange[ctype]:
                cid = ctype + str(uid).zfill(fill)
                customer = {'CID': cid, 'TYPE': custtype[ctype]}
                writer.writerow(customer)      

        fh.close()


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

def populate_organizations(organizations, climit, ctype, crange, requirements = orgreqs, preferences = orgprfs, filename = "organization.csv"):
    features = ("CID", "NAME", "COUNTRY", "INDUSTRY", "SECTOR", "REQUIREMENTS", "PREFERENCES")
    fill = len(str(climit))
    fh = open(filename, "w")

    if (fh):
        writer = csv.DictWriter(fh, features, delimiter = ";")
        writer.writeheader()

        itr = 0
        for uid in crange[ctype]:
            org = organizations[itr]

            cid = ctype + str(uid).zfill(fill)
            org[features[0]] = cid
            org[features[5]] = str.join(', ', sample(orgprfs[org["SECTOR"]], 3))
            org[features[6]] = str.join(', ', sample(orgreqs[org["SECTOR"]], 3))

            writer.writerow(org)

            itr = (itr + 1) % len(organizations)

        fh.close()

def populate_individuals(names, climit, ctype, crange, cities = cities, countries = countries, educations = educations, occupations = occupations, requirements = indreqs, prefereces = indprfs, filename = "individual.csv"):
    features = ("CID", "NAME", "GENDER", "DOB", "CITY", "COUNTRY", "EDUCATION", "OCCUPATION", "REQUIREMENTS", "PREFERENCES")
    fill = len(str(climit))
    fh = open(filename, "w")

    if (fh):
        writer = csv.DictWriter(fh, features, delimiter = ";")
        writer.writeheader()

        flag = False
        find = names["F"]
        mind = names["M"]

        ind = {}
        for uid in crange[ctype]:
            ind[features[0]] = ctype + str(uid).zfill(fill)

            flag != flag
            if (flag):
                ind[features[1]] = sample(find, k = 1)[0]
                ind[features[2]] = "F"
            else:
                ind[features[1]] = sample(mind, k = 1)[0]
                ind[features[2]] = "M"

            ind[features[3]] = fake.date_of_birth(None, 18, 80)
            ind[features[4]] = sample(cities, k = 1)[0]
            ind[features[5]] = sample(countries, k = 1)[0]
            ind[features[6]] = sample(educations, k = 1)[0]
            ind[features[7]] = sample(occupations, k = 1)[0]
            ind[features[8]] = str.join(", ", sample(requirements, k = 3))
            ind[features[9]] = str.join(", ", sample(prefereces, k = 3))

            writer.writerow(ind)

        fh.close()

def populate_transactions(txnlimit, crange = crange, organization = txnorg, individual = txnind, mode = txnmode, filename = "transaction.json"):
    features = ("CID", "TYPE", "AMOUNT", "MODE", "DATE")
    fh = open(filename, "w")

    if (fh):
        writer = csv.DictWriter(fh, features, delimiter = ";")
        writer.writeheader()

        fh.close()
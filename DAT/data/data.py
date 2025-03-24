#!/bin/python

from generate import *

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# CLIENT (CID, PWD)
#------------------------------------------------------------------------------#

# generate_clients(climit, crange)

#------------------------------------------------------------------------------#
# ADMIN (CID, NAME, GENDER, DOB, ROLE)
#------------------------------------------------------------------------------#

# populate_admins(admins, climit, ctype[0], crange)

#------------------------------------------------------------------------------#
# ORGANIZATION  (CID, NAME, COUNTRY,
#                INDUSTRY, SECTOR,
#                REQUIREMENTS, PREFERENCES)
#------------------------------------------------------------------------------#

# populate_organizations(organizations, climit, ctype[1], crange)

#------------------------------------------------------------------------------#
# INDIVIDUAL    (CID, NAME, GENDER, DOB,
#                CITY, STATE, COUNTRY,
#                EDUCATION, OCCUPATION,
#                REQUIREMENTS, PREFERENCES)
#------------------------------------------------------------------------------#

# populate_individuals(names, climit, ctype[2], crange)

#------------------------------------------------------------------------------#
# TRANSACTION   (CID, TYPE,
#                AMOUNT,
#                MODE, DATE)
#------------------------------------------------------------------------------#

populate_transactions(txnlimit)

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

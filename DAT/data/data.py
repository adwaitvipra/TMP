#!/bin/python

from generate import *

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#
# CLIENT (CID, PWD)
#------------------------------------------------------------------------------#

generate_clients(climit, crange)

#------------------------------------------------------------------------------#
# ADMIN (CID, NAME, GENDER, DOB, ROLE)
#------------------------------------------------------------------------------#

populate_admins(admins, climit, ctype[0], crange)

#------------------------------------------------------------------------------#
# ORGANIZATION  (CID, NAME, COUNTRY,
#                INDUSTRY, SECTOR,
#                REQUIREMENTS, PREFERENCES)
#------------------------------------------------------------------------------#

generate_organizations(organizations, climit, ctype[1], crange)

#------------------------------------------------------------------------------#
# INDIVIDUAL    (CID, NAME, GENDER, DOB,
#                CITY, STATE, COUNTRY,
#                EDUCATION, OCCUPATION,
#                REQUIREMENTS, PREFERENCES)
#------------------------------------------------------------------------------#

generate_individuals()

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

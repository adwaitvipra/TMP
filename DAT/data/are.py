#!/bin/python

from google import genai

orgrecord = """CID;NAME;COUNTRY;INDUSTRY;SECTOR;REQUIREMENTS;PREFERENCES
ORG0000011;Airbus;France;Aircraft Manufacturing;Aerospace & Defense;Export-friendly tax policies, Private sector partnerships, Long-term procurement cycles;Long-term procurement cycles, Advanced aerospace R&D, Private sector partnerships"""

orgservice = open("organization/service.json").read()
orgproduct = open("organization/product.json").read()

client = genai.Client(api_key="AIzaSyBBXy7rwdocFT3EQ_nU2OE1Ag4BnTSoG0o")

response = client.models.generate_content(
    model="gemini-2.0-flash",
    contents=f"You are a bank and following are the financial services provided to organizations {orgservice}, following are the financial products for the organizations {orgproduct}, for the organization {orgrecord} select one best service and product generate json"
)

print(response.text)


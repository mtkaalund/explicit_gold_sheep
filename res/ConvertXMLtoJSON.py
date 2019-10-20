import sys
import xmltodict
import json

if( len(sys.argv) <= 1 ):
    print "There need aleast to be one xml file to be parsed"
    sys.exit(1)

org_fname = sys.argv[1]
new_fname = org_fname.split(".")[0] + ".json"

print org_fname
print new_fname

with open(org_fname) as fd:
    xml_dict = xmltodict.parse(fd.read())

with open(new_fname, 'w') as json_file:
    json.dump(xml_dict, json_file)

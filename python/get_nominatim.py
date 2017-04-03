import csv
import json
import urllib.request as ur

data = []
with open('data.csv', 'r') as f:
  for row in csv.reader(f, delimiter=';'):
    data.append(row)

base_url = "https://nominatim.openstreetmap.org/search.php?q="
for d in data:
  d[2] = d[2][0:-4].replace(" ","+")
  url = base_url + d[2] + "&format=jsonv2"
  print(url)

  response = ur.urlopen(url)
  text = response.read()
  j = json.loads(text)

  if(len(j)):
    with open("out_nominatim.csv", "a") as out:
      s = "%s;%s;%s;%s;%s" % (d[0],d[1],d[2].replace("+"," "),j[0]['lat'],j[0]['lon'])
      out.write(s + "\n")
      print(s)
  else:
    with open("out_nominatim.err", "a") as out:
      s = "%s;%s;%s;%s;%s" % (d[0],d[1],d[2].replace("+"," "),"null","null")
      out.write(s + "\n")
      print(s)


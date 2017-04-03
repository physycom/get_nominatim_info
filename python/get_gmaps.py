import csv
import json
import urllib.request as ur

data = []
with open('data.csv', 'r') as f:
  for row in csv.reader(f, delimiter=';'):
    data.append(row)

base_url = "http://maps.google.com/maps/api/geocode/json?address="
for d in data:
  d[2] = d[2].replace(" ","+")
  url = base_url + d[2]
#  print(url)

  response = ur.urlopen(url)
  text = response.read()
  j = json.loads(text)

  if(len(j["results"])):
    with open("out_gmaps.csv", "a") as out:
      lat = j["results"][0]["geometry"]["location"]["lat"]
      lon = j["results"][0]["geometry"]["location"]["lng"]
      s = "%s;%s;%s;%s;%s" % (d[0],d[1],d[2].replace("+"," "),lat,lon)
      out.write(s + "\n")
      print(s)
  else:
    with open("out_gmaps.err", "a") as out:
      s = "%s;%s;%s;%s;%s" % (d[0],d[1],d[2].replace("+"," "),"null","null")
      out.write(s + "\n")
      print(s)



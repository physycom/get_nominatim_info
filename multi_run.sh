#!/bin/bash
CONVERTER="./get_nominatim_info.exe"
for json in input/*.json; do
  echo "Parsing ${json}"
  json=$(basename $json)
  out="./output/${json%.*}.out.json"
  echo $json
  echo $out
  $CONVERTER -i $json -o $out
done

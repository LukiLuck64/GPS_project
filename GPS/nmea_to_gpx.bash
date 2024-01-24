#!/bin/bash
unext ()
{
 declare -a nameparts
 num=0
 nameparts=($(echo "$1" | sed 's/\./\t/g'))
 num=$((${#nameparts[*]}-1))
 ext="\\$(eval echo ".\${nameparts[$num]}")"
 seder="s/$ext//g"
 echo "$1" | sed -e $seder
}

if [ -z "$1" ]; then
 echo "Takes a list of inout NMEA files, converts to GPX files."
 echo  "usage: $0 <nmea_input_files>"
 exit 0
fi
echo ""
for file in "$@"; do
 fileNoExt=$(unext "$file")
 if [ ! -e "$file" ]; then
  echo "$file input file doesn't exist, Skipping."
 elif [ -e "$fileNoExt.gpx" ]; then
  echo "$fileNoExt.gpx already exists. Skipping"
 else
  echo "$fileNoExt.gpx - converting"
  gpsbabel -i nmea -f "$file" -o gpx -F "$fileNoExt.gpx"
 fi
done

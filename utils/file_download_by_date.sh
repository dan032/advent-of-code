#!/bin/bash
year=$1
day=$2
token=$3

YEAR_DIR=~/Desktop/advent-of-code/${year}
DAY_DIR="${YEAR_DIR}/${day}"
FILE="${DAY_DIR}/input.txt"

if test -f $FILE
then
    echo "Input Already Exists"
    exit 0
fi

url="https://adventofcode.com/${year}/day/${day}/input"
echo "Downloading input for ${url}"

response=$(curl -sB --cookie "session=${token}" $url -H "Connection: close")

if [ ! -d $DAY_DIR ]
then
    mkdir -p $DAY_DIR
    echo "Creating $DAY_DIR"
fi
echo $response > $FILE
echo "File saved"
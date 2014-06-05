#!/bin/bash

search=""
echo "Googling: $@"
for term in $@; do
    search+="%20$term"
done
xdg-open "http://www.google.com/search?q=$search"

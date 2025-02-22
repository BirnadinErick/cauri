#!/bin/bash

dir="${1:-.}"  # default to .

output_file="merged"

rm "$output_file.md"

touch $output_file
for file in "$dir"/*.md; do
    if [[ -f "$file" ]]; then
        cat "$file" >> "$output_file"
        echo -e "\n" >> "$output_file"
    fi
done

mv merged merged.md
echo "merged."

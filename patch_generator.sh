#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <patch_file_name> <output_dir>"
    exit 1
fi

patch_file_name="$1"
output_dir="$2"

cd xv6-riscv || {
	echo "xv6-riscv dir not found!"
	exit 1
}

patch_file="${patch_file_name}.patch"

git add --all
git diff HEAD > "$patch_file"

if [ -s "$patch_file" ]; then
	echo "Patch file generated successfully: $patch_file"
else
	echo "No changes detected between the commits."
	rm "$patch_file"
fi

mv "$patch_file" "$output_dir"
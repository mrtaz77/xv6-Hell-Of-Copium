#!/bin/bash

patch_file_name="threading"
output_dir="../Offlines/threading"

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
#!/bin/bash

patch_file_name="system_call"
output_dir="../Offlines/SystemCall"

cd xv6-riscv || {
	echo "xv6-riscv dir not found!"
	exit 1
}

current_commit=$(git rev-parse HEAD)

origin_head=$(git rev-parse origin/riscv)

if [ "$current_commit" == "$origin_head" ]; then
	echo "The submodule is already up-to-date. No patch needed."
	exit 0
fi

patch_file="${patch_file_name}.patch"
git diff "$origin_head" "$current_commit" > "$patch_file"

if [ -s "$patch_file" ]; then
	echo "Patch file generated successfully: $patch_file"
else
	echo "No changes detected between the commits."
	rm "$patch_file"
fi

mv "$patch_file" "$output_dir"
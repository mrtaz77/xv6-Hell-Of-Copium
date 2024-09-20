#!/bin/bash

cd xv6-riscv || {
	echo "xv6-riscv dir not found!"
	exit 1
}

current_commit=$(git rev-parse HEAD)
current_commit_msg=$(git log -1 --pretty=%s "$current_commit")
echo "Current commit message: $current_commit_msg"

origin_head=$(git rev-parse origin/riscv)

if [ "$current_commit" == "$origin_head" ]; then
	echo "The submodule is already up-to-date. No patch needed."
	exit 0
fi

sanitized_commit_msg=$(echo "$current_commit_msg" | tr ' ' '_' | tr -cd '[:alnum:]_-')

patch_file="${sanitized_commit_msg}.patch"
git diff "$origin_head" "$current_commit" > "$patch_file"

if [ -s "$patch_file" ]; then
	echo "Patch file generated successfully: $patch_file"
else
	echo "No changes detected between the commits."
	rm "$patch_file"
fi

mv "$patch_file" ../Offlines/SystemCall
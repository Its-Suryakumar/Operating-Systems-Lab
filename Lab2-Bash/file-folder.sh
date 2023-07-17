!/bin/bash

path="/path/to/file_or_folder"

if [ -d "$path" ]; then
    echo "It is a directory."
elif [ -f "$path" ]; then
    echo "It is a regular file."
else
    echo "Neither a directory nor a regular file."
fi

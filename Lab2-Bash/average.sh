!/bin/bash

# Array of numbers
numbers=(10 20 30 40 50)

sum=0

# Calculate the sum of all numbers
for number in "${numbers[@]}"; do
    sum=$((sum + number))
done

# Calculate the average
count=${#numbers[@]}
average=$((sum / count))

echo "Average: $average"

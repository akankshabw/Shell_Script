#!/bin/bash

#-------------------------   Question (1)   -----------------------------
# Check if the number of arguments is equal to 2, if not then send error message.
if [ "$#" != 2 ]; then
	echo -e "Oops!!\nThe file can't be accessed....\nThis script can be executed only when two arguments are passed."
	exit 1
fi



#-------------------------   Question (2)   -----------------------------
# Check if the input file exists in the system. If not then send error message. 
if [ ! -e "$1" ]; then
    	echo "There is no file named $1 in our system."
        exit 1
fi



#-------------------------   Question (3)   -----------------------------
# Print all the unique cities in the input file.

echo -e "The unique cities are :\n" >> "$2"
awk -F ',' 'NR > 1 {print $3}' "$1" | sort | uniq >> "$2"
echo -e "----------------------------------------------------------------\n\n" >> "$2"



#-------------------------   Question (4)   -----------------------------
# Sort the input file according to the 4th column that is the salary column and then print the top 3 individuals.

echo -e "The top 3 individuals with highest salary are as follows:\n" >> "$2"
echo -e "Name,  Age, City, Salary\n" >> "$2"
sort -t ',' -k 4 -rn "$1" | head -n 3 >> "$2"
echo -e "----------------------------------------------------------------\n\n" >> "$2"



#-------------------------   Question (5)   -----------------------------
# Find the sum of salaries of all individuals in a city and their number as well. Print the average.
echo -e "The average salaries of all the cities are as follows:\n" >> "$2"

awk -F ',' 'NR > 1 { sum[$3]+=$4; count[$3]++} END { for (city in sum)
{
    avg[city] = sum[city]/count[city]; 
    print "City: "city "    Average Salary: " avg[city];
}}' "$1" | sort -t ',' -k1  >> "$2"
echo -e "----------------------------------------------------------------\n\n" >> "$2"



#-------------------------   Question (6)   -----------------------------
# Extract unique cities from the input file and format as comma-separated list

cities=$(tail -n +2 "$1" | awk -F ',' '{print $3}' | sort | uniq | paste -sd "," -)

IFS=','
echo -e "The individuals with salary greater than the average salary in their respective cities are:\n" >> "$2"
echo -e "Name,  Age, City, Salary\n" >> "$2"
for city in $cities; do
    # Calculate average salary for the current city
    average_salary=$(awk -F ',' -v city="$city" '$3 == city {sum += $4; count++} END {if (count > 0) print sum / count}' "$1")
    
    # Check if the salary of an individual is greater than the average salary of that city and print it.
    awk -F ',' -v city="$city" -v avg="$average_salary" '$3 == city && $4 > avg {print}' "$1" >> "$2"
done
echo -e "----------------------------------------------------------------\n\n" >> "$2"




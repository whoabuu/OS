#!/bin/bash

echo -e "Enter filename: "
read filename
repeat=1

while (( repeat == 1 ))
do
  echo -e "\n\t1. Create book
\t2. Add data
\t3. Display
\t4. Search
\t5. Delete
\t6. Modify\n"

  echo -e "Enter your choice: "
  read choice

  case $choice in
    1)
      touch "$filename"
      echo "File created successfully."
      ;;
      
    2)
      echo -e "Enter Employee ID, Name, City and Phone Number:"
      read empid empname empcity empno
      echo -e "$empid\t$empname\t$empcity\t$empno" >> "$filename"
      echo "Record added successfully."
      ;;
      
    3)
      echo -e "EmpID\tEmpName\tEmpCity\tEmpNo"
      echo "---------------------------------------"
      column -t -s $'\t' "$filename"
      ;;
      
    4)
      echo -e "Enter city or name to search:"
      read search
      if grep -q "$search" "$filename"; then
        echo -e "\nRecord found:"
        grep "$search" "$filename"
      else
        echo -e "\nRecord not found."
      fi
      ;;
      
    5)
      echo -e "Enter name or city to delete record:"
      read key
      grep -v "$key" "$filename" > temp && mv temp "$filename"
      echo "Record deleted successfully (if existed)."
      ;;
      
    6)
      echo -e "Enter old detail (exact match to replace):"
      read old
      echo -e "Enter new detail:"
      read new
      sed -i "s/$old/$new/" "$filename"
      echo "Record modified successfully."
      ;;
      
    *)
      echo "Invalid choice."
      ;;
  esac

  echo -e "\nDo you want to repeat (1/0)? "
  read

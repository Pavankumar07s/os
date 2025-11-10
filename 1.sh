
echo "📘 ADDRESS BOOK"
read -p "Enter file name: " fname

# create file with header
echo -e "ID\tName\tMobile\tSalary\tLocation" > $fname

while true
do
  echo -e "\n1. Create Address Book"
  echo "2. View Address Book"
  echo "3. Add Record"
  echo "4. Delete Record"
  echo "5. Modify Record"
  echo "6. Search Record"
  echo "7. Exit"
  read -p "Enter your choice: " ch

  case $ch in
    1)
      read -p "Enter number of records: " n
      for ((i=1; i<=n; i++)); do
        read -p "ID: " id
        read -p "Name: " name
        read -p "Mobile: " mno
        read -p "Salary: " sal
        read -p "Location: " loc
        echo -e "$id\t$name\t$mno\t$sal\t$loc" >> $fname
      done ;;
    
    2) cat $fname ;;
    
    3)
      read -p "ID: " id
      read -p "Name: " name
      read -p "Mobile: " mno
      read -p "Salary: " sal
      read -p "Location: " loc
      echo -e "$id\t$name\t$mno\t$sal\t$loc" >> $fname ;;
    
    4)
      read -p "Enter ID to delete: " id
      if grep -qw $id $fname; then
        grep -vw $id $fname > temp && mv temp $fname
        echo "Record deleted."
      else
        echo "Record not found!"
      fi ;;
    
    5)
      read -p "Enter ID to modify: " id
      if grep -qw $id $fname; then
        grep -vw $id $fname > temp && mv temp $fname
        read -p "New Name: " name
        read -p "New Mobile: " mno
        read -p "New Salary: " sal
        read -p "New Location: " loc
        echo -e "$id\t$name\t$mno\t$sal\t$loc" >> $fname
        echo "Record modified."
      else
        echo "Record not found!"
      fi ;;
    
    6)
      read -p "Enter ID to search: " id
      if grep -qw $id $fname; then
        grep -w $id $fname
      else
        echo "Record not found!"
      fi ;;
    
    7) echo "Exiting..."; break ;;
    *) echo "Invalid choice!" ;;
  esac
done

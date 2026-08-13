from database import create_tables
from hospital import *

create_tables()

print("===== Hospital Management System =====")

u = input("Username : ")
p = input("Password : ")

if login(u, p):

    while True:

        print("\n1. Add Patient")
        print("2. View Patients")
        print("3. Delete Patient")
        print("4. Exit")

        ch = eval(input("Enter Choice : "))

        if ch == 1:
            add_patient()

        elif ch == 2:
            view_patients()

        elif ch == 3:
            delete_patient()

        elif ch == 4:
            print("Thank You")
            break

        else:
            print("Invalid Choice")

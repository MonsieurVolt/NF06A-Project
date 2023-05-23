from get_data import *
import os

exit = True
print("Welcome to the Schedule App")
fileName = input("Enter the name of the file : ")
ext = fileName.split(".")[1]
if os.path.isfile(fileName) and (ext == "csv" or ext == "xlsx"):
    exit = False
    print("File Found....Reading your data")
    readFiles(fileName)
else:
    print("File not found or does not have a .csv or .xlsx etension")


if not exit:
    # loop for the menu
    while not exit:
        print("\nMenu : \n1) View your data \n2) Modifiate your data \n3) Launch the analyse \n4) Exit...\n")
        choice = int(input("Enter your choice : "))
        if choice == 1:
            print_datas()

        elif choice == 2:
            change_datas()
        elif choice == 3:
            analyse()
        else:
            Exit(fileName)
            exit = True

##
# @file main.py
#
# @brief Main page use to launch the program and handle the main menu


from get_data import *
import os

##
#  bool used to know the state of the program
exit = True

print("Welcome to the Schedule App")
print("The file must be an .xlsx or .csv file")
print("The first task must be on the second row")
print("The file must be as following : \nName        | Release Date| Due Date    | Processing Time\nTask Name   |01/01/2000   | 01/02/2000  | 15")
fileName = input("Enter the name of the file : ")
##
#  get the extension of the input file name
ext = fileName.split(".")[1]
if os.path.isfile(fileName) and (ext == "csv" or ext == "xlsx"):
    exit = False
    print("File Found....Reading your datas")
    readFiles(fileName)
else:
    print("File not found or does not have a .csv or .xlsx etension")


if not exit:
    #  get back to the menu, each time a task in finish
    while not exit:
        print("\nMenu : \n1) View your data \n2) Modifiate your data \n3) Launch the analyse \n4) Exit...\n")

        #  check the input of the user (check the range value and the type)
        while True:
            try:
                ##
                # input of the menu number by the user
                choice = int(
                    input("Enter an integer between 1 and 4 :  "))
                if 1 <= choice <= 4:
                    break
                else:
                    print("The integer must be between 1 and 4")
            except ValueError:
                print("This is not an integer")
        #  execute functions writes in the get_data.py file
        if choice == 1:
            print_datas()

        elif choice == 2:
            change_datas()
        elif choice == 3:
            analyse()
        else:
            Exit(fileName)
            exit = True

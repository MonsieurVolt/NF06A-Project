from get_data import *

print("Welcome to the Schedule App")

print("Reading your data...")

exit = False
# loop for the menu
while not exit:
    print(" Menu : \n 1) View your data \n 2) Modifiate your data \n 3) Launch the analyse \n 4) Exit...")
    choice = int(input("Enter your choice : "))
    if choice == 1:
        print_datas()

    elif choice == 2:
        change_datas()
    else:
        print("Exit...")
        exit = True
dataframe.save("cheat.xlsx")

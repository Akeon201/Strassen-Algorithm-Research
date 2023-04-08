import algorithms as alg

def main():

    while True:
        user_input = input("Please enter a number ranging from 1-3 or type 'exit' to quit:\n1. Brute Force\n2. Strassen\n3. Brute + Strass\n4. All\n")

        if user_input.lower() == "exit":
            print("Exiting...")
            break

        # Add your flags and their corresponding actions here
        elif user_input == "1":
            alg.run_algorithms(user_input)
        elif user_input == "2":
            alg.run_algorithms(user_input)
        elif user_input == "3":
            alg.run_algorithms(user_input)
        elif user_input == "4":
            alg.run_algorithms(user_input)
        else:
            print("Invalid command. Try again.")
    
if __name__ == "__main__":
    main()

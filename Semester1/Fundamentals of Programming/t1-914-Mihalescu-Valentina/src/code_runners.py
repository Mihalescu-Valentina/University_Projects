"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""
from functions import generate_random_number,split_command_params,check_valid_guess,codes_and_runners
from ui import print_win_message_computer,print_function
def command():
    #cmd_dict = {'play': add_command, 'list': list_command, 'eval': eval_command}
    options=[]
    game_status=1
    randnr = generate_random_number()
    while game_status==1:
        # Print calc value & read user input
        user_cmd = input("enter a valid input")
        cmd_word, cmd_params = split_command_params(user_cmd)
        # Parse user command into command word & parameters
        # unpacking the function's return


        try:
                if cmd_word == 'exit':
                    return

                elif cmd_word == None:
                    raise KeyError("Enter a valid input, do not press only the enter key")

                elif cmd_word !='play' and cmd_word!='report':
                    raise KeyError("Bad command")

                elif cmd_params == None:
                    raise KeyError("Enter proper function parameters for each command word")
                elif cmd_word=='play':
                     if cmd_params.isdigit()==True :
                         if check_valid_guess(int(cmd_params))==0:
                             game_status=0
                             computer_won=1
                             print_win_message_computer()
                elif int(cmd_params)==8086:
                    print("this was the generated number for this game")
                    print_function(randnr)
                elif cmd_word=='report' and cmd_params.isdigit()==True:
                    print_function(randnr)
                    print("the codes and the runners in this order are")
                    print_function(codes_and_runners(int(cmd_params),randnr))
                elif cmd_params.isdigit()==False:
                    raise ValueError("The parameters introduced after the command word must be a number of 4 digits")




        except (ValueError, KeyError) as error_message:
                print(str(error_message))


if __name__ == '__main__':
    command()
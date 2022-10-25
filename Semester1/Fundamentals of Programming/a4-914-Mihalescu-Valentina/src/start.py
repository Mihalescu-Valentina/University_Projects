"""
  Start the program by running this module
"""
import copy

from ui import  print_instructions,average_command,min_avg_command,list_command,top_command,print_list_1
from functions import  add_command, insert_command, remove_command, replace_command, split_command_params,tests,undo_command
"""
the function implements the command driven interface
scores-the list of dictionaries containing the grades of every student
cmd_word-a string containing the command word which corresponds to a non-ui function
user_cmd- the string containing both the command word and the parameters(the input from the user)
cmd_param- the string containing the parameters for every functionality 
"""
def command():
    scores = [{"p1": 10, "p2": 9, "p3": 7}, {"p1": 9, "p2": 7, "p3": 2}, {"p1": 6, "p2": 10, "p3": 5},
              {"p1": 4, "p2": 2, "p3": 3}, {"p1": 10, "p2": 5, "p3": 7}, {"p1": 10, "p2": 2, "p3": 8},
              {"p1": 8, "p2": 9, "p3": 7}, {"p1": 10, "p2": 9, "p3": 4}, {"p1": 10, "p2": 10, "p3": 10},
              {"p1": 10, "p2": 5, "p3": 3}]

    # Init a dict with an entry for each correct command
    cmd_dict = {'add': add_command, 'insert': insert_command, 'remove': remove_command,
                'replace': replace_command,
                'list': list_command, 'avg': average_command, 'min': min_avg_command, 'top': top_command,'undo':undo_command}
    print("the list of scores is:")
    print_list_1(scores)
    all_scores=[]
    #all_scores.append(scores[:])
    #lst.append(copy.deepcopy(scores))
    while True:
        # Print calc value & read user input

        user_cmd = input("enter a valid input")

        # Parse user command into command word & parameters
        # unpacking the function's return
        cmd_word, cmd_params = split_command_params(user_cmd)


        if cmd_word == 'exit':
            return
        # Call the correct function for the given command

        if cmd_word==None:
               print("Enter a valid input, do not press only the enter key")
           # elif cmd_word not in cmd_dict and cmd_word.lower()!="undo" :
        elif cmd_word not in cmd_dict:
               raise KeyError("Bad command")
        # except(ValueError, KeyError) as error_message:
        #     print(str(error_message))

        else:
            try:

                if cmd_params == None and cmd_word.lower() != "list" and cmd_word.lower()!="undo":
                    print("Introduce parameters for the desired command")
                    cmd_params = input("Introduce the right list of parameters depending on the command")
                elif cmd_params == None and cmd_word == "list":
                    cmd_params = ' '
                if cmd_word.lower()=="undo":
                      print(cmd_dict[cmd_word](scores,all_scores))


                elif cmd_word.lower()=="avg" or cmd_word.lower()=="min" or cmd_word.lower()=="top":
                    cmd_dict[cmd_word](scores, cmd_params)
                elif cmd_word.lower() == 'add' or cmd_word.lower() == 'insert' or cmd_word.lower() == 'remove' or cmd_word.lower() == 'replace' or cmd_word.lower()=='list':
                    cmd_dict[cmd_word](scores,cmd_params,all_scores)
                  #lst.append(copy.deepcopy(scores))
                  # if cmd_word.lower() == 'add' or cmd_word.lower() == 'insert' or cmd_word.lower() == 'remove' or cmd_word.lower() == 'replace' :
                  #    print("the new list is")
                  #    print_list_1(scores)

            except (ValueError,KeyError) as error_message:
                print(str(error_message))


            # cmd_dict                             -> dictionary of commands
            # cmd_dict[cmd_word]                   -> the function reference that needs to be called
            # cmd_dict[cmd_word](calc, cmd_params) -> actual function call

if __name__ == '__main__':

  print_instructions()
  tests()
  command()


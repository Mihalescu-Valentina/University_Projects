"""
  Write non-UI functions below

"""

"""
getters functions used for security
"""


def get_p1(score):
    return score["p1"]  # getter used for storing the value of p1(numerical value)


def get_p2(score):
    return score["p2"]  # getter used for storing the value of p2(numerical value)


def get_p3(score):
    return score["p3"]  # getter used for storing the value of p2(numerical value)


"""
setters functions used for security
"""


def set_p1(score, grade):
    score["p1"] = grade


def set_p2(score, grade):
    score["p2"] = grade


def set_p3(score, grade):
    score["p3"] = grade


def set_student(scores, k, grade):
    scores[k] = grade


def get_student(scores, k):
    return scores[k]


"""
the function creates a new dictionary coresponding to a new participant
params: p1,p2,p3-natural values
"""


def create_new_participant_entry(p1, p2, p3):
    return {"p1": p1, "p2": p2, "p3": p3}


"""
the function adds a new entry coresponding to a new student at the end of the dictionary
tokens is used for splitting the parameters stored in the variable params
"""


def add_command(scores, params):
    tokens = params.split(' ')

    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")

    for token in tokens:
        token = token.strip()
        if token.isdigit() == False:
            raise ValueError("Enter 3 valid numerical values")
        if int(token) < 0 or int(token) > 10:
            raise ValueError("Enter 3 valid values between 0 and 10")
    new_participant = create_new_participant_entry(int(tokens[0]), int(tokens[1]), int(tokens[2]))
    scores.append(new_participant)


def add_zero(scores):
    extend = create_new_participant_entry(0, 0, 0)
    scores.append(extend)


"""
the function inserts a new entry coresponding to a new student at a desired position stored in tokens[3]
tokens[0]-p1
tokens[1]-p2
tokens[2]-p3
tokens is used for splitting the parameters stored in the variable params
"""


def insert_command(scores, params):
    tokens = params.split(' ')
    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")
    for token in tokens:
        token = token.strip()
    if tokens[3] != "at":
        raise KeyError("Enter the word 'at' after the 3 numerical scores")  # why is not working with keyerror
    for i in range(3):
        if int(tokens[i]) < 0 or int(tokens[i]) > 10:
            raise ValueError("Enter 3 valid values between 0 and 10")
    if int(tokens[len(tokens) - 1]) < 0 or int(tokens[len(tokens) - 1]) >= len(scores):
        raise ValueError("Enter a valid index")

    # add_zero(scores)
    # i = len(scores) - 1
    # while i > int(tokens[4]):
    #     scores[i] = scores[i - 1]
    #     i = i - 1

    #scores[int(tokens[4])] = {"p1": 0, "p2": 0, "p3": 0} #de ce daca nu pun instr asta imi dubleaza insertia stergand totodata o intrare din dictionar
    newscore=create_new_participant_entry(int(tokens[0]),int(tokens[1]),int(tokens[2]))
    scores.insert(int(tokens[4]),newscore)
    # set_p1(scores[int(tokens[4])], int(tokens[0]))
    # set_p2(scores[int(tokens[4])], int(tokens[1]))
    # set_p3(scores[int(tokens[4])], int(tokens[2]))


"""
the function removes one entry coresponding to a new student at the end of the dictionary
params stores the position where the values p1,p2,p3 will be set to 0
"""


def remove_command(scores, params):
    if len(params) == 1:
        if int(params) < 0 or int(params) >= len(scores):
            raise ValueError("Enter a valid position")
        set_p1(scores[int(params)], 0)
        set_p2(scores[int(params)], 0)
        set_p3(scores[int(params)], 0)
    else:
        tokens = params.split(' ')
        if params.find(" ") == -1:
            raise ValueError("Enter the desired numerical values with a space between them")
        for token in tokens:
            token = token.strip()
            if token != "to":
                if int(token) < 0 or int(token) > 10:
                    raise ValueError("Enter 2 valid values between 0 and 10")
        if len(tokens) != 3:
            raise ValueError
        if not tokens[1] == "to":
            raise KeyError

        for i in range(int(tokens[0]), int(tokens[2]) + 1):
            set_p1(scores[i], 0)
            set_p2(scores[i], 0)
            set_p3(scores[i], 0)


"""
the function removes more entries 
tokens is used for splitting the parameters stored in the variable params
tokens[0]-starting position
tokens[1]-ending position
"""

"""
the function replaces one entry from the dictionary 
tokens is used for splitting the parameters stored in the variable params
tokens[0]-the index of the participant
tokens[1]-p1,p2,p3 as a string
tokens[2]-the new score
"""


def replace_command(scores, params):
    tokens = params.split(' ')
    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")
    for token in tokens:
        token = token.strip()
    if int(tokens[0]) < 0 or int(tokens[0]) >= len(scores):
        raise ValueError("Enter a valid index between 0 and 10")
    if tokens[1] != "p1" and tokens[1] != "p2" and tokens[1] != "p3":
        raise ValueError(
            "Enter one of the following words: 'p1', 'p2', 'p3' after one numerical corect numerical value ")
    if tokens[2] != "with":
        raise ValueError("Enter the word 'with' followed by a number between 0 and 10")

    if tokens[1] != 'p1' and tokens[1] != 'p2' and tokens[1] != 'p3':
        raise ValueError("Enter a valid string: p1,p2,p3")
    if int(tokens[3]) < 0 or int(tokens[3]) > 10:
        raise ValueError("Enter a valid score between 0 and 10")

    scores[int(tokens[0])][tokens[1]] = int(tokens[3])


"""
the function calculates the average of the 3 values p1,p2,p3
"""


def calc_average_score(scores, k):
    return (get_p1(scores[k]) + get_p2(scores[k]) + get_p3(scores[k])) / 3


"""
the function lists the participant that check a property: <,>,= 
tokens[0]-'<,>,='
tokens[1]-a numerical value
"""


# the function sorts the dictionary scores descending
# i index,j index
def sort_descending(scores):
    for i in range(len(scores) - 1):
        for j in range(i, len(scores)):
            if calc_average_score(scores, i) < calc_average_score(scores, j):
                aux = get_student(scores, i)
                set_student(scores, i, get_student(scores, j))
                set_student(scores, j, aux)


# the function sorts the dictionary scores ascending
# i index,j index
def sort_ascending(scores):
    for i in range(len(scores) - 1):
        for j in range(i, len(scores)):
            if calc_average_score(scores, i) > calc_average_score(scores, j):
                aux = get_student(scores, i)
                set_student(scores, i, get_student(scores, j))
                set_student(scores, j, aux)


# this function splits the user_cmd

def split_command_params(user_cmd):
    """
    Split the user's command into the command word and a parameters string
    ex:
         add 5, 6, 7  -> ('add', '5, 6, 7')
         insert 5,4,3,2   -> ('insert', '5,4,3,2')
         exit            -> ('exit', None)
    :param user_cmd: Command input by the user
    :return: A tuple of (<command word>, <command params>) in lowercase
    """
    user_cmd = user_cmd.strip()
    tokens = user_cmd.split(maxsplit=1)
    cmd_word = tokens[0].lower() if len(tokens) > 0 else None  # ?:
    cmd_param = tokens[1].lower() if len(tokens) == 2 else None  # ?:

    return cmd_word, cmd_param


####### UI functions#######

# this function lists all the scores
def list_command(scores, params):
    if params == ' ':
        print(scores)
        return  # is this correct? because i put return in a ui function

    tokens = params.split(' ')
    for token in tokens:
        token = token.strip()

    if len(tokens)==1:
            raise ValueError("Enter '>' or '<' after list sorted")

    elif tokens[0] == "sorted" and tokens[1] != '>' and tokens[1] != '<':
            raise ValueError("Enter '>' or '<' ")
    elif tokens[0] == "sorted" and tokens[1] == '<':
            sort_descending(scores)
            print(scores)
    elif tokens[0] == "sorted" and tokens[1] == '>':
            sort_ascending(scores)
            print(scores)


    elif tokens[0] == '>':
            list_greater(scores, int(tokens[1]))
    elif tokens[0] == '<':
            list_less(scores, int(tokens[1]))
    elif tokens[0] == '=':
            list_equal(scores, int(tokens[1]))
    else:
            raise ValueError("Enter one of these symbols: '<' '>' '=' followed by a space and a numerical value")



def list_command_all(scores):
    print(scores)


# this function lists the students with a score less than val(numerical value)
def list_less(scores, val):
    nr = 0
    i = 0
    while i < len(scores):
        if calc_average_score(scores, i) < val:
            print(scores[i])
            nr = nr + 1
        i = i + 1

    if nr == 0:
        print("there are no participants with an average score<the value entered by the user")


# this function lists the students with a score equal to val(numerical value)
def list_equal(scores, val):
    nr = 0
    i = 0
    while i < len(scores):
        if calc_average_score(scores, i) == val:
            print(scores[i])
            nr = nr + 1
        i = i + 1

    if nr == 0:
        print("there are no participants with an average score equal to the value entered by the user")


# this function lists the students with a score greater than val(numerical value)
def list_greater(scores, val):
    nr = 0
    i = 0
    while i < len(scores):
        if calc_average_score(scores, i) > val:
            print(scores[i])
            nr = nr + 1
        i = i + 1

    if nr == 0:
        print("there are no participants with an average score>the value entered by the user")


# the function lists the scores list either ascending or descending
def list_sort_command(scores, params):
    tokens = params.split(' ')
    for token in tokens:
        token = token.strip()
    if tokens[0] != '<' and tokens[0] != '>':
        raise ValueError("Enter a valid sign: < for descending sort, > for ascending sort")
    if tokens[0] == '<':
        sort_descending(scores)
        print(scores)
    elif tokens[0] == '>':
        sort_ascending(scores)
        print(scores)


# this function prints the instructions so the user know what to enter
def print_instructions():
    print("Choose an option:")
    print("- add <P1 score> <P2 score> <P3 score>")
    print("- insert <P1 score> <P2 score> <P3 score> at <position>")
    print("- remove <position>")
    print("- remove <start position> to <end position>")
    print("- replace <old score> <P1 | P2 | P3> with <new score>")
    print("- list")
    print("- list sorted")
    print("- list [ < | = | > ] <score>")
    print("- exit")


##############test functions###############

# this function tests the split_command
def test_split_command_params():
    # assert crashes if False, does nothing if True
    assert split_command_params('exit') == ('exit', None)
    assert split_command_params('eXiT') == ('exit', None)
    assert split_command_params('add 7 4 10') == ('add', '7 4 10')
    assert split_command_params('   ADD    7 4 10   ') == ('add', '7 4 10')
    # This is a bad command, but still should be split
    assert split_command_params('remove_one abcd') == ('remove_one', 'abcd')
    assert split_command_params('  remove_one 7') == ('remove_one', '7')


# this function tests the add comand
def test_add_command():
    scores = []
    params = "10 5 2"
    add_command(scores, params)
    assert scores[0] == {"p1": 10, "p2": 5, "p3": 2}


# this function tests the insert command
def test_insert_command():
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}]
    params = "8 4 5 at 1"
    insert_command(scores, params)
    assert scores[1] == {"p1": 8, "p2": 4, "p3": 5}


# this function tests the remove_one command
def test_remove_command():
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}, {"p1": 1, "p2": 7, "p3": 3},
              {"p1": 3, "p2": 9, "p3": 9}]
    params = "0"
    remove_command(scores, params)
    assert scores[0] == {"p1": 0, "p2": 0, "p3": 0}
    params = "2 to 3"
    remove_command(scores, params)
    assert scores[2] == {"p1": 0, "p2": 0, "p3": 0}
    assert scores[3] == {"p1": 0, "p2": 0, "p3": 0}


# this function tests the replace_command
def test_replace_command():
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}, {"p1": 1, "p2": 7, "p3": 3},
              {"p1": 3, "p2": 9, "p3": 9}]
    params = "2 p3 with 5"
    replace_command(scores, params)
    assert get_p3(scores[2]) == 5


"""
  Write the command-driven UI below
"""


def command_ui():
    scores = [{"p1": 10, "p2": 9, "p3": 7}, {"p1": 9, "p2": 7, "p3": 2}, {"p1": 6, "p2": 10, "p3": 4},
              {"p1": 4, "p2": 2, "p3": 5}, {"p1": 10, "p2": 5, "p3": 7}, {"p1": 10, "p2": 2, "p3": 8},
              {"p1": 8, "p2": 9, "p3": 7}, {"p1": 10, "p2": 9, "p3": 4}, {"p1": 10, "p2": 10, "p3": 10},
              {"p1": 10, "p2": 5, "p3": 3}]

    # Init a dict with an entry for each correct command
    cmd_dict = {'add': add_command, 'insert': insert_command, 'remove': remove_command,
                'replace': replace_command,
                'list': list_command}  # 'list sorted': list_sort_command} pot pune list sorted in dictionarul de comenzi?
    print("the list of scores is:")
    print(scores)
    while True:
        # Print calc value & read user input

        user_cmd = input("enter a valid input")

        # Parse user command into command word & parameters
        # unpacking the function's return
        cmd_word, cmd_params = split_command_params(user_cmd)
        if cmd_word == 'exit':
            return
        # if cmd_word2=="list":
        #     try:
        #         if cmd_params2==None:
        #            list_command_all(scores)
        #     except ValueError as error_message:
        #         print(str(error_message))

        # Call the correct function for the given command

        if cmd_word not in cmd_dict:
            print("Bad command")

        else:
            try:
                if cmd_params == None and cmd_word != "list":
                    print("Introduce parameters for the desired command")
                    cmd_params = input("Introduce the right list of parameters depending on the command")
                elif cmd_params == None and cmd_word == "list":
                    cmd_params = ' '
                cmd_dict[cmd_word](scores, cmd_params)
                if cmd_word.lower() == 'add' or cmd_word.lower() == 'insert' or cmd_word.lower() == 'remove' or cmd_word.lower() == 'replace':
                    print("the new list is")
                    print(scores)
            except (ValueError,KeyError) as error_message:
                print(str(error_message))


            # cmd_dict                             -> dictionary of commands
            # cmd_dict[cmd_word]                   -> the function reference that needs to be called
            # cmd_dict[cmd_word](calc, cmd_params) -> actual function call


if __name__ == '__main__':
    print_instructions()
    test_add_command()
    test_split_command_params()
    test_insert_command()
    test_remove_command()
    test_replace_command()

    command_ui()
#ce inseamna calc[-1] din lecture 3 si la tema 4 cand nu se mai pot face undo-uri inseamna ca lista de note e egala cu cea initiala,nu?
#si cum mai exact se foloseste lambda
#list(filter(lambda s: get_id(s) == id, students))
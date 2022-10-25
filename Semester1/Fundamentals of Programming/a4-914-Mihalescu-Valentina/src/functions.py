"""
  Program functionalities module
"""
import copy

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

def add_command(scores, params,all_scores):
    tokens = params.split(' ')

    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")

    for token in tokens:
        token = token.strip()
        if token.isdigit() == False:
            raise ValueError("Enter 3 valid numerical values")
        if int(token) < 0 or int(token) > 10:
            raise ValueError("Enter 3 valid values between 0 and 10")
    all_scores.append(scores[:])
    new_participant = create_new_participant_entry(int(tokens[0]), int(tokens[1]), int(tokens[2]))
    scores.append(new_participant)

def add_zero(scores):
    extend = create_new_participant_entry(0, 0, 0)
    scores.append(extend)


"""
the function inserts a new entry coresponding to a new student at a desired position stored in tokens[4]
tokens[0]-p1
tokens[1]-p2
tokens[2]-p3
tokens is used for splitting the parameters stored in the variable params
"""
def insert_command(scores, params,all_scores):
    tokens = params.split(' ')
    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")
    for token in tokens:
        token = token.strip()
    if tokens[3] != "at":
        raise KeyError("Enter the word 'at' after the 3 numerical scores")
    for i in range(3):
        if int(tokens[i]) < 0 or int(tokens[i]) > 10:
            raise ValueError("Enter 3 valid values between 0 and 10")
    if int(tokens[len(tokens) - 1]) < 0 or int(tokens[len(tokens) - 1]) >= len(scores):
        raise ValueError("Enter a valid index")
    all_scores.append(scores[:])
    newscore = create_new_participant_entry(int(tokens[0]), int(tokens[1]), int(tokens[2]))
    scores.insert(int(tokens[4]), newscore)

"""
the function removes one entry coresponding to a new student at the end of the dictionary if the length of params is 1
otherwise the function removes more entries from position stored in tokens[0] to position stored in tokens[2]
params stores the position where the values p1,p2,p3 will be set to 0
"""


def remove_command(scores, params,all_scores):
    # if len(params) == 1:
    #     if int(params) < 0 or int(params) >= len(scores):
    #         raise ValueError("Enter a valid position")

    #else:
    # if params.find(" ") == -1:
    #     raise ValueError("Enter the desired numerical values with a space between them")
        tokens = params.split(' ')
        all_scores.append(copy.deepcopy(scores))
        for token in tokens:
            token = token.strip()
        if len(tokens)!=1 and params.find(" ") == -1:
           raise ValueError("Enter the desired numerical values with a space between them")
        if len(tokens)==1:
            if int(tokens[0])<0 or int(tokens[0])>=len(scores):
                raise ValueError("Enter a valid position")
            set_p1(scores[int(tokens[0])], 0)
            set_p2(scores[int(tokens[0])], 0)
            set_p3(scores[int(tokens[0])], 0)
        elif len(tokens)==3:
            if not tokens[1] == "to":
                raise KeyError("Enter the word at after a numerical value followed by a number")
            for i in range(int(tokens[0]), int(tokens[2]) + 1):
                set_p1(scores[i], 0)
                set_p2(scores[i], 0)
                set_p3(scores[i], 0)
        elif len(tokens)==2:
            if tokens[0]!='<' and tokens[0]!='>' and tokens[0]!='=':
                raise ValueError("Enter '<' or '>' or '=' before a numerical value <=10" )
            if tokens[0]=='<':
                for i in range(len(scores)):
                    if calc_average_score(scores,i)<int(tokens[1]):
                        set_p1(scores[i], 0)
                        set_p2(scores[i], 0)
                        set_p3(scores[i], 0)
            elif  tokens[0]=='=':
                for i in range (len(scores)):
                    if calc_average_score(scores,i)==int(tokens[1]):
                        set_p1(scores[i], 0)
                        set_p2(scores[i], 0)
                        set_p3(scores[i], 0)
            elif tokens[0]=='>':
                for i in range (len(scores)):
                    if calc_average_score(scores,i)>int(tokens[1]):
                        set_p1(scores[i], 0)
                        set_p2(scores[i], 0)
                        set_p3(scores[i], 0)

        else:
            raise ValueError("Enter valid paramters for the command")

            # if token != "to":
            #     if int(token) < 0 or int(token) > 10:
            #         raise ValueError("Enter 2 valid values between 0 and 10")



"""
the function replaces one entry from the dictionary 
tokens is used for splitting the parameters stored in the variable params
tokens[0]-the index of the participant
tokens[1]-p1,p2,p3 as a string
tokens[2]-"with"
tokens[3]-the new score
"""


def replace_command(scores, params,all_scores):
    tokens = params.split(' ')
    all_scores.append(scores[:])
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

def sort_p_desc(scores,p,all_scores):
    all_scores.append(scores[:])
    for i in range(len(scores) - 1):
        for j in range(i, len(scores)):
            if p=='p1':
                pi=get_p1(scores[i])
                pj=get_p1(scores[j])
            elif p=='p2':
                pi=get_p2(scores[i])
                pj=get_p2(scores[j])
            elif p=='p3':
                pi=get_p3(scores[i])
                pj=get_p3(scores[j])
            if pi< pj:
                aux = get_student(scores, i)
                set_student(scores, i, get_student(scores, j))
                set_student(scores, j, aux)

# the function sorts the dictionary scores descending
# i index,j index
def sort_descending(scores):
    for i in range(len(scores) - 1):
        for j in range(i, len(scores)):
            if calc_average_score(scores, i) < calc_average_score(scores, j):
                aux = get_student(scores, i)
                set_student(scores, i, get_student(scores, j))
                set_student(scores, j, aux)


# the function sorts the ditionary scores ascending
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
         add 5, 6, 7  -> ('add', '5 6 7')
         insert 5,4,3,2   -> ('insert', '5 4 3 at 2')
         exit            -> ('exit', None)
    :param user_cmd: Command input by the user
    :return: A tuple of (<command word>, <command params>) in lowercase
    """
    user_cmd = user_cmd.strip()
    tokens = user_cmd.split(maxsplit=1)
    cmd_word = tokens[0].lower() if len(tokens) > 0 else None  # ?:
    cmd_param = tokens[1].lower() if len(tokens) == 2 else None  # ?:

    return cmd_word, cmd_param

def elim_entry(lst,index):
    del lst[index]

def undo_command(scores,all_scores):
        l=[]
        try:
          scores=all_scores[-1]
          all_scores.pop(-1)
          #scores=all_
          return scores,"You have successfully returned to the previous step"
        except:
            return "No more undo operations can be performed"

        # elim_entry(lst,len(lst)-1)
        # print(lst)
        # scores[:]=copy.deepcopy(lst[len(lst) - 1])
        #print(scores[:])








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
    all_scores=[]
    add_command(scores, params,all_scores)
    assert scores[0] == {"p1": 10, "p2": 5, "p3": 2}


# this function tests the insert command
def test_insert_command():
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}]
    params = "8 4 5 at 1"
    all_scores=[]
    insert_command(scores, params,all_scores)
    assert scores[1] == {"p1": 8, "p2": 4, "p3": 5}


# this function tests the remove_one command
def test_remove_command():
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}, {"p1": 1, "p2": 7, "p3": 3},
              {"p1": 3, "p2": 9, "p3": 9}]
    params = "0"
    all_scores=[]
    remove_command(scores, params,all_scores)
    assert scores[0] == {"p1": 0, "p2": 0, "p3": 0}
    params = "2 to 3"
    remove_command(scores, params,all_scores)
    assert scores[2] == {"p1": 0, "p2": 0, "p3": 0}
    assert scores[3] == {"p1": 0, "p2": 0, "p3": 0}
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}, {"p1": 1, "p2": 7, "p3": 3},
              {"p1": 3, "p2": 9, "p3": 9}]
    params="< 5"
    remove_command(scores,params,all_scores)
    assert scores[0]== {"p1": 0, "p2": 0, "p3": 0}
    assert scores[2]== {"p1": 0, "p2": 0, "p3": 0}
    params="> 5"
    remove_command(scores,params,all_scores)
    assert scores[1] == {"p1": 0, "p2": 0, "p3": 0}
    assert scores[3] == {"p1": 0, "p2": 0, "p3": 0}
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}, {"p1": 1, "p2": 7, "p3": 3},
              {"p1": 3, "p2": 9, "p3": 9}]
    params="= 7"
    remove_command(scores,params,all_scores)
    assert scores[3] == {"p1": 0, "p2": 0, "p3": 0}



# this function tests the replace_command
def test_replace_command():
    scores = [{"p1": 2, "p2": 5, "p3": 6}, {"p1": 10, "p2": 5, "p3": 2}, {"p1": 1, "p2": 7, "p3": 3},
              {"p1": 3, "p2": 9, "p3": 9}]
    params = "2 p3 with 5"
    all_scores=[]
    replace_command(scores, params,all_scores)
    assert get_p3(scores[2]) == 5

#the function tests the function that sorts asecnding
def test_sort_asc():
    scores=[{'p1':0,'p2':1,'p3':2},{'p1':7,'p2':1,'p3':2}]
    sort_ascending(scores)
    assert scores==[{'p1':0,'p2':1,'p3':2},{'p1':7,'p2':1,'p3':2}]

#test a function that sorts the list descending
def test_sort_desc():
    scores=[{'p1':7,'p2':1,'p3':2},{'p1':0,'p2':1,'p3':2}]
    sort_descending(scores)
    assert scores==[{'p1':7,'p2':1,'p3':2},{'p1':0,'p2':1,'p3':2}]

#the function tests the function that sorts according to a p equal to p1,p2,p3
def test_sort_p():
    p='p1'
    scores = [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3':2 }]
    all_scores=[]
    sort_p_desc(scores,p,all_scores)
    assert scores == [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}]
    p='p2'
    scores = [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}]
    sort_p_desc(scores, p,all_scores)
    assert scores==[{'p1': 0, 'p2': 6, 'p3': 2},{'p1': 7, 'p2': 4, 'p3':10}]
    p='p3'
    scores = [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}]
    sort_p_desc(scores, p,all_scores)
    assert scores == [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}]

#the function tests the undo command
def test_undo():
    # scores= [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3':2 },{'p1': 0, 'p2': 6, 'p3':2 }]
    # lst = copy.deepcopy(scores)
    # params="1 2 4"
    # add_command(copy.deepcopy(scores),params)
    # lst.append(copy.deepcopy(scores))
    # undo_command(lst,copy.deepcopy(scores))
    # assert scores== [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3':2 },{'p1': 0, 'p2': 6, 'p3':2 }]
    #
    # params="2"
    # remove_command(copy.deepcopy(scores),params)
    # lst.append(copy.deepcopy(scores))
    # undo_command(lst,copy.deepcopy(scores))
    # assert scores== [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3':2 },{'p1': 0, 'p2': 6, 'p3':2 }]
    #
    # params="1 1 1 at 1"
    # insert_command(copy.deepcopy(scores), params)
    # lst.append(copy.deepcopy(scores))
    # undo_command(lst, copy.deepcopy(scores))
    # assert scores == [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}, {'p1': 0, 'p2': 6, 'p3': 2}]
    #
    # params="0 p1 with 10"
    # replace_command(copy.deepcopy(scores), params)
    # lst.append(copy.deepcopy(scores))
    # undo_command(lst, copy.deepcopy(scores))
    # assert scores == [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}, {'p1': 0, 'p2': 6, 'p3': 2}]

      scores=[{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3':2 },{'p1': 0, 'p2': 6, 'p3':2 }]
      all_scores=[]
      all_scores.append(scores[:])
      params = "1 2 4"
      add_command(scores,params,all_scores)
      undo_command(scores,all_scores)
      assert all_scores[-1]== [{'p1': 7, 'p2': 4, 'p3': 10}, {'p1': 0, 'p2': 6, 'p3': 2}, {'p1': 0, 'p2': 6, 'p3': 2}]

#the function calls all the test functions from this module
def tests():
    test_add_command()
    test_split_command_params()
    test_insert_command()
    test_remove_command()
    test_replace_command()
    test_sort_asc()
    test_sort_desc()
    test_sort_p()
    test_undo()






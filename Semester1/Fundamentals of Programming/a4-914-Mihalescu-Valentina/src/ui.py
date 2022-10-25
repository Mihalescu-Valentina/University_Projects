"""
  User interface module
"""

from functions import sort_ascending, sort_descending,calc_average_score, add_command, insert_command, remove_command, replace_command, split_command_params,sort_p_desc
# this function lists all the scores if params=' ', prints the sorted list descending if tokens[0]="sorted" and tokens[1]= <
#prints the sorted list ascending if tokens[0]="sorted" and tokens[1]= > and otherwise different value errors are raised
def list_command(scores, params,all_scores):
    if params == ' ':
        print(scores)
        return

    tokens = params.split(' ')
    for token in tokens:
        token = token.strip()

    if len(tokens)==1:
            raise ValueError("Enter '>' or '<' after list sorted or enter spaces between the symbols after list")

    elif tokens[0] == "sorted" and tokens[1] != '>' and tokens[1] != '<':
            raise ValueError("Enter '>' or '<' ")
    elif tokens[0] == "sorted" and tokens[1] == '<':
            all_scores.append(scores[:])
            sort_descending(scores)
            print(scores)
    elif tokens[0] == "sorted" and tokens[1] == '>':
            all_scores.append(scores[:])
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

"""
this function displays the average of a given number of students
tokens-a list of parameters
tokens[0]-the beggining of the interval
tokens[1]-to
tokens[2]-the end of the interval
"""
def average_command(scores,params):
    tokens = params.split(' ')
    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")
    for token in tokens:
        token = token.strip()
    if int(tokens[0]) < 0 or int(tokens[0]) >= len(scores):
        raise ValueError("Enter a valid index between 0 and 10")
    if tokens[1]!="to":
        raise ValueError("Enter the word 'to' after a numerical value")
    if tokens[2].isdigit()==False:
        raise ValueError("Enter a numerical value in the range")
    if int(tokens[len(tokens) - 1]) < 0 or int(tokens[len(tokens) - 1]) >= len(scores):
        raise ValueError("Enter a valid index")
    avg=0
    for i in range(int(tokens[0]),int(tokens[2])+1):
        avg=calc_average_score(scores,i)+avg
    print("The average of the scores for participants between the given positions is")
    print(avg/(int(tokens[2])-int(tokens[0])+1))

"""
this function displays the lowest average scores between 2 given positions
tokens-a list of parameters
tokens[0]-the beggining of the interval
tokens[1]-to
tokens[2]-the end of the interval
"""
def min_avg_command(scores,params):
    tokens = params.split(' ')
    if params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")
    for token in tokens:
        token = token.strip()
    if int(tokens[0]) < 0 or int(tokens[0]) >= len(scores):
        raise ValueError("Enter a valid index between 0 and 10")
    if tokens[1] != "to":
        raise ValueError("Enter the word 'to' after a numerical value")

    if tokens[2].isdigit()==False:
        raise ValueError("Enter a numerical value in the range")
    if int(tokens[len(tokens) - 1]) < 0 or int(tokens[len(tokens) - 1]) >= len(scores):
        raise ValueError("Enter a valid index")
    minavg=11
    for i in range (int(tokens[0]),int(tokens[2])+1):
        if calc_average_score(scores,i)<minavg:
            minavg=calc_average_score(scores,i)
    print("The lowest average score of the participants between the given positions is")
    print(minavg)

"""
this function displays the participants having the highest average score based on a given input
tokens-a list of parameters
top value:
tokens[0]-the number of students in the top
top value grade:
tokens[0]-the number of students in the top
tokens[1]-p1,p2,p3
"""

def top_command(scores,params):
    tokens = params.split(' ')
    for token in tokens:
        token = token.strip()
    if len(tokens)!=1 and params.find(" ") == -1:
        raise ValueError("Enter the desired numerical values with a space between them")

    if len(tokens)==2 and tokens[1]!='p1' and tokens[1]!='p2' and tokens[1]!='p3':
        raise KeyError("Enter p1, p2 or p3 after a numerical value end the command word top")
    if tokens[0].isdigit() == False:
        raise ValueError("Enter a numerical value in the range")
    if int(tokens[0])<1 or int(tokens[0])>len(scores):
        raise ValueError("Enter a valid index")


    aux=scores
    if(len(tokens)==1):
      if len(tokens)==1:
        sort_descending(aux)
        for i in range (int(tokens[0])):
            print(aux[i])
    elif len(tokens)==2:
            sort_p_desc(aux,tokens[1])
            for i in range(int(tokens[0])):
                print(aux[i])








def print_list(scores):
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
    print("- avg <start position> to <end position>")
    print("- min <start position> to <end position>")
    print("- top < number >")
    print("- top < number > < P1 | P2 | P3 >")
    print("- remove [ < | = | >] < score >")
    print("- exit")

#this function lists each student following by a space
def print_list_1(scores):
    for i in range (len(scores)):
        print(scores[i])

import random
"""
this function generates the secret number through a while loop which uses the randint function to generate 
a number of 4 digits which is afterwards checked using // and % for the desired properties
params:
x=the random generated number
ok=variable used in order to stop the programme when the desired number is found
a=the digit coresponding to the units
b=the third digit from left to right
c=the digit coresponding to the thousands
d=the second digit from left to right
"""
def generate_random_number():
    ok=0
    while ok==0:
        x=random.randint(1000,9999)
        a=x%10
        b=x//10%10
        c=x//1000
        d=x//100%10
        if c!=0 and a!=b and a!=c and a!=d and b!=d and b!=c and c!=d:
            ok=1
    return x
def check_valid_guess(x):
    ok=0
    a = x % 10
    b = x // 10 % 10
    c = x // 1000
    d = x // 100 % 10
    if a != 0 and a != b and a != c and a != d and b != d and b != c and c != d:
        ok = 1
    return ok
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

def codes_and_runners(x,y):
    aux2=y
    codes=0
    runners=0
    aux1=x
    while aux2!=0 and aux1!=0:
         if aux1 %10==aux2%10:
            codes=codes+1
         aux1=aux1//10
         aux2=aux2//10

    aux2=y
    aux1=x
    while aux2!=0:
        if aux2%10==aux1%10 or aux2%10==aux1//10%10 or aux2%10==aux1//1000 or aux2%10==aux1//100%10:
            runners=runners+1
        aux2=aux2//10

    return codes,runners

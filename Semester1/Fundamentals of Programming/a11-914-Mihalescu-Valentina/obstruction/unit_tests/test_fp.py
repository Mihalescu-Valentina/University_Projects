def m2():
    a=lambda x: x+1
    b=lambda x: x+[1]
    c= b([2]) #b=[2,1]
    d=[a,b,c]  #d=[a(),b(),[2,1])
    print(a(2),b([2]))
    a=[3,4]
    b=[5,6]
    c=[7,8]
    print(d[0](2))
    print(d[2][0])
m2()
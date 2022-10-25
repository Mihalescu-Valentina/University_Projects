class Container():
    class IteratorObject:
        def __init__(self, my_container):
            self.__my_container = my_container
            self.__keys = list(self.__my_container.keys())
            self.__key_pos = 0

        def __next__(self):
            if self.__key_pos == len(self.__my_container):
                raise StopIteration

            self.__key_pos = self.__key_pos + 1
            return self.__keys[self.__key_pos - 1]

    def __init__(self):
        self._dict = dict()

    def keys(self):
        return self._dict.keys()

    def __len__(self):
        return len(self._dict)

    def __setitem__(self, key, value):
        self._dict[key] = value

    def __getitem__(self, index):
        return self._dict[index]

    def __delitem__(self, key):
        del self._dict[key]

    def __iter__(self):
        return self.IteratorObject(self)  # self=object of type my container (an instance of type Container)

    def values(self):
        return self._dict.values()


def comb_sort(my_list, func=lambda x, y: x < y):
    def getNextGap(gap):
        gap = (gap * 10) / 13
        if gap < 1:
            return 1
        return gap

    gap = len(my_list)

    # Initialize ok as true
    ok = True

    # Keep running while gap is more than 1 and last
    # iteration caused a swap
    while gap != 1 or ok == True:

        # Find next gap
        gap = int(getNextGap(gap))

        # Initialize ok as false so that we can
        # check if ok happened or not
        ok = False

        # Compare all elements with current gap
        for i in range(0, len(my_list) - gap):

            if func(my_list[i],my_list[i+1]) == False:
                my_list[i],my_list[i+1]=my_list[i+1],my_list[i]
                ok = True
    return my_list

def my_filter(my_list,func):    #there is no default for filter
       new_list=[]
       for elem in my_list:
           if func(elem) is True:
              new_list.append(elem)
       return new_list






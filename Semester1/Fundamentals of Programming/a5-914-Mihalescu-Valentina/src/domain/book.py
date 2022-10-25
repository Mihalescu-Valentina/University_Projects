class Book:
    def __init__(self, isbn, author, title):
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    @property
    def isbn(self):
        return self.__isbn

    @isbn.setter
    def isbn(self, code):
        self.__isbn = code

    @property
    def author(self):
        return self.__author

    @author.setter
    def author(self, name):
        self.__author = name

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, name):
        self.__title = name

    #this functions displays the attributes of a class
    def __str__(self):
        return f"ISBN: {self.__isbn }, Author: {self.__author}, Title: {self.__title}"


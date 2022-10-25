from src.domain.book import Book
from src.domain.validators import BookValidator
from copy import deepcopy
import random

class BookService:
    #i initialised a list of 14 objects(books) from which using random.sample the functions chooses 10 random entries
    #__operation_stack used for undo
    def __init__(self):
        self.__books_list = random.sample([Book('14-39', 'Rick Riordan', 'Kane Chronicles'), Book('27-44', 'Rick Yancey', 'The 5th Wave'),
             Book('11-13', 'Jules Verne', 'Two Years Vacation'),Book('25-42', 'Rick Riordan', 'The Lightning Thief'),
             Book('79-97', 'Lev Tolstoy', 'Anna Karenina'), Book('12-60','Ionel Teodoreanu','La Medeleni'),
             Book('12-78', 'Rick Riordan', 'Magnus Chase'), Book('44-46','Franz Kafka','Procesul'),Book('34-90','Stephen King','Pet Semetary'),
             Book('10-40','Millie Bobby','Horse'),Book('20-80','Rudiard Kipling','Jungle Book'),Book('56-89','Anne Cuthbert','Anne with an E'),
             Book('34-90','Duffer Brothers','Stranger Things')], 10)
        self.__operations_stack = []

    #getter for the list of books
    @property
    def books_list(self):
        """
        :return: the list of the books
        """
        return self.__books_list

    #setter for the list of books
    @books_list.setter
    def books_list(self, updated_list):
        """
        It sets the list of the book with the given one.
        :param updated_list: the list of books that has to be set
        """
        self.__books_list = updated_list

    #getter for the stack used for undo
    @property
    def operations_stack(self):
        """
        :return: the list with all the previous status of the books list
        """
        return self.__operations_stack

    #setter for the undo stack
    @operations_stack.setter
    def operations_stack(self, updated_list):
        """
        It sets the list of previous operations to the given list
        :param updated_list: the list of operations that has to be set
        """
        self.__operations_stack = updated_list

    def add_book(self, isbn, author, title):
        """
        I instantiate a new book and add it to the list.
        :param isbn: the International Standard Book Number of the book
        :param author: the author of the book
        :param title: the title of the book
        """
        new_book = Book(isbn, author, title)
        validator = BookValidator()
        validator.is_element_string(isbn)
        validator.is_element_string(title)
        # validator.is_title_valid(title)
        validator.is_element_string(author)
        validator.isbn_is_valid(isbn)
        validator.isbn_is_unique(isbn, self.__books_list)
        self.__books_list.append(new_book)

    def filter_books_list_by_word(self, word):
        """
        It filters the lift of books by removing the objects whose titles begin with the given word
        :param word: string representing the search word in the begging of the title
        -the filter will apply the condition from the left to the __books_list so the list
          will only contain entries which do not have titles that beggin with the given 'word'
        """
        self.__books_list = list(filter(lambda book: word not in book.title[:book.title.find(" ")], self.__books_list))



    def save_current_list_status(self):
        """
        It saves the status of the current list of books.
        """
        self.__operations_stack.append(deepcopy(self.__books_list))


    def undo_last_operation(self):
        """
        It undoes the last operation.
        """
        if len(self.__operations_stack):
            previous_list = self.__operations_stack[-1]
            self.__books_list = deepcopy(previous_list)
            self.__operations_stack.pop(-1)
        else:
            print("No more undo operations can be performed")



def to_test_add_operation_errors():
    book_service = BookService()
    # the book is added successfully if isbn is unique
    try:
        book_service.add_book('44-55', 'author', 'title')
        assert True
    except ValueError:
        assert False

    # an exception is raised if the isbn is not unique
    try:
        book_service.add_book('445', 'author', 'title')
        assert False
    except ValueError:
        assert True

#the function tests the add functionality
def test_add():
      book_service=BookService()
      book_service.add_book('89-00','Autor','Titlu')
      list_elements=book_service.books_list
      last_element=book_service.books_list[len(list_elements)-1]
      assert last_element.title=='Titlu'
      assert last_element.isbn=='89-00'
      assert last_element.author=='Autor'

#The function tests the filter functionality
def test_filter():
    book_service=BookService()
    book_service.add_book('89-90','Blue','Autor Titlu')
    book_service.add_book('11-99','Miriam Leon','Carte')
    book_service.add_book('22-00','Lili','Autor Info')
    book_service.filter_books_list_by_word('Autor')
    list_elements=book_service.books_list
    assert book_service.books_list[len(list_elements)-1].author=='Miriam Leon'
    assert book_service.books_list[len(list_elements)-1].title=='Carte'
    assert book_service.books_list[len(list_elements)-1].isbn=='11-99'


#the function tests the undo functionality
def test_undo():
    book_service=BookService()
    book_service.save_current_list_status()
    book_service.add_book('11-99', 'Miriam Leon','Carte')
    book_service.save_current_list_status()
    book_service.add_book('56-09','Lylian Viv','Blue')
    # book_service.save_current_list_status()
    book_service.undo_last_operation()
    list_elements=book_service.books_list
    assert book_service.books_list[len(list_elements) - 1].author == 'Miriam Leon'
    assert book_service.books_list[len(list_elements) - 1].title == 'Carte'
    assert book_service.books_list[len(list_elements) - 1].isbn == '11-99'
    book_service.save_current_list_status()
    book_service.add_book('11-11', 'Lili Didi', 'Mimi')
    book_service.save_current_list_status()
    book_service.add_book('45-69','Avram Anca','Carte de povesti')
    book_service.save_current_list_status()
    book_service.filter_books_list_by_word('Carte')
    book_service.undo_last_operation()
    assert book_service.books_list[len(list_elements) - 1].author == 'Avram Anca'
    assert book_service.books_list[len(list_elements) - 1].title == 'Carte de povesti'
    assert book_service.books_list[len(list_elements) - 1].isbn == '45-69'






to_test_add_operation_errors()
test_add()
test_filter()
test_undo()

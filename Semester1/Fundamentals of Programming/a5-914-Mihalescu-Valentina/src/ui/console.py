from src.services.book_service import BookService


class Console:
    def __init__(self):
        self.__book_service = BookService()

    @staticmethod
    def display_menu():
        print("Options: ")
        print("add - add a new book to the list")
        print("list - display the list of the books")
        print("filter - remove the books for which the titles start with a given word")
        print("undo - undo the last operation")
        print("x - exit")

    def read_input(self):
        self.display_menu()
        while True:
            option = input("Enter option: ").lower().strip()

            try:
                if option == 'x':
                    break
                self.execute_user_command(option)
            except KeyError as error_message:
                print(str(error_message))

    def display_list(self):
        for book in self.__book_service.books_list:
            print(str(book))

    def execute_user_command(self, option):
        if option not in ['add', 'filter', 'list', 'undo']:
            raise KeyError('Enter a valid option!')
        if option == 'add':
            book_isbn = input("Isbn: ")
            if book_isbn == '':
                raise KeyError("Enter a valid isbn not a space")
            book_author = input("Author: ")
            if book_author == '':
                raise KeyError("Enter a valid author not a space")
            book_title = input("Title: ")
            if book_title == '':
                raise KeyError("Enter a valid title not a space")
            self.__book_service.save_current_list_status()
            try:
                self.__book_service.add_book(book_isbn, book_author, book_title)
            except (ValueError,KeyError) as error_message:
                print(str(error_message))
        elif option == 'filter':
            word = input("Word: ")
            self.__book_service.save_current_list_status()
            self.__book_service.filter_books_list_by_word(word)
        elif option == 'list':
            self.display_list()
        elif option == 'undo':
            self.__book_service.undo_last_operation()


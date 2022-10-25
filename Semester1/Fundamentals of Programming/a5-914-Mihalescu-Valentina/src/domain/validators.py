class BookValidator:
    def isbn_is_unique(self, isbn, books_list):
        for book in books_list:
            if isbn == book.isbn:
                raise ValueError("A book with this ISBN already exists.")

    #the function checks if element_to_check which is going to be a either the title,the author,the isbn is a string
    def is_element_string(self,element_to_check):
            if not isinstance(element_to_check,str):
                raise KeyError("Enter a string")


   #the function checks if the isbn respects the form 'ab-cd' a,b,c,d digits
    def isbn_is_valid(self,isbn):
        if len(isbn)!=5:
            raise ValueError("The isbn must have 5 characters ab-cd")
        if isbn[2]!='-':
            raise ValueError("Introduce the isbn in the desired format 'ab-cd' a,b,c,d digits")
        if isbn[0].isdigit()==False or isbn[1].isdigit()==False or isbn[3].isdigit()==False or isbn[4].isdigit()==False:
            raise ValueError("Introduce 2 digits followed by - then another 2 digits")

#ui->service->domain



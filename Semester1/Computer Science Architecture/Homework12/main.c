#include <stdio.h>
/*
29. Read a sentence from the keyboard. Count the letters from each word and print the numbers on the screen.
*/
void cnt_word_letters(char []);
int main()
{
    char s[101];
    printf("\nEnter sequence: ");
    fgets(s,101,stdin); //this function reads from the stream(keyboard-stdin-standard input) and stores the data into the string s with a maximum length of 101 characters
    cnt_word_letters(s);
	return 0;
}

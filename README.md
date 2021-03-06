# Text-Editor
The program simulates the working of a regular text editor by using some of the basic data structures.


Problem Definition:
The assignment nurtures a good understanding and implementation skills of linked lists.
It is an implementation of a text editor using linked lists. The text is essentially lists of characters,
where each list is a line in the text and a line is a sequence of characters terminated by a newline character.
The whole text could be represented as a doubly-linked list of lines and each line as a doubly-linked list of characters with each character
as a node. The editor has a single cursor at any place in the text including a blank line (a blank line has a newline character because every 
line has a newline character at the end; so a blank line is not really blank). When a new empty text is created,
it is created with an empty line and the cursor is at the beginning of the text, that is, at the newline character of the only empty line.
Text always has at least one line. A character is any displayable ASCII character except the newline character 
(ASCII code of newline character is 13, whereas displayable ASCII characters starts from 32). The editor can take the following operations.


Operations:
“Insert” a character before the cursor.
“Enter” (i.e. create) a new line and the cursor moves to the new line. If the cursor was at the end of line, a new empty line is created, 
 otherwise the current line is split into a new line starting from the character at the cursor.
“Delete” a character at the cursor, or the end of line if the cursor is at the end of a line.
 Deleting an end of line is essentially concatenating the next line with the current line.
 No operation if the cursor is at the end of line of the last line.
Move the cursor “Left” by a character (or to the end of line of above line if the cursor is at the beginning of a line). No operation if the cursor is the beginning of the first line.
Move the cursor “Down” to the below line (beginning of the below line). No operation if the cursor is already at the last line.
Move the cursor “Up” to the above line (beginning of the above line). No operation if the cursor is already at the first line.
Move the cursor “Right” by a character (or to the beginning of below line if the cursor is at the end of a line). No operation if the cursor is the end of line of the last line.
Move the cursor to “Home”, that is, beginning of the current line. No operation if the cursor is at the beginning of a line.
Move the cursor to “End”, that is, end of line the current line. No operation if the cursor is at the end of a line.
“Print Line” prints the current line.
“Print Text” prints the whole text.
“Quit” from the text editor.



Input Format
Sequence of operations one per line and the program terminates on the “Quit” operation. An operation is on a new line starting with the
 operation code given above, and any data needed for the operation separated by a space. Only “Insert” operation needs an extra information.


Output Format
Only operations with code 10 and 11 can print. These operations starts printing on a new line.


Constraints
Not more than a million operations before “Quit” operation.


Sample Input 1
I a
P
I b
I  
I c
P
I d
P
Q


Sample Output 1
a
ab c
ab cd


Sample Input 2
I D
I e
I a
I r
I  
I S
I t
I u
I d
I e
I n
I t
I s
I ,
P
N
P
N

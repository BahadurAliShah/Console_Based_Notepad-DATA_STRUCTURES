# Console_Based_Notepad-DATA_STRUCTURES
  Create a notepad that allows the user to write text (char by char) on the console. For this
purpose, the user should be able to control and track the movement of the cursor. The user
should be able to navigate to any part of console (cursor control) in order to perform any
insertion or deletion of words.
Internally, the notepad is composed of two-dimensional linked list (every node should
comprise of data element (char) and 4 pointers for navigating left, right, up, and down). Since
text can be written on multiple lines, each row of the 2D linked list represents one line. Each
line is terminated when a newline is inserted in the ADT.

# Functionality of Console based Notepad Application:
• Upon execution, the program should display a menu prompting the user to either
create a new text file or load an existing text file onto 2D linked list.
• To delete text, user would press "Backspace" button.
• To quit notepad, user would press “Esc” button. Program should ask user to enter
name/path of the file. And save 2D linked list contents onto text file.
• Cursor movement would be done using Arrow keys (↑↓←→).
• For newline use “Enter” button.
o If cursor is end of row(line) and “Enter” button pressed, cursor must be moved
to next line.
o If cursor is middle of row(line) and “Enter” button pressed, cursor must be
moved to next line along with remain text of line.

o “Enter” button pressed multiple times will produce empty lines.

• To add or delete some text (char by char), the user can take the cursor to that location
(using the arrow keys) and perform the required operation (to insert or to delete the
character). Insertion, deletion, updating & cursor movement functionality should be
exactly similar to that of Notepad application (cursor should not move beyond text
area).

o Inserting text in 2D Linked List. Inserting in Start, End & Middle of each line. It
should also insert lines between lines.

o Deletion in 2D Linked List. deletion in Start, End & Middle of each line. It should
also delete lines between lines.

• If you close the program, you should free up all memory occupied by linked list.

#include <Windows.h>
#include <iostream>
#include<fstream>
using namespace std;

class character
{
public:
	char data;
	character* upper;
	character* lower;
	character* left;
	character* right;
	character()
	{
		data = '\0';
		upper = left = right = lower = nullptr;
	}
};
//=================================================================
class LinkedRows
{
	int total_chars;
public:
	character* head;
	LinkedRows()
	{
		head = nullptr;
		total_chars = 0;
	}
	void insertAt(char val, int x)
	{
		if (head && x > 1)
		{
			character* temp = head;
			int i = 1;
			for (i = 1; i < x - 1; i++)
			{
				temp = temp->right;
			}
			if (temp)
			{
				character* temp_ptr = new character;
				temp_ptr->data = val;
				temp_ptr->right = temp->right;
				if (temp->right)
				{
					temp->right->left = temp_ptr;
				}
				temp->right = temp_ptr;
				temp_ptr->left = temp;
			}
		}
		else if (!head && x == 1)
		{
			head = new character;
			head->data = val;
		}
		else
		{
			character* temp = new character;
			temp->data = val;
			temp->right = head;
			head->left = temp;
			head = temp;
		}
		total_chars++;
	}

	void deleteAt(int x)
	{
		character* temp = head;
		if (x == 2)
		{
			head = head->right;
			total_chars--;
			if (head && head->right)
			{
				head->right->left = nullptr;
			}
		}
		else if (x > 2)
		{
			for (int i = 1; i < x - 2 && temp; i++)
				temp = temp->right;
			if (temp)
			{
				character* temp_ptr = temp->right;
				temp->right = temp->right->right;
				if (temp->right)
					temp->right->left = temp;
				delete temp_ptr;
				total_chars--;
			}
		}
	}

	char get(int x)
	{
		character* temp = head;
		for (int i = 1; i < x; i++)
		{
			temp = temp->right;
		}
		return temp ? temp->data : '\0';
	}

	int getTotalChars()
	{
		return total_chars;
	}

	character* returnNext(int x)
	{
		character* temp = head;
		for (int i = 1; i < x && temp; i++)
			temp = temp->right;
		return temp;
	}

	~LinkedRows()
	{

	}
};

//--------------------------------------------------------------
class RowsOfRows
{
	LinkedRows** rows;
	int total_rows;
public:
	RowsOfRows()
	{
		total_rows = 1;
		rows = new LinkedRows * [total_rows];
		*rows = new LinkedRows;
	}

	void insertAt(char val, int x, int y)
	{
		if (total_rows < y)
		{
			this->newRow(y);
		}
		rows[y - 1]->insertAt(val, x);

		character* temp = returnNext(x, y);
		if (y - 1)
		{
			if (x <= rows[y - 1]->getTotalChars())
				temp->upper = returnNext(x, y - 1);
			else
				temp->upper = nullptr;
		}

		if (y < total_rows - 1)
		{
			if (x <= rows[y + 1]->getTotalChars())
				temp->lower = returnNext(x, y + 1);
			else
				temp->lower = nullptr;
		}
	}

	void deleteAt(int x, int y)
	{
		if (x > 1)
		{
			rows[y - 1]->deleteAt(x);
			character* temp = returnNext(x, y);
			if (y - 1)
			{
				if (x <= rows[y - 1]->getTotalChars())
					temp->upper = returnNext(x, y - 1);
				else
					temp->upper = nullptr;
			}

			if (y < total_rows - 1)
			{
				if (x <= rows[y + 1]->getTotalChars())
					temp->lower = returnNext(x, y + 1);
				else
					temp->lower = nullptr;
			}
		}
		else
		{
			if (y > 1)
			{
				int total = rows[y - 1]->getTotalChars();
				for (int i = 0; i < total; i++)
				{
					rows[y - 2]->insertAt(rows[y - 1]->get(i + 1),
						rows[y - 2]->getTotalChars() + 1);
				}
				LinkedRows** temp = new LinkedRows * [total_rows - 1];
				for (int i = 0; i < total_rows; i++)
				{
					if (i < y - 1)
					{
						temp[i] = rows[i];
					}
					else if (i >= y)
					{
						temp[i - 1] = rows[i];
					}
				}
				delete[]rows;
				rows = temp;
				total_rows--;
			}
		}
	}

	int newRow(int y)
	{
		total_rows++;
		LinkedRows** temp = new LinkedRows * [total_rows];
		if (rows)
		{
			for (int i = 0; i < total_rows; i++)
			{
				if (i < y - 1)
					temp[i] = rows[i];
				else if (i >= y)
					temp[i] = rows[i - 1];
			}
			delete[]rows;
		}
		temp[y - 1] = new LinkedRows;
		rows = temp;
		return total_rows;
	}

	character* returnNext(int x, int y)
	{
		return rows[y - 1]->returnNext(x);
	}

	int getTotalRows()
	{
		return total_rows;
	}

	int getTotalChars(int y)
	{
		return rows[y - 1]->getTotalChars();
	}

	//File Handling
	//Writing Function

	void writeToFile(char* pointer)
	{
		std::fstream output(pointer, std::ios::out);
		if (output.fail())
		{
			std::cout << "Error in opening the file.\n";
			return;
		}
		else
		{
			for (int i = 0; i < total_rows; i++)
			{
				character* temp = rows[i]->returnNext(1);
				while (temp)
				{
					output.put(temp->data);
					temp = temp->right;
				}
				if (i + 1 < total_rows)
					output.put('\n');
			}
		}
		output.close();
	}
	void readFromFile(char* pointer)
	{
		std::fstream fin(pointer, std::ios::in);
		if (fin.fail())
		{
			std::cout << "file not found.\n";
		}
		else
		{
			int x = 1, y = 1;
			while (!fin.eof())
			{
				if (y - 1)
					newRow(y);
				x = 1;
				char reader = fin.get();
				while (reader != '\n' && !fin.eof())
				{
					rows[y - 1]->insertAt(reader, x);
					reader = fin.get();
					x++;
				}
				y++;
			}
		}
		fin.close();
	}

	void enter(int x, int y)
	{
		newRow(y + 1);
		character* temp = returnNext(x, y);
		for (int i = 1; temp; i++)
		{
			insertAt(temp->data, i, y + 1);
			temp = temp->right;
		}
		temp = returnNext(x, y);
		for (int temp_x = getTotalChars(y); temp_x >= x; temp_x--)
		{
			deleteAt(temp_x + 1, y);
		}
	}
};

//-----------------------------------------------------------------
inline void
fileInput(RowsOfRows* manager)
{
	cout << "Press y or Y If you want to read from file: ";
	char temp;
	cin >> temp;
	if (temp == 'y' || temp == 'Y')
	{
		cout << "Enter the name of file: ";
		char* pointer = new char[50];
		cin >> pointer;
		manager->readFromFile(pointer);
		delete[]pointer;
	}
}

inline void
Save(RowsOfRows* manager)
{
	system("cls");
	cout << "If you want to Save Press y or Y: ";
	{
		char temp;
		cin >> temp;
		if (temp == 'y' || temp == 'Y')
		{
			cout << "Enter the name of file: ";
			char* pointer = new char[50];
			cin >> pointer;
			manager->writeToFile(pointer);
			delete[]pointer;
		}
	}
}

inline void
gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline void
Screen(RowsOfRows* manager)
{
	system("cls");
	for (int y = 1; y <= manager->getTotalRows(); y++)
	{
		gotoxy(1, y);
		character* temp = manager->returnNext(1, y);
		while (temp)
		{
			cout << temp->data;
			temp = temp->right;
		}
	}

}

//----------------------------------------------------------------------------
int
main(int argc, char* argv[])
{

	system("cls");
	HANDLE rhnd = GetStdHandle(STD_INPUT_HANDLE);	// handle to read console

	DWORD Events = 0;		// Event count
	DWORD EventsRead = 0;		// Events read from console
	RowsOfRows manager;

	bool Running = true;

	int x = 1, y = 1;
	gotoxy(x, y);

	fileInput(&manager);
	Screen(&manager);
	//programs main loop
	while (Running)
	{

		// gets the systems current "event" count
		GetNumberOfConsoleInputEvents(rhnd, &Events);

		if (Events != 0)
		{			// if something happened we will handle the events we want

		  // create event buffer the size of how many Events
			INPUT_RECORD eventBuffer[200];

			// fills the event buffer with the events and saves count in EventsRead
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

			// loop through the event buffer using the saved count
			for (DWORD i = 0; i < EventsRead; ++i)
			{

				// check if event[i] is a key event && if so is a press not a release
				if (eventBuffer[i].EventType == KEY_EVENT
					&& eventBuffer[i].Event.KeyEvent.bKeyDown)
				{


					// check if the key press was an arrow key
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{

					case VK_UP:	//up
						if (y > 1)
						{
							y--;
							if (x > manager.getTotalChars(y))
								x = manager.getTotalChars(y) + 1;

							gotoxy(x, y);
						}
						break;
					case VK_DOWN:	//down
						if (y < manager.getTotalRows())
						{
							y++;
							if (x > manager.getTotalChars(y))
								x = manager.getTotalChars(y);

							gotoxy(x, y);
						}
						break;
					case VK_RIGHT:	//right
						if (x <= manager.getTotalChars(y))
						{
							x++;
						}
						else if (y < manager.getTotalRows())
						{
							x = 1;
							y++;
						}
						gotoxy(x, y);
						break;
					case VK_LEFT:	//left
						if (x > 1)
							x--;
						else if (y > 1)
						{
							y--;
							x = manager.getTotalChars(y) + 1;
						}
						gotoxy(x, y);

						break;
					default:
					{
						switch (eventBuffer->Event.KeyEvent.uChar.AsciiChar)
						{
						case 27:
							Save(&manager);
							exit(1);
						case 13:
							manager.enter(x, y);
							x = 1;
							y++;
							Screen(&manager);
							gotoxy(x, y);
							break;
						case 8:
							if (x >= 2)
							{
								manager.deleteAt(x, y);
								x -= 1;
							}
							else if (y >= 2)
							{
								x = manager.getTotalChars(y - 1) + 1;
								manager.deleteAt(1, y);
								y--;
							}
							Screen(&manager);
							gotoxy(x, y);
							break;
						default:
							manager.insertAt(eventBuffer->Event.KeyEvent.
								uChar.AsciiChar, x, y);
							Screen(&manager);
							x++;
							gotoxy(x, y);
						}
					}

					}
				}

			}			// end EventsRead loop

		}

	}				// end program loop

	return 0;
}
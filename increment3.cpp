#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>

using namespace std;

void search();
void fileSearch(string, string);
void fileSearch2(string, string, string);




int main(int argc, char* argv[])
{

	if (argc == 1)
	{
		search();
	}

	else if (argc == 3)
	{
		fileSearch(argv[1], argv[2]);

	}
	
	else if (argc == 4)
	{
		if ((argv[1])[0]!='-' || (argv[1])[1]!='o')
		{
			cout << "Invalid argument \"" << argv[1] << "\" discarded." << endl;

			fileSearch(argv[2], argv[3]);
		}

		else
		{
			fileSearch2(argv[1], argv[2], argv[3]);

		}
	}

	else
	{
		cout << "Invalid argument. \"" << argv[1] << "\" discarded." << endl;
	}





	return 0;
}













void search()
{
	string file, searchTerm;

	while (file.length() < 1)
	{
		cout << "Give a string from which to search for: ";
		getline(cin, file);
	}

	while (searchTerm.length() < 1)
	{
		cout << "Give search string: ";
		getline(cin, searchTerm);
	}

	size_t found = file.find(searchTerm);


	if (found == string::npos)
	{
		cout << "\"" << searchTerm << "\" NOT found in \"" << file << "\"";
	}
	else
	{
		cout << "\"" << searchTerm << "\" found in \"" << file << "\" in position " << found;
	}
}










void fileSearch(string searchTerm, string fileName)
{
	string text;
	ifstream reader;
	size_t found;


	reader.open(fileName);


	if (!reader)
	{
		cout << endl << fileName << " was not found. Check filename and location." << endl;
		exit(1);
	}

	while (getline(reader, text))
	{

		found = text.find(searchTerm);


		if (found != string::npos)
		{
			cout << text << endl;
		}

	}


	reader.close();

}

void fileSearch2(string options, string searchTerm, string fileName)
{
	string text;
	ifstream reader;
	size_t found;
	int lineNumbering = 0, occurrences = 0;


	reader.open(fileName);

	options.erase(0, 2);






	if (!reader)
	{
		cout << endl << fileName << " was not found. Check filename and location." << endl;
		exit(1);
	}

	while (getline(reader, text))
	{
		
		found = text.find(searchTerm);

		lineNumbering++;


		if (found != string::npos)
		{
			if ((options.find('l')) != string::npos)

			{
				cout << lineNumbering << ":" << text << endl;

			}

			else
			{
				
				cout << text << endl;

			}


			occurrences++;

		}

	}


	reader.close();

	if ((options.find('o')) != string::npos)
	{
		cout << endl <<  "Occurrences of lines containing \"" << searchTerm << "\": " << occurrences;
	
	}
}
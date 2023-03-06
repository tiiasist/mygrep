#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>

using namespace std;

void search();
void fileSearch(string, string);



int main(int argc, char *argv[])
{

	if (argc == 1)
	{
		search();
	}

	else if (argc == 3)
	{
		fileSearch(argv[1], argv[2]);

	}

	else
	{
		cout << "Invalid argument \"" << argv[1] << "\" discarded." << endl;
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

void fileSearch(string searchTerm ,string fileName)
{
	string text;
	ifstream reader; 
	size_t found;


	reader.open(fileName);


	if (!reader)
	{
		cout <<endl << fileName << " was not found. Check filename and location." << endl;
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
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

void search();


int main()
{

	search();





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
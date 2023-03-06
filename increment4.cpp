#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>

using namespace std;

// FUNKTIOIDEN PROTOTYYPIT
//--------------------------------------------------------------
void search();
void fileSearch(string, string);
void fileSearch2(string, string, string);
string caseIgnore(string);



// PÄÄOHJELMA - Tarkistetaan komentorivillä syötetyiden argumenttien määrä ja kutsutaan oikeaa aliohjelmaa määrän perusteella

//--------------------------------------------------------------

int main(int argc, char* argv[])
{

	if (argc == 1)		// Jos argumenttejä on vain yksi, kutsutaan search-aliohjelmaa, joka vastaa increment 1:tä
	{
		search();
	}

	else if (argc == 3)			// Jos argumenttejä on kolme, kutsutaan fileSearch-aliohjelmaa
	{
		fileSearch(argv[1], argv[2]);

	}

	else if (argc == 4)			// Jos argumenttejä on neljä, kutsutaan fileSearch-aliohjelmaa
	{
		if ((argv[1])[0] != '-' || (argv[1])[1] != 'o')
		{
			cout << "Invalid argument \"" << argv[1] << "\" discarded." << endl;		// Poikkeuskäsittely tarkistaa alkaako toinen argumentti merkit - ja o. Jos merkkejä ei löydy, antaa ohjelma virheilmoituksen ja kutsuu fileSearch-aliohjelmaa

			fileSearch(argv[2], argv[3]);
		}

		else
		{
			fileSearch2(argv[1], argv[2], argv[3]);		// Jos merkit - ja o löytyvät, kutsutaan aliohjelmaa fileSearch2

		}
	}

	else
	{
		cout << "Invalid argument. \"" << argv[1] << "\" discarded." << endl;	// Jos komentorivillä on annettu virheellisiä argumenttejä, antaa ohjelma virheilmoituksen ja ohjelma sulkeutuu. 
	}





	return 0;
}



// ALIOHJELMAT 

//--------------------------------------------------------------


//SEARCH - INKREMENTTI 1 (Ohjelma etsii komentorivillä annetusta merkkijonosta toisena syötettyä merkkijonoa ja tulostaa sen sijainnin merkkijonossa tai ilmoituksen etsittävän merkkirivin puuttumisesta)
//--------------------------------------------------------------

void search()
{
	string file, searchTerm;

	while (file.length() < 1)		// Ohjelma pyytää merkkijonoa, ja vaatii vähintään yhden merkin
	{
		cout << "Give a string from which to search for: ";
		getline(cin, file);
	}

	while (searchTerm.length() < 1)		// Ohjelma pyytää hakutermiä, ja vaatii vähintään yhden merkin
	{
		cout << "Give search string: ";
		getline(cin, searchTerm);
	}

	size_t found = file.find(searchTerm);


	if (found == string::npos)		// Jos annettua hakutermiä ei löydy, antaa ohjelma not found -ilmoituksen
	{
		cout << "\"" << searchTerm << "\" NOT found in \"" << file << "\"";
	}

	else		// Jos annettu hakutermi löytyy, tulostaa ohjelma koko rivin sekä sen sijainnin. 
	{
		cout << "\"" << searchTerm << "\" found in \"" << file << "\" in position " << found;
	}
}



// FILESEARCH-ALIOHJELMA - INKREMENTTI 2 (Ohjelma etsii komentorivillä syötettyä hakutermiä (toinen argumentti) annetusta tiedostosta (kolmas argumentti))
//--------------------------------------------------------------

void fileSearch(string searchTerm, string fileName)
{
	string text;
	ifstream reader;
	size_t found;


	reader.open(fileName);


	if (!reader)		// Ohjelma antaa virheilmoituksen, jos komentorivillä annettua tiedostoa ei löydy.
	{
		cout << endl << fileName << " was not found. Check filename and location." << endl;
		exit(1);
	}

	while (getline(reader, text))  // Ohjelma käsittelee annetun tiedoston kaikki rivit
	{

		found = text.find(searchTerm);


		if (found != string::npos) // Ohjelma tulostaa tekstirivit, joissa annettu hakutermi esiintyy
		{
			cout << text << endl;
		}

	}


	reader.close();

}


// FILESEARCH2-ALIOHJELMA - INKREMENTIT 3 JA 4 (Ohjelma etsii komentorivillä syötettyä hakutermiä (kolmas argumentti) annetusta tiedostosta (neljäs argumentti). Komentorivillä voidaan syöttää toisena argumentti, joka määrittelee neljä eri optioita)
//--------------------------------------------------------------

// OPTIOT - Kirjoitetaan pienillä kirjaimilla ja argumentti aloitetaan aina merkeillä -o
// o = occurrences		|	Ohjelma ilmoittaa lopuksi kuinka monella rivillä hakutermi esiintyy
// l = line numbering	|	Ohjelma ilmoittaa rivin tulostuksen yhteydessä millä rivillä hakutermi esiintyy tiedostossa
// r = reverse search	|	Käänteinen haku. Ohjelma tulostaa rivit, joilla hakutermiä ei esiinny
// i = ignore case		|	Isot ja pienet kirjaimet ovat samanarvoisia, jolloin hakutermin kirjainkoolla ei ole väliä. 
//--------------------------------------------------------------

void fileSearch2(string options, string searchTerm, string fileName)
{
	string text;
	ifstream reader;
	size_t found;
	int lineNumbering = 0, occurrences = 0;


	reader.open(fileName);		// Avataan käsiteltävä tiedosto, joka komentorivillä annetaan (neljäs argumentti)

	options.erase(0, 2);		// muuttujasta, johon toinen argumentti on tallennettu, pyyhitään kaksi ensimmäistä merkkiä, merkit -o. Tämä mahdollistaa, että optiot voidaan esittää missä järjestyksessä tahansa 






	if (!reader)		// Ohjelma antaa virheilmoituksen, jos komentorivillä annettua tiedostoa ei löydy.
	{	
		cout << endl << fileName << " was not found. Check filename and location." << endl;
		exit(1);
	}



	while (getline(reader, text))		 // Ohjelma käsittelee annetun tiedoston kaikki rivit
	{

		if (((options.find('i')) != string::npos))		// Jos option-argumentistä löytyy i, kutsutaan caseIgnore-aliohjelmaa, joka käsittelee stringin ja muuttaa merkit isoiksi kirjaimiksi. Käsittely tehdään sekä tekstille että hakuehdolle, ja lopuksi verrataan löytyykö hakuehtoa tekstistä
		{
			found = (caseIgnore(text)).find(caseIgnore(searchTerm));

		}
	
		else
		{
			found = text.find(searchTerm);
		}
		
		lineNumbering++;		// Laskee tekstin rivinumeroita 

		if ((options.find('r')) != string::npos)		// Jos option-argumentistä löytyy r, tulostetaan rivit joissa ei esiinny hakuehtoa. 
		{ 
		

			if (found == string::npos)		// Jos ohjelma käsittelee rivin loppuun asti (eli hakuehtoa ei löydy), tarkistetaan löytyykö option-argumentistä l ja/tai o
			{
				if ((options.find('l')) != string::npos)		// Jos l-merkki löytyy, tulostetaan rivin numero tulostettavan tekstirivin eteen.

				{
					cout << lineNumbering << ":" << text << endl;

				}



				else		// Jos merkkiä ei ole, tulostetaan pelkkä tekstirivi
				{

					cout << text << endl;	

				}


				occurrences++;		// Lasketaan löydetyt rivit yhteen 

			}

		}
		




		else		// Jos r-optiota ei ole, käsitellään rivejä, joilla hakutermi (argumentti 3) esiintyy
		{
			if (found != string::npos)
			{

				if ((options.find('l')) != string::npos)		// Jos l-merkki löytyy, tulostetaan rivin numero tulostettavan tekstirivin eteen.

				{
					cout << lineNumbering << ":" << text << endl;

				}



				else		// Jos merkkiä ei ole, tulostetaan pelkkä tekstirivi
				{

					cout << text << endl;

				}


				occurrences++;		// Lasketaan löydetyt rivit yhteen


			}
		}

	}

	reader.close();			// suljetaan käsiteltävä tiedosto

	if ((options.find('o')) != string::npos)		// Jos optioriviltä löytyy o, tulostetaan yhteenlaskettu rivien lukumäärä
	{
		if ((options.find('r')) != string::npos)		// Jos optiorivillä on r, tulostetaan rivien, joilta hakuehtoa ei löydy, lukumäärä
		{

			cout << endl << "Occurrences of lines NOT containing \"" << searchTerm << "\": " << occurrences;

		}

		else		// Tulostetaan rivien, joissa hakuehto esiintyy, lukumäärä.
		{
			cout << endl << "Occurrences of lines containing \"" << searchTerm << "\": " << occurrences;
		}
	}
}












// CASEINGNORE-ALIOHJELMA (INKREMENTTI 4) - Muuttaa vastaanottamansa stringin isoin kirjaimin kirjoitetuksi ja palauttaa sen pääohjelmaan.
//--------------------------------------------------------------

string caseIgnore(string caseConverter)
{
	
	for (int i = 0; i < caseConverter.length(); i++)
	{
		caseConverter[i] = toupper(caseConverter[i]);

	}

	return caseConverter; 
}
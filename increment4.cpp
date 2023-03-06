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



// P��OHJELMA - Tarkistetaan komentorivill� sy�tetyiden argumenttien m��r� ja kutsutaan oikeaa aliohjelmaa m��r�n perusteella

//--------------------------------------------------------------

int main(int argc, char* argv[])
{

	if (argc == 1)		// Jos argumenttej� on vain yksi, kutsutaan search-aliohjelmaa, joka vastaa increment 1:t�
	{
		search();
	}

	else if (argc == 3)			// Jos argumenttej� on kolme, kutsutaan fileSearch-aliohjelmaa
	{
		fileSearch(argv[1], argv[2]);

	}

	else if (argc == 4)			// Jos argumenttej� on nelj�, kutsutaan fileSearch-aliohjelmaa
	{
		if ((argv[1])[0] != '-' || (argv[1])[1] != 'o')
		{
			cout << "Invalid argument \"" << argv[1] << "\" discarded." << endl;		// Poikkeusk�sittely tarkistaa alkaako toinen argumentti merkit - ja o. Jos merkkej� ei l�ydy, antaa ohjelma virheilmoituksen ja kutsuu fileSearch-aliohjelmaa

			fileSearch(argv[2], argv[3]);
		}

		else
		{
			fileSearch2(argv[1], argv[2], argv[3]);		// Jos merkit - ja o l�ytyv�t, kutsutaan aliohjelmaa fileSearch2

		}
	}

	else
	{
		cout << "Invalid argument. \"" << argv[1] << "\" discarded." << endl;	// Jos komentorivill� on annettu virheellisi� argumenttej�, antaa ohjelma virheilmoituksen ja ohjelma sulkeutuu. 
	}





	return 0;
}



// ALIOHJELMAT 

//--------------------------------------------------------------


//SEARCH - INKREMENTTI 1 (Ohjelma etsii komentorivill� annetusta merkkijonosta toisena sy�tetty� merkkijonoa ja tulostaa sen sijainnin merkkijonossa tai ilmoituksen etsitt�v�n merkkirivin puuttumisesta)
//--------------------------------------------------------------

void search()
{
	string file, searchTerm;

	while (file.length() < 1)		// Ohjelma pyyt�� merkkijonoa, ja vaatii v�hint��n yhden merkin
	{
		cout << "Give a string from which to search for: ";
		getline(cin, file);
	}

	while (searchTerm.length() < 1)		// Ohjelma pyyt�� hakutermi�, ja vaatii v�hint��n yhden merkin
	{
		cout << "Give search string: ";
		getline(cin, searchTerm);
	}

	size_t found = file.find(searchTerm);


	if (found == string::npos)		// Jos annettua hakutermi� ei l�ydy, antaa ohjelma not found -ilmoituksen
	{
		cout << "\"" << searchTerm << "\" NOT found in \"" << file << "\"";
	}

	else		// Jos annettu hakutermi l�ytyy, tulostaa ohjelma koko rivin sek� sen sijainnin. 
	{
		cout << "\"" << searchTerm << "\" found in \"" << file << "\" in position " << found;
	}
}



// FILESEARCH-ALIOHJELMA - INKREMENTTI 2 (Ohjelma etsii komentorivill� sy�tetty� hakutermi� (toinen argumentti) annetusta tiedostosta (kolmas argumentti))
//--------------------------------------------------------------

void fileSearch(string searchTerm, string fileName)
{
	string text;
	ifstream reader;
	size_t found;


	reader.open(fileName);


	if (!reader)		// Ohjelma antaa virheilmoituksen, jos komentorivill� annettua tiedostoa ei l�ydy.
	{
		cout << endl << fileName << " was not found. Check filename and location." << endl;
		exit(1);
	}

	while (getline(reader, text))  // Ohjelma k�sittelee annetun tiedoston kaikki rivit
	{

		found = text.find(searchTerm);


		if (found != string::npos) // Ohjelma tulostaa tekstirivit, joissa annettu hakutermi esiintyy
		{
			cout << text << endl;
		}

	}


	reader.close();

}


// FILESEARCH2-ALIOHJELMA - INKREMENTIT 3 JA 4 (Ohjelma etsii komentorivill� sy�tetty� hakutermi� (kolmas argumentti) annetusta tiedostosta (nelj�s argumentti). Komentorivill� voidaan sy�tt�� toisena argumentti, joka m��rittelee nelj� eri optioita)
//--------------------------------------------------------------

// OPTIOT - Kirjoitetaan pienill� kirjaimilla ja argumentti aloitetaan aina merkeill� -o
// o = occurrences		|	Ohjelma ilmoittaa lopuksi kuinka monella rivill� hakutermi esiintyy
// l = line numbering	|	Ohjelma ilmoittaa rivin tulostuksen yhteydess� mill� rivill� hakutermi esiintyy tiedostossa
// r = reverse search	|	K��nteinen haku. Ohjelma tulostaa rivit, joilla hakutermi� ei esiinny
// i = ignore case		|	Isot ja pienet kirjaimet ovat samanarvoisia, jolloin hakutermin kirjainkoolla ei ole v�li�. 
//--------------------------------------------------------------

void fileSearch2(string options, string searchTerm, string fileName)
{
	string text;
	ifstream reader;
	size_t found;
	int lineNumbering = 0, occurrences = 0;


	reader.open(fileName);		// Avataan k�sitelt�v� tiedosto, joka komentorivill� annetaan (nelj�s argumentti)

	options.erase(0, 2);		// muuttujasta, johon toinen argumentti on tallennettu, pyyhit��n kaksi ensimm�ist� merkki�, merkit -o. T�m� mahdollistaa, ett� optiot voidaan esitt�� miss� j�rjestyksess� tahansa 






	if (!reader)		// Ohjelma antaa virheilmoituksen, jos komentorivill� annettua tiedostoa ei l�ydy.
	{	
		cout << endl << fileName << " was not found. Check filename and location." << endl;
		exit(1);
	}



	while (getline(reader, text))		 // Ohjelma k�sittelee annetun tiedoston kaikki rivit
	{

		if (((options.find('i')) != string::npos))		// Jos option-argumentist� l�ytyy i, kutsutaan caseIgnore-aliohjelmaa, joka k�sittelee stringin ja muuttaa merkit isoiksi kirjaimiksi. K�sittely tehd��n sek� tekstille ett� hakuehdolle, ja lopuksi verrataan l�ytyyk� hakuehtoa tekstist�
		{
			found = (caseIgnore(text)).find(caseIgnore(searchTerm));

		}
	
		else
		{
			found = text.find(searchTerm);
		}
		
		lineNumbering++;		// Laskee tekstin rivinumeroita 

		if ((options.find('r')) != string::npos)		// Jos option-argumentist� l�ytyy r, tulostetaan rivit joissa ei esiinny hakuehtoa. 
		{ 
		

			if (found == string::npos)		// Jos ohjelma k�sittelee rivin loppuun asti (eli hakuehtoa ei l�ydy), tarkistetaan l�ytyyk� option-argumentist� l ja/tai o
			{
				if ((options.find('l')) != string::npos)		// Jos l-merkki l�ytyy, tulostetaan rivin numero tulostettavan tekstirivin eteen.

				{
					cout << lineNumbering << ":" << text << endl;

				}



				else		// Jos merkki� ei ole, tulostetaan pelkk� tekstirivi
				{

					cout << text << endl;	

				}


				occurrences++;		// Lasketaan l�ydetyt rivit yhteen 

			}

		}
		




		else		// Jos r-optiota ei ole, k�sitell��n rivej�, joilla hakutermi (argumentti 3) esiintyy
		{
			if (found != string::npos)
			{

				if ((options.find('l')) != string::npos)		// Jos l-merkki l�ytyy, tulostetaan rivin numero tulostettavan tekstirivin eteen.

				{
					cout << lineNumbering << ":" << text << endl;

				}



				else		// Jos merkki� ei ole, tulostetaan pelkk� tekstirivi
				{

					cout << text << endl;

				}


				occurrences++;		// Lasketaan l�ydetyt rivit yhteen


			}
		}

	}

	reader.close();			// suljetaan k�sitelt�v� tiedosto

	if ((options.find('o')) != string::npos)		// Jos optiorivilt� l�ytyy o, tulostetaan yhteenlaskettu rivien lukum��r�
	{
		if ((options.find('r')) != string::npos)		// Jos optiorivill� on r, tulostetaan rivien, joilta hakuehtoa ei l�ydy, lukum��r�
		{

			cout << endl << "Occurrences of lines NOT containing \"" << searchTerm << "\": " << occurrences;

		}

		else		// Tulostetaan rivien, joissa hakuehto esiintyy, lukum��r�.
		{
			cout << endl << "Occurrences of lines containing \"" << searchTerm << "\": " << occurrences;
		}
	}
}












// CASEINGNORE-ALIOHJELMA (INKREMENTTI 4) - Muuttaa vastaanottamansa stringin isoin kirjaimin kirjoitetuksi ja palauttaa sen p��ohjelmaan.
//--------------------------------------------------------------

string caseIgnore(string caseConverter)
{
	
	for (int i = 0; i < caseConverter.length(); i++)
	{
		caseConverter[i] = toupper(caseConverter[i]);

	}

	return caseConverter; 
}
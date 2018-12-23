#include "pch.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::init()
{
	strichLinie();
	cout << "Willkommen bei dem Spiel Schiffe versenken!" << endl;
	copyRight();
	strichLinie();
	cout << "Bitte geben Sie einen Namen fuer Spieler 1 ein:" << endl;
	cin >> this->S1.name;
	setShip(this->S1.name, &S1ownNetz);
	system("cls");
	strichLinie();
	cout << "Willkommen bei dem Spiel Schiffe versenken!" << endl;
	cout << "Geben Sie 'Computer' ein wenn Sie gegen den Computer spielen wollen!" << endl;
	copyRight();
	strichLinie();
	cout << "Bitte geben Sie einen Namen fuer Spieler 2 ein:" << endl;
	cin >> this->S2.name;
	/*gegen Compueter*/
	if (this->S2.name == "Computer") {
		cout << "Sie spielen gegen den Computer!" << endl;
		getchar();
		setShipComputer(this->S2.name, &S2ownNetz);
		
	}
	//dann mit else weiter
	else {
		setShip(this->S2.name, &S2ownNetz);
	}
	
	try {			//play läuft solange bis eine Exception ausgeworfen wird
		play();		//wenn Spiel Ende, Spiel unterbrochen mit Nachricht wer gewonnen hat
	}
	catch (const char* Fehler) {
		system("cls");
		cout << endl << endl << endl;
		cout << Fehler << endl;
		cout << "GAME OVER" << endl;
		cout << endl << endl << endl;
		system("Pause");
	}
}
						
void Game::play()
{ 
	char Y;
	int x;
	int y;
	int antwort = 0;

	while (true) {		//Mit exception wird die While verlassen!
		system("cls");
		// Spieler 1
		printField(S1.name, S1enemyNetz);
		printField(S1.name, S1ownNetz);
		cout << "Wohin wollen sie Schiessen:" << endl;
		cout << "Geben sie die Y Kordinate ein (A,B..):" << endl;
		Y = charEinlesen();
		cout << "Geben sie die X Kordinate ein (1,2..):" << endl;
		x = intEinlesen();
		try {
			y = umwandlungYAchse(Y);
			fire(&S1enemyNetz, &S2ownNetz, x, y);
		}
		catch (const char* Fehler) {
			system("cls");
			cout << endl << endl << endl;
			cout << Fehler << endl;
			cout << endl << endl << endl;
			system("Pause");
		}
		try {	//Schaut nach jedem Schuss nach ob beim GegnerFeld nach
				//ob noch ein Feld mit einem nichtgetroffenes Schiff vorhanden ist
			gameOver(&S2ownNetz);

		}
		catch(int i){	//wenn Wert unter trow ein 2er ist dann heißt es Spiel Ende
			if (i == 1) {
				try {
					update(&S2ownNetz);
				}
				catch (int i) {
				if (i == 3) {	//Wenn alle Kammer voll mit Wasser sind
						system("cls");
						cout << endl << endl << endl;
						cout << "Schiff versenkt !!" << endl;
						cout << endl << endl << endl;
						system("Pause");
					}
				}
			}
			if (i == 2) {
				throw "Spieler 1 Gewinnt !!";
			}	
		}
		system("cls");

		if (this->S2.name == "Computer") {
			/*Spieler 2 = Computer*/
			bool status = true;
			int z = 0, s = 0;
			//wenn Schiff getroffen ist dann soll der Comp in dieser Zeile weitermachen
			try {
				for (auto temp : this->S1ownNetz.vMatrix) {
					for (auto Zeile : temp) {
						//Wenn in der Zeile ein Schiff getroffen ist und 
						if (Zeile->fieldstate->getState() == 'X') {
							trefferZeile = z;
							throw 20;		//raus aus den for-eachschleifen
						}
					}
					z++;
				}
			}
			catch (int e) {
				//fahre weiter mit dem Rest des Codes fort
			}
			if (trefferZeile>=0 && trefferZeile<10) {					//weiter in dieser Zeile schißen bis Schiff zerstört ist

				printField(S2.name, S2enemyNetz);
				printField(S2.name, S2ownNetz);
				cout << "Der Computer schiesst auf:" << endl;	
				Y = umwandlungCompYAchse(trefferZeile);					//Umwandlung in char  dann uebergabe
				cout << "Die Y Kordinate ist:" << Y << endl;
				getchar();
				z = 0;
				auto temp = this->S1ownNetz.vMatrix[trefferZeile];		//suche in dieser Zeile
				try {
					x = -1; //initialisieren
					for (auto Zeile : temp) {
						s++;
						//Wenn in der Zeile ein Schiff ok ist  
						if (Zeile->fieldstate->getState() == 'V' ) {
							x = s;			//die X Koord. ist jetzt Schiff ok
							throw 10;
						}
					}
				}
				catch (int f) {				
					//fahre weiter mit dem Rest des Codes fort		
				}
				if (x == -1) {
					printField(S2.name, S2enemyNetz);
					printField(S2.name, S2ownNetz);
					cout << "Der Computer schiesst auf:" << endl;
					Y = umwandlungCompYAchse((rand() % 10));
					cout << "Die Y Kordinate ist:" << Y << endl;
					getchar();
					x = rand() % 10;
					cout << "Die X Kordinate ist:" << x << endl;
					getchar();
				}
				else {
					cout << "Die X Kordinate ist:" << x << endl;
					getchar();
				}
				
			}
			else {
				printField(S2.name, S2enemyNetz);
				printField(S2.name, S2ownNetz);
				cout << "Der Computer schiesst auf:" << endl;
				Y = umwandlungCompYAchse((rand() % 10));
				cout << "Die Y Kordinate ist:" << Y << endl;
				getchar();
				x = rand() % 10;
				cout << "Die X Kordinate ist:" << x << endl;
				getchar();
			}
			try {	//für Y wert und für Firemethode ob das Schiff getroffen wurde oder nicht
				y = umwandlungYAchse(Y);
				fire(&S2enemyNetz, &S1ownNetz, x, y);
			}
			catch (const char* Status) {
				system("cls"); 
				cout << endl << endl << endl;
				cout << Status << endl;
				cout << endl << endl << endl;
				system("Pause");
			}
			try {	//Schaut nach jedem Schuss nach ob beim GegnerFeld nach
				//ob noch ein Feld mit einem nichtgetroffenes Schiff vorhanden ist
				gameOver(&S1ownNetz);
				update(&S1ownNetz);
			}
			catch (int i) {	//wenn Wert unter trow ein 2er ist dann heißt es Spiel Ende
				if (i == 1) {
					try {
						update(&S2ownNetz);
					}
					catch (int i) {
						if (i == 3) {		//Wenn alle Kammer voll mit Wasser sind
							system("cls");
							cout << endl << endl << endl;
							cout << "Schiff versenkt !!" << endl;
							cout << endl << endl << endl;
							trefferZeile = -1;
							system("Pause");
						}
					}
				}
				if (i == 2) {
					throw "Spieler 2 Gewinnt !!";
				}
				else if (i == 3) {		//Wenn alle Kammer voll mit Wasser sind
					system("cls");
					cout << endl << endl << endl;
					cout << "Schiff versenkt !!" << endl;
					trefferZeile = -1;
					cout << endl << endl << endl;
					system("Pause");
				}
			}		
		}
		else {
			//Spieler 2
			printField(S2.name, S2enemyNetz);
			printField(S2.name, S2ownNetz);
			cout << "Wohin wollen sie Schiessen:" << endl;
			cout << "Geben sie die Y Kordinate ein (A,B..):" << endl;
			Y = charEinlesen();
			cout << "Geben sie die X Kordinate ein (1,2..):" << endl;
			x = intEinlesen();
			try {	//für Y wert und für Firemethode ob das Schiff getroffen wurde oder nicht
				y = umwandlungYAchse(Y);
				fire(&S2enemyNetz, &S1ownNetz, x, y);
			}
			catch (const char* Status) {
				system("cls");
				cout << endl << endl << endl;
				cout << Status << endl;
				cout << endl << endl << endl;
				system("Pause");
			}
			try {	//Schaut nach jedem Schuss nach ob beim GegnerFeld nach
					//ob noch ein Feld mit einem nichtgetroffenes Schiff vorhanden ist
				gameOver(&S1ownNetz);
				update(&S1ownNetz);
			}
			catch (int i) {	//wenn Wert unter trow ein 2er ist dann heißt es Spiel Ende
				if (i == 1) {
					try {
						update(&S2ownNetz);
					}
					catch (int i) {
						if (i == 3) {		//Wenn alle Kammer voll mit Wasser sind
							system("cls");
							cout << endl << endl << endl;
							cout << "Schiff versenkt !!" << endl;
							cout << endl << endl << endl;
							system("Pause");
						}
					}
				}
				if (i == 2) {
					throw "Spieler 2 Gewinnt !!";
				}
				else if (i == 3) {		//Wenn alle Kammer voll mit Wasser sind
					system("cls");
					cout << endl << endl << endl;
					cout << "Schiff versenkt !!" << endl;
					cout << endl << endl << endl;
					system("Pause");
				}
			}
		}
	}
}

void Game::fire(Grid * own, Grid * enemy, int X, int Y)
{
	int i = 0;
	int j = 1;
	int k = 0;
	int l = 1;
	for (auto temp : enemy->vMatrix) {	 //Schauen ins Gegnerfeld 
		if (i == Y) {
			for (auto Zeile : temp) {		
				if (j == X){	
					try {				//Sollte eine Exception rausgeworfen werden, sonst in die for darunter weitermachen 
						Zeile->fieldstate->setStateShoot();
					}
					catch (const char* Treffer) { //Wenn getroffen wurde, setzen wir in Owngrid Schiff auf treffer 
						Zeile->ship->kammer--;
						for (auto temp : own->vMatrix) {
							if (k == Y) {
								for (auto Zeile : temp) {
									if (l == X) {
										Zeile->fieldstate->setStateWater(true);
										//vergleichbar mit brek od return mit Statusinfo
										throw Treffer;	//Unterbrechung, raus aus der Methode, weil fertig Gegnerfeld u Ownfeld ist beschrieben
									}
									l++;
								}
							}
							k++;
						}
					}
				}
				j++;
			}
		}
		i++;
	}
	i = 0;
	j = 1;
	for (auto temp : own->vMatrix) {
		if (i == Y) {
			for (auto Zeile : temp) {
				if (j == X) {		
						Zeile->fieldstate->setStateWater(false);
						throw "Schuss ging ins Wasser";
				}
				j++;
			}
		}
		i++;
	}
}

void Game::gameOver(Grid* Netz)		//Schaut im Grid nach ob noch ein V (Schiff ok) vorhanden ist
{									
	for (auto temp: Netz->vMatrix) {
		for (auto Zeile : temp) {
			if (Zeile->fieldstate->getState() == 'V') {
				throw 1;			// exception mit den Wert 1 zurück zum auswerten
			}
		}
	}
	throw 2;						//wenn Kein V mehr vorhanden ist ist das Spiel zu ende
}
void Game::printField(string spielerName, Grid netz)
{
	
	char abc = 'A';
	cout << "\t\t\t"<<spielerName << "\t\t\t\t" << endl;
	cout << "\t | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|" << endl;
	cout << "\t |--+--+--+--+--+--+--+--+--+--|" << endl;
	for (auto temp: netz.vMatrix) {
		cout <<"\t"<< abc << "|";
		for (auto zeile: temp) {

			cout << " " << zeile->fieldstate->getState() << "|";
			
		}
		cout << endl << "\t |--+--+--+--+--+--+--+--+--+--|" << endl;
		abc++;
	}
	cout << "\t | 1| 2| 3| 4| 5| 6| 7| 8| 9|10|" << endl;

}

void Game::setShip(string spielerName, Grid* netz)
{
	string eingabe;
	int Anzahl = 0;
	char Y;
	int y;
	int x;
	 
	while (Anzahl < anzahlBoote) {
		system("cls");
		printField(spielerName, *netz);
		cout << "Bitte Platzieren sie den Kreuzer:" << endl;
		cout << "Geben sie die Y Kordinate ein (A,B..):" << endl;
		Y = charEinlesen();
		cout << "Geben sie die X Kordinate ein (1,2..):" << endl;
		x = intEinlesen();
		try {
			y = umwandlungYAchse(Y);
			Schiff* Kreuzer = new KreuzerSchiff();
			setShipField(Kreuzer, x, y, netz);
			Anzahl++;
		}
		catch (const char* Fehler) {
			system("cls");
			cout << endl << endl << endl;
			cout << Fehler << endl;
			cout << endl << endl << endl;
			system("Pause");
		}
	}
	
	Anzahl = 0;
	while (Anzahl < anzahlBoote) {
		system("cls");
		printField(spielerName, *netz);
		cout << "Bitte Platzieren sie ihre Fregatte:" << endl;
		cout << "Geben sie die Y Kordinate ein (A,B..):" << endl;
		Y = charEinlesen();
		cout << "Geben sie die X Kordinate ein (1,2..):" << endl;
		x = intEinlesen();
		try {
			y = umwandlungYAchse(Y);
			Schiff* Fregatte = new FregatteSchiff();
			setShipField(Fregatte, x, y, netz);
			Anzahl++;
		}
		catch (const char* Fehler) {
			system("cls");
			cout << endl << endl << endl;
			cout << Fehler << endl;
			cout << endl << endl << endl;
			system("Pause");
		}
	}
	
}

void Game::setShipField(Schiff * meinSchiff, int X, int Y, Grid * meinNetz)
{
	if (X < 1 || X>10) {

		throw "Eingabe der X Kordinate fehlerhaft!";
	}
	int i = 0;
	int j = 1;		//weil bei Spalten wird von 1 zum zählen angefangen
	int k = (meinSchiff->getShipSize())/2;		//Mitte Schiff rausfinden
	int l = 0;
	
	if ((X - k) < 1 || (X + k) > 10) {			//überprüfen ob Schiff platz hat
		throw "Schiff ist ausserhalb des Grides!";
	}

	for (auto temp : meinNetz->vMatrix) {		//Schleife zum überprüfen ob ein Schiff auf ein anderes platziert wird 
		if (i == Y) {
			for (auto Zeile : temp) {			//in den Spalten das Schiff platzieren
				if (j >= (X-k) && j <= (X+k)) {	//Vom Schiffmitte li u re Felder belegen
					Zeile->fieldstate->canSetStateShip();
				}
				j++;
			}
		}
		i++;
	}
	i = 0; j = 1;
	for (auto temp : meinNetz->vMatrix) {		//Wenn oben keine Ecepition ausgeworfen wird dann geht es in dieser Schleife rein
		if (i == Y) {
			for (auto Zeile : temp) {			//in den Spalten das Schiff platzieren
				if (j >= (X - k) && j <= (X + k)) {	//Vom Schiffmitte li u re Felder belegen
					Zeile->fieldstate->setStateShip();
					Zeile->setPointerShip(meinSchiff);
				}
				j++;
			}
		}
		i++;
	}
}

int Game::umwandlungYAchse(char Y)		//Methode damit für den Buchstaben eine Zeile zugeordnet werden kann
{
	int i = 0;
	switch (Y)
	{
	case 'A':i = 0; break;
	case 'B':i = 1; break;
	case 'C':i = 2; break;
	case 'D':i = 3; break;
	case 'E':i = 4; break;
	case 'F':i = 5; break;
	case 'G':i = 6; break;
	case 'H':i = 7; break;
	case 'I':i = 8; break;
	case 'J':i = 9; break;
	default:throw "Kein Grossbuchstaben erkannt";
	}
	return i;
}

char Game::umwandlungCompYAchse(int Y)
{
	char c;
	switch (Y)
	{
		case 0 :	c = 'A'; break;
		case 1:		c = 'B'; break;
		case 2:		c = 'C'; break;
		case 3:		c = 'D'; break;
		case 4:		c=  'E';  break;
		case 5:		c = 'F'; break;
		case 6:		c = 'G'; break;
		case 7:		c = 'H'; break;
		case 8:		c = 'I'; break;
		case 9:		c = 'J'; break;
		default:throw "Kein Zahl in der vorgegebene Grenze erkannt";
	}
	return c;
}

int Game::intEinlesen()
{
	int i;
	while (true) {
		cin >> i;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Fehlerhafte Eingabe";
		}
		else break;
	}
	return i;
}

char Game::charEinlesen()
{
	char i;
	while (true) {
		cin >> i;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "Fehlerhafte Eingabe";
		}
		else break;
	}
	return i;
}

void Game::update(Grid* Netz)
{
	bool flag = false;
	for (auto temp : Netz->vMatrix) {
		for (auto Zeile : temp) {
			if (Zeile->ship != NULL) {
				if (Zeile->ship->kammer == 0) {
					Zeile->fieldstate->setStateDestroyed();
					if (Zeile->ship->Versenkt == false) {
						flag = true;
					}
					Zeile->ship->Versenkt = true;
				}
			}
		}
	}
	if (flag == true) {
		throw 3;
	}
}

void Game::setShipComputer(string spielerName, Grid * netz)
{
	string eingabe;
	int Anzahl = 0;
	char Y;
	int y;
	int x;
	bool status = true;


	while (Anzahl < anzahlBoote) {
		//Bis die passenden Koordinaten eingegeben worden sind
		while (status == true) {
			system("cls");
			printField(spielerName, *netz);
			cout << "Kreuzer patzieren:" << endl;
			Y = umwandlungCompYAchse((rand() % 10));
			cout << "Die Y Kordinate ist:" << Y << endl;
			getchar();
			x = rand() % 10;
			cout << "Die X Kordinate ist:" << x << endl;
			getchar();
			try {
				y = umwandlungYAchse(Y);
				Schiff* Kreuzer = new KreuzerSchiff();
				setShipField(Kreuzer, x, y, netz);
				Anzahl++;
				status = false;
			}
			catch (const char* Fehler) {
				system("cls");
				cout << endl << endl << endl;
				cout << Fehler << endl;
				cout << endl << endl << endl;
				status = true;
			}
		}		
	}
	status = true;

	Anzahl = 0;
	while (Anzahl < anzahlBoote) {
		//Bis die passenden Koordinaten eingegeben worden sind
		while (status == true) {
			system("cls");
			printField(spielerName, *netz);
			cout << "Fregatte platzieren:" << endl;
			Y = umwandlungCompYAchse((rand() % 10));
			cout << "Die Y Kordinate ist:" << Y << endl;
			getchar();
			x = rand() % 10;
			cout << "Die X Kordinate ist:" << x << endl;
			getchar();
			try {
				y = umwandlungYAchse(Y);
				Schiff* Fregatte = new FregatteSchiff();
				setShipField(Fregatte, x, y, netz);
				Anzahl++;
				status = false;
			}
			catch (const char* Fehler) {
				system("cls");
				cout << endl << endl << endl;
				cout << Fehler << endl;
				cout << endl << endl << endl;
				status = true;
			}
		}

	}

}

void Game::copyRight()
{	
	int i;
	printf(" ");
	printf("\t\t\t\t\t\t\t\t\t\t\t%c", 0xDA);
	for (i = 1; i <= 24; i++)
		printf("%c", 0xC4);
	printf("%c\n", 0xBF);
	printf("\t\t\t\t\t\t\t\t\t\t\t%c \xB8  B Maxim u. M Kargl  %c\n", 0xB3, 0xB3);
	printf("\t\t\t\t\t\t\t\t\t\t\t%c", 0xC0);
	for (i = 1; i <= 24; i++)
		printf("%c", 0xC4);
	printf("%c\n", 0xD9);
	printf("\n");

}

void Game::strichLinie()
{
	//Schleife fuer die Ausgabe einer kpl Strichlinie
	for (int i = 0; i < 120; i++) {
		cout << "_";
	}
}



Imi� i nazwisko: Krzysztof Najda

======================================================================================================================================================
Specyfikacja problemu:
======================================================================================================================================================
Mamy na p�aszczy�nie XY dok�adnie N punkt�w. W jednym ruchu mo�emy zaznaczy� zbi�r punkt�w, z kt�rych wszystkie s� wsp�liniowe, i usun�� je. 
Celem gry jest usuni�cie wszystkich punkt�w w jak najmniejszej liczbie ruch�w. 
Zaproponuj algorytm, kt�ry wyliczy minimaln� liczb� ruch�w potrzebn� do usuni�cia wszystkich punkt�w oraz liczb� mo�liwych kombinacji ruch�w s�u��cych usuni�ciu tych punkt�w (przy czym jeden ruch r�ni si� od innego je�li przynajmniej jeden punkt jest usuni�ty w innym ruchu).

======================================================================================================================================================
Polecenia aktywacji programu:
======================================================================================================================================================
-m	Wyb�r trybu uruchomienia programu
	1 - Zbi�r punkt�w podawany przez standardowe wej�cie
	2 - Zbi�r punkt�w generowany jednym z generator�w
	3 - Uruchomienie eksperymentu z�o�ono�ci czasowej algorytm�w

-g	Wyb�r generatora punkt�w [tylko dla trybu -m 2]
	grid -	generowanie punkt�w w siatce, tj. wszystkie punkty maj� wsp�rz�dne takie �e s� kolejnymi liczbami ca�kowitymi
	sgrid -	jak grid z tym �e licza punkt�w do generacji jest zadana przez u�ytkownika
	sparse - generowanie punkt�w w liniach o losowych parametrach
	comb - generowanie punkt�w w formie grzebienia 
	diamond - generowanie siatki o �ci�tych kraw�dziach

-col	Wyb�r ilo�ci kolumn w siatce [tylko dla -g grid, sgrid, comb, diamond]
-row	Wyb�r ilo�ci rz�d�w w siatce [tylko dla -g grid, sgrid, comb, diamond]
-il	Wyb�r wielko�ci wci�cia w lewym g�rnym rogu siatki [tylko dla -g diamond]
-ir	Wyb�r wielko�ci wci�cia w prawym dolnym rogu siatki [tylko dla -g diamond]
-nmin	Wyb�r max ilo�ci punkt�w w jednej linii [tylko dla -g sparse]
-nmax	Wyb�r min ilo�ci punkt�w w jednej linii [tylko dla -g sparse]
-n	Wyb�r ilo�ci punkt�w [tylko dla -g sgrid], lub ilo�ci linii [tylko dla -g sparse]
-d	Wyb�r g�sto��i punkt�w [tylko dla -g sgrid oraz -m 3]

-r	Wyb�r ilo�ci powt�rze�, czyli ile razy b�dzie powtarzany eksperyment [tylko dla -m 3]
-i	Wyb�r ilo�ci iteracji, czyli ile razy liczba punkt�w b�dzie powi�kszana [tylko dla -m 3]
-step	Wyb�r wielko�ci kroku mi�dzy kolejnymi iteracjami, czyli ile zostanie dodane punkt�w [tylko dla -m 3]

-lines	Opcjonalna flaga, do��czenie jej spowoduje wy�wietlenie podsumowania wygenerowanych linii - ile jest linii o danych rozmiarze [tylko dla -m 1, 2]
-points	Opcjonalna flaga, do��czenie jej spowoduje wy�wietlenie podsumowania zbioru punkt�w, oraz w pliku points.txt pojawi si� zbi�r wszystkich wprowadzonych punkt�w [tylko dla -m 1, 2]
-time	Opcjonalna flaga, do��czenie jej spowoduje wy�wietlenie ile czasu zaj�o wykonanie ka�dego etapu algorytmu [tylko dla -m 1, 2]

======================================================================================================================================================
Konwencja danych wej�ciowych i prezentacji wynik�w
======================================================================================================================================================
Dane dotycz�ce punkt�w mog� zosta� wprowadzone ze standardowego wej�cia (dla trybu -m 1).
Powinny one mie� tak� form�, �e kolejne wsp�rz�dne s� oddzielone za pomoc� whitespace, a kolejne pary liczb to wsp�rz�dne kolejnych punkt�w.

Przyk�ad:
1 	0
3.1 	8
0 	2.5
1 	1

Takie dane wygeneruj� nast�puj�ce punkty: (1, 0), (3.1, 8), (0, 2.5), (1, 1)
Takie same punkty zosta�yby wygenerowane dla nast�puj�cego wej�cia: 1 0 3.1 8 0 2.5 1 1
= = = = = =
Prezentacja wynik�w dla trybu -m 1, 2 jest taka sama i zale�y w du�ym stopni od tego czy program zosta� wywo�any z flagami: -lines, -points, -time.
Bez wzgl�du na obecno�� tych flag, zawsze s� wy�wietlane: ile min ruch�w(linii) potrzeba aby pokry� dany zbi�r punkt�w, oraz ile jest kombinacji, aby to wykona� takie minimalne pokrycie.

Przyk�ad:

MinCover: 15
UniqueSolutions: 2 (2615348736000) //przed nawiasem ile jest unikalnych rozwi�za� (nie bior�c pod uwag� kolejno�ci usuwania kolejnych linii z rozwi�zania)
= = = = = =
Gdyby zosta�e w��czone opcjonalne flagi -lines, -points, -time, mog�o by to wygl�da� tak:

Lines size: //-lines
0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	
0	0	0	1706	432	236	20	48	36	4	4	4	4	4	4	32	
Execution time: 101 //-time (czas wykonania generacji linii)

MinCover: 15
Execution time: 16 //-time (czas znalezienia minimalnego rozwi�zania)

UniqueSolutions: 2 (2615348736000)
Execution time: 743 //-time (czas znalezienia ilo�ci rozwi�za�)
= = = = = =
Wyj�cie dla trybu -m 3 wygl�da inaczej:
Kolejno, w tej samej linii, odzielone za pomoc� '\t', dla ka�dej iteracji wypisywane s�: 
	czas wykonania generacji linii,
	czas znalezienia minimalnego pokrycia,
	ile linii pokrywa dan� iteracje problemu, 
	czas znalezienia ilo�ci unikalnych rozwi�za�, 
	ile unikalnych rozwi�za� znaleziono.
Newline oddziela kolejne powt�rzenia problemu.

Po wykonaniu wszystkich powt�rze� wypisywane jest podsumowanie u�rednionych czas�w wykonania ka�dego z algorytm�w dla ka�dej z iteracji, oraz u�rednion� liczb� linii znalezionych w danej iteracji.

Przyk�ad dla ustawie� -d 0.5 -r 2 -i 8 -step 25:

0	0	7	0	5	
0	0	9	0	1	
15	0	12	0	1	
16	0	14	15	1	
32	0	16	46	2	
32	15	17	63	1	
62	47	19	415	2	
94	90	20	597	2	

0	0	7	0	43	
15	0	11	0	6	
0	16	13	0	2	
15	16	15	47	5	
31	16	16	47	1	
31	391	18	506	1	
63	522	20	2190	2	
78	641	21	2868	2	


LinesNumber: 	35	120	257	458	744	1070	1451	1895	
LineGen: 	0	7	7	15	31	31	62	86	
MinCover: 	0	0	8	8	8	203	284	365	
Unique: 	0	0	0	31	46	284	1302	1732	
======================================================================================================================================================
Opis metody rozwi�zania i struktur danych
======================================================================================================================================================
Problem zosta� podzielony na 3 zasadnicze podproblemy:
1. Odnalezienie wszystkich linii kt�re zawieraj� 3 lub wi�cej punkt�w (nie ma sensu zapami�tywa� tych kt�re maj� 2 lub mniej punkt�w, poniewa� takie linie mo�na u�o�y� mi�dzy ka�dym z dowolnych punkt�w)
2. Odnalezienie minimalnej liczby linii pokrywaj�cej wszystkie punkty
3. Odnalezienie wszystkich rozwi�za�, sk�adaj�cych si� z liczby linii, kt�ra zosta�a okre�lona przez algorytm numer 2
= = = = = =
Zosta�y zastosowane nast�puj�ce struktury danych:
Line oraz Point
	Reprezentuj� linie i punkty. Ka�da linia trzyma list� punkt�w, kt�re ta linia zawiera. Podobnie ka�dy punkt trzyma list� linii, k�te przecinaj� ten punkt.
	Dok�adniej ujmuj�c to obie te struktury trzymaj� iteratory na t� drug�, co jest mo�liwe poniewa� punkty oraz linie s� trzymane w li�cie, kt�rej iteratory s� sta�e.
	Dzi�ki temu nie trzeba korzysta� z pointer�w, ani kopiowa� obiekt�w.

PlaneXY
	Trzyma lis� punkt�w oraz wektor list kt�re trzymaj�c� linie. Ka�dy indeks wektora odpowiada rozmiarowi danej linii (czyli ilo�ci trzymanych przez niego punkt�w).
	Dzi�ki temu linie s� zawsze posortowane wed�ug rozmiaru, co okazuje si� przydatne w trakcie dzia�ania algorytmu 2 i 3.
	Dost�pne s� metody kt�re "niby wy��czaj�" dan� linie - tzn. symuluj� uk�ad struktury danych tak jakby linia i wszystkie punkty kt�re ona zawiera zosta�a usuni�ta.
	Mo�liwy jest tak�e "splice" danych linii, co jest u�ywane, aby przesun�� przetestowane ju� linie do innej struktury danych. Dzi�ki temu dana kombinacja linii jest sprawdzana max raz.
= = = = = =
Algorytm numer 1
	Aby m�c rozwa�a�, kt�re linie nale�y wybra�, aby spe�ni� warunki polecenia, trzeba je najpierw znale��. 
	W tym celu wybieram ze zbioru punkt�w dwa punkty, okre�lam na jakiej linii te dwa punkty le�� i sprawdzam czy linia o takich parametrach nie zosta�a ju� rozwa�ona. (to ostanie realizowane za pomoc� unordered_set)
	Je�li taka linia rzeczywi�cie zosta�a ju� rozwa�ona to wracam do pocz�tku algorytmu wybieraj�c dwa kolejne punkty.
	Nast�pnie dla wszystkich punkt�w za wyj�tkiem tych ju� rozwa�onych, sprawdzam czy nale�� do rozwa�anej linii. Je�li tak to dodaje punkt do linii. 
	Po sprawdzeniu wszystkich punkt�w dla danej linii sprawdzam, czy le�� na niej wi�cej ni� 2 punkty. Je�li tak to lini� zapisuj� i wracam do pocz�tku algorytmu. 
	Post�puj� tak dop�ki nie rozwa�� wszystkich par punkt�w.

Algorytm numer 2
	Przed w�a�ciwym algorytmem znajdowania minimalnego pokrycia, nast�puje preprocesing.
	Znajduje on punkty kt�re nie le�a na �adnej z linii znalezionych za pomoc� algorytmu 1, i odejmuje znalezion� liczb� od liczby punkt�w dla kt�rych szukane b�dzie rozwi�zanie.
	Znajduje on tak�e linie, kt�re maj� co najmniej 2 punkty kt�re s� przecinane tylko przez t� linie. Taka linia mo�e zosta� usuni�ta z danych wej�ciownych do w�a�ciwego algorytmu.
	Po tych zabiegach nast�puje przej�cie do w�a�ciwej cz�ci algorytmu.
	Algorytm przyjmuje liczb� punkt�w (n), przypuszczaln� liczb� linii (k), oraz zbi�r linii wygenerowany algorytmem z pkt. 1 i poddany preprocesingowi. 
	Liczba punkt�w jest dana, natomiast jako parametr pocz�tkowy k podawana jest liczba ceil(n/2) - czyli tak jakby�my nie przewidywali �adnych linii kt�re zawieraj� wi�cej ni� 2 punkty.
	Dla ka�dej linii kt�ra przecina wi�cej ni� ceil(c/k) punkt�w, po zasymulowaniu usuni�cia tej�e linii i przerzucania jej do listy przetestowanych ju� linii wywo�ywany jest rekurencyjnie ten algorytm.
	Gdy rekurencja wraca, przetestowana linia jest "w��czana" (ale ca�y czas pozostaje w li�cie przetestownych) i wybierana jest kolejna linia.
	Kiedy znalezione zostaje rozwi�zanie dla k linii, parametr k zostaje dekrementowany, a nowe stany s� rozwijane z ostrzejszym ograniczeniem.
	Gdy nie ma ju� stan�w kt�re mo�naby rozwin�� zwracane jest najlepsze znalezione dotychczas rozwi�zanie, a je�li takiego nie ma -1.

Algorytm numer 3
	Pomys� na algorytm do problemu numer 3 jest modyfikacj� algorytmu z punktu 2. 
	Podobnie przeszukujemy w g��b bez linii kt�re nie zawieraj� wi�cej ni� n/k punkt�w. 
	Zmian� jest to, �e parametr k jest sta�y (wyliczony za pomoc� algorytmu numer 2), a zwracane jest nie nowe rozwi�zanie, a liczba kt�ra reprezentuje ile unikalnych rozwi�za� zosta�o znalezionych.

======================================================================================================================================================
Pliki programu
======================================================================================================================================================
//TODO

======================================================================================================================================================
Dodatkowe zalecenia
======================================================================================================================================================
//TODO
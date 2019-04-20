Imiê i nazwisko: Krzysztof Najda

======================================================================================================================================================
Specyfikacja problemu:
======================================================================================================================================================
Mamy na p³aszczyŸnie XY dok³adnie N punktów. W jednym ruchu mo¿emy zaznaczyæ zbiór punktów, z których wszystkie s¹ wspó³liniowe, i usun¹æ je. 
Celem gry jest usuniêcie wszystkich punktów w jak najmniejszej liczbie ruchów. 
Zaproponuj algorytm, który wyliczy minimaln¹ liczbê ruchów potrzebn¹ do usuniêcia wszystkich punktów oraz liczbê mo¿liwych kombinacji ruchów s³u¿¹cych usuniêciu tych punktów (przy czym jeden ruch ró¿ni siê od innego jeœli przynajmniej jeden punkt jest usuniêty w innym ruchu).

======================================================================================================================================================
Polecenia aktywacji programu:
======================================================================================================================================================
-m	Wybór trybu uruchomienia programu
	1 - Zbiór punktów podawany przez standardowe wejœcie
	2 - Zbiór punktów generowany jednym z generatorów
	3 - Uruchomienie eksperymentu z³o¿onoœci czasowej algorytmów

-g	Wybór generatora punktów [tylko dla trybu -m 2]
	grid -	generowanie punktów w siatce, tj. wszystkie punkty maj¹ wspó³rzêdne takie ¿e s¹ kolejnymi liczbami ca³kowitymi
	sgrid -	jak grid z tym ¿e licza punktów do generacji jest zadana przez u¿ytkownika
	sparse - generowanie punktów w liniach o losowych parametrach
	comb - generowanie punktów w formie grzebienia 
	diamond - generowanie siatki o œciêtych krawêdziach

-col	Wybór iloœci kolumn w siatce [tylko dla -g grid, sgrid, comb, diamond]
-row	Wybór iloœci rzêdów w siatce [tylko dla -g grid, sgrid, comb, diamond]
-il	Wybór wielkoœci wciêcia w lewym górnym rogu siatki [tylko dla -g diamond]
-ir	Wybór wielkoœci wciêcia w prawym dolnym rogu siatki [tylko dla -g diamond]
-nmin	Wybór max iloœci punktów w jednej linii [tylko dla -g sparse]
-nmax	Wybór min iloœci punktów w jednej linii [tylko dla -g sparse]
-n	Wybór iloœci punktów [tylko dla -g sgrid], lub iloœci linii [tylko dla -g sparse]
-d	Wybór gêstoœæi punktów [tylko dla -g sgrid oraz -m 3]

-r	Wybór iloœci powtórzeñ, czyli ile razy bêdzie powtarzany eksperyment [tylko dla -m 3]
-i	Wybór iloœci iteracji, czyli ile razy liczba punktów bêdzie powiêkszana [tylko dla -m 3]
-step	Wybór wielkoœci kroku miêdzy kolejnymi iteracjami, czyli ile zostanie dodane punktów [tylko dla -m 3]

-lines	Opcjonalna flaga, do³¹czenie jej spowoduje wyœwietlenie podsumowania wygenerowanych linii - ile jest linii o danych rozmiarze [tylko dla -m 1, 2]
-points	Opcjonalna flaga, do³¹czenie jej spowoduje wyœwietlenie podsumowania zbioru punktów, oraz w pliku points.txt pojawi siê zbiór wszystkich wprowadzonych punktów [tylko dla -m 1, 2]
-time	Opcjonalna flaga, do³¹czenie jej spowoduje wyœwietlenie ile czasu zajê³o wykonanie ka¿dego etapu algorytmu [tylko dla -m 1, 2]

======================================================================================================================================================
Konwencja danych wejœciowych i prezentacji wyników
======================================================================================================================================================
Dane dotycz¹ce punktów mog¹ zostaæ wprowadzone ze standardowego wejœcia (dla trybu -m 1).
Powinny one mieæ tak¹ formê, ¿e kolejne wspó³rzêdne s¹ oddzielone za pomoc¹ whitespace, a kolejne pary liczb to wspó³rzêdne kolejnych punktów.

Przyk³ad:
1 	0
3.1 	8
0 	2.5
1 	1

Takie dane wygeneruj¹ nastêpuj¹ce punkty: (1, 0), (3.1, 8), (0, 2.5), (1, 1)
Takie same punkty zosta³yby wygenerowane dla nastêpuj¹cego wejœcia: 1 0 3.1 8 0 2.5 1 1
= = = = = =
Prezentacja wyników dla trybu -m 1, 2 jest taka sama i zale¿y w du¿ym stopni od tego czy program zosta³ wywo³any z flagami: -lines, -points, -time.
Bez wzglêdu na obecnoœæ tych flag, zawsze s¹ wyœwietlane: ile min ruchów(linii) potrzeba aby pokryæ dany zbiór punktów, oraz ile jest kombinacji, aby to wykonaæ takie minimalne pokrycie.

Przyk³ad:

MinCover: 15
UniqueSolutions: 2 (2615348736000) //przed nawiasem ile jest unikalnych rozwi¹zañ (nie bior¹c pod uwagê kolejnoœci usuwania kolejnych linii z rozwi¹zania)
= = = = = =
Gdyby zosta³e w³¹czone opcjonalne flagi -lines, -points, -time, mog³o by to wygl¹daæ tak:

Lines size: //-lines
0	1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	
0	0	0	1706	432	236	20	48	36	4	4	4	4	4	4	32	
Execution time: 101 //-time (czas wykonania generacji linii)

MinCover: 15
Execution time: 16 //-time (czas znalezienia minimalnego rozwi¹zania)

UniqueSolutions: 2 (2615348736000)
Execution time: 743 //-time (czas znalezienia iloœci rozwi¹zañ)
= = = = = =
Wyjœcie dla trybu -m 3 wygl¹da inaczej:
Kolejno, w tej samej linii, odzielone za pomoc¹ '\t', dla ka¿dej iteracji wypisywane s¹: 
	czas wykonania generacji linii,
	czas znalezienia minimalnego pokrycia,
	ile linii pokrywa dan¹ iteracje problemu, 
	czas znalezienia iloœci unikalnych rozwi¹zañ, 
	ile unikalnych rozwi¹zañ znaleziono.
Newline oddziela kolejne powtórzenia problemu.

Po wykonaniu wszystkich powtórzeñ wypisywane jest podsumowanie uœrednionych czasów wykonania ka¿dego z algorytmów dla ka¿dej z iteracji, oraz uœrednion¹ liczbê linii znalezionych w danej iteracji.

Przyk³ad dla ustawieñ -d 0.5 -r 2 -i 8 -step 25:

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
Opis metody rozwi¹zania i struktur danych
======================================================================================================================================================
Problem zosta³ podzielony na 3 zasadnicze podproblemy:
1. Odnalezienie wszystkich linii które zawieraj¹ 3 lub wiêcej punktów (nie ma sensu zapamiêtywaæ tych które maj¹ 2 lub mniej punktów, poniewa¿ takie linie mo¿na u³o¿yæ miêdzy ka¿dym z dowolnych punktów)
2. Odnalezienie minimalnej liczby linii pokrywaj¹cej wszystkie punkty
3. Odnalezienie wszystkich rozwi¹zañ, sk³adaj¹cych siê z liczby linii, która zosta³a okreœlona przez algorytm numer 2
= = = = = =
Zosta³y zastosowane nastêpuj¹ce struktury danych:
Line oraz Point
	Reprezentuj¹ linie i punkty. Ka¿da linia trzyma listê punktów, które ta linia zawiera. Podobnie ka¿dy punkt trzyma listê linii, kóte przecinaj¹ ten punkt.
	Dok³adniej ujmuj¹c to obie te struktury trzymaj¹ iteratory na t¹ drug¹, co jest mo¿liwe poniewa¿ punkty oraz linie s¹ trzymane w liœcie, której iteratory s¹ sta³e.
	Dziêki temu nie trzeba korzystaæ z pointerów, ani kopiowaæ obiektów.

PlaneXY
	Trzyma lisê punktów oraz wektor list które trzymaj¹c¹ linie. Ka¿dy indeks wektora odpowiada rozmiarowi danej linii (czyli iloœci trzymanych przez niego punktów).
	Dziêki temu linie s¹ zawsze posortowane wed³ug rozmiaru, co okazuje siê przydatne w trakcie dzia³ania algorytmu 2 i 3.
	Dostêpne s¹ metody które "niby wy³¹czaj¹" dan¹ linie - tzn. symuluj¹ uk³ad struktury danych tak jakby linia i wszystkie punkty które ona zawiera zosta³a usuniêta.
	Mo¿liwy jest tak¿e "splice" danych linii, co jest u¿ywane, aby przesun¹æ przetestowane ju¿ linie do innej struktury danych. Dziêki temu dana kombinacja linii jest sprawdzana max raz.
= = = = = =
Algorytm numer 1
	Aby móc rozwa¿aæ, które linie nale¿y wybraæ, aby spe³niæ warunki polecenia, trzeba je najpierw znaleŸæ. 
	W tym celu wybieram ze zbioru punktów dwa punkty, okreœlam na jakiej linii te dwa punkty le¿¹ i sprawdzam czy linia o takich parametrach nie zosta³a ju¿ rozwa¿ona. (to ostanie realizowane za pomoc¹ unordered_set)
	Jeœli taka linia rzeczywiœcie zosta³a ju¿ rozwa¿ona to wracam do pocz¹tku algorytmu wybieraj¹c dwa kolejne punkty.
	Nastêpnie dla wszystkich punktów za wyj¹tkiem tych ju¿ rozwa¿onych, sprawdzam czy nale¿¹ do rozwa¿anej linii. Jeœli tak to dodaje punkt do linii. 
	Po sprawdzeniu wszystkich punktów dla danej linii sprawdzam, czy le¿¹ na niej wiêcej ni¿ 2 punkty. Jeœli tak to liniê zapisujê i wracam do pocz¹tku algorytmu. 
	Postêpujê tak dopóki nie rozwa¿ê wszystkich par punktów.

Algorytm numer 2
	Przed w³aœciwym algorytmem znajdowania minimalnego pokrycia, nastêpuje preprocesing.
	Znajduje on punkty które nie le¿a na ¿adnej z linii znalezionych za pomoc¹ algorytmu 1, i odejmuje znalezion¹ liczbê od liczby punktów dla których szukane bêdzie rozwi¹zanie.
	Znajduje on tak¿e linie, które maj¹ co najmniej 2 punkty które s¹ przecinane tylko przez t¹ linie. Taka linia mo¿e zostaæ usuniêta z danych wejœciownych do w³aœciwego algorytmu.
	Po tych zabiegach nastêpuje przejœcie do w³aœciwej czêœci algorytmu.
	Algorytm przyjmuje liczbê punktów (n), przypuszczaln¹ liczbê linii (k), oraz zbiór linii wygenerowany algorytmem z pkt. 1 i poddany preprocesingowi. 
	Liczba punktów jest dana, natomiast jako parametr pocz¹tkowy k podawana jest liczba ceil(n/2) - czyli tak jakbyœmy nie przewidywali ¿adnych linii które zawieraj¹ wiêcej ni¿ 2 punkty.
	Dla ka¿dej linii która przecina wiêcej ni¿ ceil(c/k) punktów, po zasymulowaniu usuniêcia tej¿e linii i przerzucania jej do listy przetestowanych ju¿ linii wywo³ywany jest rekurencyjnie ten algorytm.
	Gdy rekurencja wraca, przetestowana linia jest "w³¹czana" (ale ca³y czas pozostaje w liœcie przetestownych) i wybierana jest kolejna linia.
	Kiedy znalezione zostaje rozwi¹zanie dla k linii, parametr k zostaje dekrementowany, a nowe stany s¹ rozwijane z ostrzejszym ograniczeniem.
	Gdy nie ma ju¿ stanów które mo¿naby rozwin¹æ zwracane jest najlepsze znalezione dotychczas rozwi¹zanie, a jeœli takiego nie ma -1.

Algorytm numer 3
	Pomys³ na algorytm do problemu numer 3 jest modyfikacj¹ algorytmu z punktu 2. 
	Podobnie przeszukujemy w g³¹b bez linii które nie zawieraj¹ wiêcej ni¿ n/k punktów. 
	Zmian¹ jest to, ¿e parametr k jest sta³y (wyliczony za pomoc¹ algorytmu numer 2), a zwracane jest nie nowe rozwi¹zanie, a liczba która reprezentuje ile unikalnych rozwi¹zañ zosta³o znalezionych.

======================================================================================================================================================
Pliki programu
======================================================================================================================================================
//TODO

======================================================================================================================================================
Dodatkowe zalecenia
======================================================================================================================================================
//TODO
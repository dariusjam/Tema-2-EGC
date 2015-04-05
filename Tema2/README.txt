Mangea Liviu Darius 334CA

World builder - aplicatie 3D pe a construi o mini-lume.

Tastele folosite sunt:

- a s d w - pentru scroll
- i j k l - pentru mutarea cursorului/obiectelor

- q - merge un pas inapoi in ierarhia de moduri de editare

- 1 - mod editare teren
- 2 - mod editare piete
- 3 - mod editare case
- 4 - mod editare drumuri

- b - adaugare pamant in mod editare teren
- n - adaugare apa in mod editare teren
- m - adaugare iarba in mod editare teren
- , - adaugare forma de relief in mod editare teren

- space - avansare in ierarhia de moduri de editare pentru adaugare
	teren, piete si drumuri
- f - finalizare adaugare piata sau casa

- c - revenirea scroll-ului in mijlocul hartii

- t - rotire casa in sens trigonometric
- y - rotire casa in sens anti-trigonometric

- r - generare random de teren (se poate folosi doar o data la inceputul
	jocului inainte de a adauga vreun obiect)


Platforma folosita a fost Visual Studio 2012 Ultimate.
Fisierele in care am scris cod sunt main.cpp si Transform3D.cpp in care
am adaugat transformarea izometrica.

Arhiva contine:
-Frameworkul din laborator in care au fost modificate fisierele main.cpp
si Transform3D.cpp pentru adaugarea transformarii izometrice.
-Fisier README

Implementarea transformarile de translatie si transformarea izometrica
aplicate obiectelor la fiecare pas in functia onIdle. In functia onKey
se afla o mare parte din cod deoarece in functie de tastele apasate se
executa diverse actiuni in cadrul jocului.

Functionalitati:

Functionalitati standard:
-Adaugare teren
-Adaugare piete
-Adaugare case
-Adaugare drum
-Scroll
-Cursor
-Transformare izometrica
-Rotatie case
-Indicare case conectate la piata
-Raza de acoperire piata vizibila cand la adaugare piata sau la adaugare
casa

Functionalitati bonus:
-Adaugare forme de relief
-Generare random a terenului daca se doreste
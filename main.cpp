#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data
{
public:
    string lastName;
    string firstName;
    string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename)
{

    ifstream input(filename);
    if (!input)
    {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;

    // Load the data
    for (int i = 0; i < size; i++)
    {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }

    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename)
{

    ofstream output(filename);
    if (!output)
    {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    // Write the size first
    int size = l.size();
    output << size << "\n";

    // Write the data
    for (auto pData : l)
    {
        output << pData->lastName << " "
               << pData->firstName << " "
               << pData->ssn << "\n";
    }

    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main()
{
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data *> theList;
    loadDataList(theList, filename);

    cout << "Data loaded.\n";

    cout << "Executing sort...\n";
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);

    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.
#include <unordered_map>

unordered_map<string, list<Data *>> lastNameBins;
string sortedLastNames[500] = {"ACOSTA", "ADAMS", "ADKINS", "AGUILAR", "AGUIRRE", "ALEXANDER", "ALLEN", "ALVARADO", "ALVAREZ", "ANDERSON", "ANDREWS", "ARMSTRONG", "ARNOLD", "AUSTIN", "AVILA", "AYALA", "BAILEY", "BAKER", "BALDWIN", "BANKS", "BARBER", "BARKER", "BARNES", "BARNETT", "BARRETT", "BARTON", "BATES", "BECK", "BECKER", "BELL", "BENNETT", "BENSON", "BERRY", "BISHOP", "BLACK", "BLAIR", "BLAKE", "BOWEN", "BOWMAN", "BOYD", "BRADLEY", "BRADY", "BREWER", "BROOKS", "BROWN", "BRYANT", "BURGESS", "BURKE", "BURNS", "BURTON", "BUSH", "BUTLER", "BYRD", "CABRERA", "CALDERON", "CALDWELL", "CAMACHO", "CAMPBELL", "CAMPOS", "CANNON", "CARDENAS", "CARLSON", "CARPENTER", "CARR", "CARRILLO", "CARROLL", "CARTER", "CASTANEDA", "CASTILLO", "CASTRO", "CERVANTES", "CHAMBERS", "CHAN", "CHANDLER", "CHANG", "CHAPMAN", "CHAVEZ", "CHEN", "CHRISTENSEN", "CLARK", "CLARKE", "COHEN", "COLE", "COLEMAN", "COLLINS", "COLON", "CONTRERAS", "COOK", "COOPER", "CORTEZ", "COX", "CRAIG", "CRAWFORD", "CROSS", "CRUZ", "CUMMINGS", "CUNNINGHAM", "CURRY", "CURTIS", "DANIEL", "DANIELS", "DAVIDSON", "DAVIS", "DAWSON", "DAY", "DEAN", "DELACRUZ", "DELEON", "DELGADO", "DENNIS", "DIAZ", "DIXON", "DOMINGUEZ", "DOUGLAS", "DOYLE", "DUNCAN", "DUNN", "DURAN", "EDWARDS", "ELLIOTT", "ELLIS", "ERICKSON", "ESPINOZA", "ESTRADA", "EVANS", "FARMER", "FERGUSON", "FERNANDEZ", "FIELDS", "FIGUEROA", "FISCHER", "FISHER", "FITZGERALD", "FLEMING", "FLETCHER", "FLORES", "FORD", "FOSTER", "FOWLER", "FOX", "FRANCIS", "FRANCO", "FRANK", "FRANKLIN", "FRAZIER", "FREEMAN", "FUENTES", "FULLER", "GALLAGHER", "GALLEGOS", "GARCIA", "GARDNER", "GARNER", "GARRETT", "GARZA", "GEORGE", "GIBSON", "GILBERT", "GILL", "GOMEZ", "GONZALES", "GONZALEZ", "GOODMAN", "GOODWIN", "GORDON", "GRAHAM", "GRANT", "GRAVES", "GRAY", "GREEN", "GREENE", "GREGORY", "GRIFFIN", "GRIFFITH", "GROSS", "GUERRA", "GUERRERO", "GUTIERREZ", "GUZMAN", "HAIL", "HALE", "HALL", "HAMILTON", "HAMMOND", "HAMPTON", "HANSEN", "HANSON", "HARDY", "HARMON", "HARPER", "HARRINGTON", "HARRIS", "HARRISON", "HART", "HARVEY", "HAWKINS", "HAYES", "HAYNES", "HENDERSON", "HENRY", "HERNANDEZ", "HERRERA", "HICKS", "HIGGINS", "HILL", "HINES", "HODGES", "HOFFMAN", "HOLLAND", "HOLMES", "HOLT", "HOPKINS", "HORTON", "HOWARD", "HOWELL", "HUANG", "HUBBARD", "HUDSON", "HUGHES", "HUNT", "HUNTER", "INGRAM", "JACKSON", "JACOBS", "JAMES", "JENKINS", "JENNINGS", "JENSEN", "JIMENEZ", "JOHNSON", "JOHNSTON", "JONES", "JORDAN", "JOSEPH", "JUAREZ", "KELLER", "KELLEY", "KELLY", "KENNEDY", "KHAN", "KIM", "KING", "KLEIN", "KNIGHT", "LAMBERT", "LANE", "LARA", "LARSON", "LAWRENCE", "LAWSON", "LE", "LEE", "LEON", "LEONARD", "LEWIS", "LI", "LIN", "LITTLE", "LIU", "LOGAN", "LONG", "LOPEZ", "LOVE", "LOWE", "LUCAS", "LUNA", "LYNCH", "LYONS", "MACK", "MALDONADO", "MALONE", "MANN", "MANNING", "MARQUEZ", "MARSHALL", "MARTIN", "MARTINEZ", "MASON", "MATTHEWS", "MAXWELL", "MAY", "MCCARTHY", "MCCOY", "MCDANIEL", "MCDONALD", "MCGEE", "MCKINNEY", "MCLAUGHLIN", "MEDINA", "MEJIA", "MENDEZ", "MENDOZA", "MEYER", "MILES", "MILLER", "MILLS", "MIRANDA", "MITCHELL", "MOLINA", "MONTGOMERY", "MONTOYA", "MOORE", "MORALES", "MORAN", "MORENO", "MORGAN", "MORRIS", "MORRISON", "MOSS", "MULLINS", "MUNOZ", "MURPHY", "MURRAY", "MYERS", "NAVARRO", "NEAL", "NELSON", "NEWMAN", "NEWTON", "NGUYEN", "NICHOLS", "NORMAN", "NORRIS", "NUNEZ", "OBRIEN", "OCHOA", "OCONNOR", "OLIVER", "OLSON", "ORTEGA", "ORTIZ", "OWENS", "PACHECO", "PADILLA", "PAGE", "PALMER", "PARK", "PARKER", "PARKS", "PARSONS", "PATEL", "PATTERSON", "PAUL", "PAYNE", "PEARSON", "PENA", "PEREZ", "PERKINS", "PERRY", "PERSON", "PETERS", "PETERSON", "PHAM", "PHILLIPS", "PIERCE", "PORTER", "POTTER", "POWELL", "POWERS", "PRICE", "QUINN", "RAMIREZ", "RAMOS", "RAMSEY", "RAY", "REED", "REESE", "REEVES", "REID", "REYES", "REYNOLDS", "RHODES", "RICE", "RICHARDS", "RICHARDSON", "RILEY", "RIOS", "RIVAS", "RIVERA", "ROBBINS", "ROBERTS", "ROBERTSON", "ROBINSON", "ROBLES", "RODGERS", "RODRIGUEZ", "ROGERS", "ROJAS", "ROMAN", "ROMERO", "ROSALES", "ROSE", "ROSS", "ROWE", "RUIZ", "RUSSELL", "RYAN", "SALAZAR", "SALINAS", "SANCHEZ", "SANDERS", "SANDOVAL", "SANTIAGO", "SANTOS", "SAUNDERS", "SCHMIDT", "SCHNEIDER", "SCHROEDER", "SCHULTZ", "SCHWARTZ", "SCOTT", "SERRANO", "SHARP", "SHAW", "SHELTON", "SHERMAN", "SILVA", "SIMMONS", "SIMON", "SIMPSON", "SIMS", "SINGH", "SMITH", "SNYDER", "SOLIS", "SOTO", "SPENCER", "STANLEY", "STEELE", "STEPHENS", "STEVENS", "STEVENSON", "STEWART", "STONE", "STRICKLAND", "SULLIVAN", "SUTTON", "SWANSON", "TATE", "TAYLOR", "TERRY", "THOMAS", "THOMPSON", "THORNTON", "TODD", "TORRES", "TOWNSEND", "TRAN", "TRUJILLO", "TUCKER", "TURNER", "VALDEZ", "VALENCIA", "VARGAS", "VASQUEZ", "VAUGHN", "VAZQUEZ", "VEGA", "VELASQUEZ", "WADE", "WAGNER", "WALKER", "WALLACE", "WALSH", "WALTERS", "WALTON", "WANG", "WARD", "WARNER", "WARREN", "WASHINGTON", "WATERS", "WATKINS", "WATSON", "WATTS", "WEAVER", "WEBB", "WEBER", "WEBSTER", "WELCH", "WELLS", "WEST", "WHEELER", "WHITE", "WILLIAMS", "WILLIAMSON", "WILLIS", "WILSON", "WISE", "WOLF", "WOLFE", "WONG", "WOOD", "WOODS", "WRIGHT", "WU", "YANG", "YOUNG", "ZHANG", "ZIMMERMAN"};
unordered_map<string, list<Data *>> firstNameBins;
string sortedFirstNames[500] = {"AALIYAH", "AARON", "ABEL", "ABIGAIL", "ABRAHAM", "ADALINE", "ADALYN", "ADALYNN", "ADAM", "ADDISON", "ADELINE", "ADELYN", "ADRIAN", "ADRIANA", "AIDAN", "AIDEN", "ALAINA", "ALAN", "ALANA", "ALAYNA", "ALEJANDRO", "ALEX", "ALEXA", "ALEXANDER", "ALEXANDRA", "ALEXIS", "ALICE", "ALINA", "ALIVIA", "ALIYAH", "ALLISON", "ALYSSA", "AMARA", "AMAYA", "AMELIA", "AMIR", "AMY", "ANA", "ANASTASIA", "ANDREA", "ANDRES", "ANDREW", "ANGEL", "ANGELA", "ANGELINA", "ANNA", "ANNABELLE", "ANTHONY", "ANTONIO", "ARABELLA", "ARIA", "ARIANA", "ARIANNA", "ARIEL", "ARTHUR", "ARYA", "ASHER", "ASHLEY", "ASHTON", "ATHENA", "AUBREE", "AUBREY", "AUDREY", "AUGUST", "AURORA", "AUSTIN", "AUTUMN", "AVA", "AVERY", "AVERY", "AXEL", "AYDEN", "AYLA", "BAILEY", "BARRETT", "BEAU", "BECKETT", "BELLA", "BENJAMIN", "BENNETT", "BENTLEY", "BLAKE", "BRADLEY", "BRADY", "BRANDON", "BRANTLEY", "BRAXTON", "BRAYDEN", "BRIAN", "BRIANNA", "BRIELLE", "BRODY", "BROOKE", "BROOKLYN", "BROOKLYNN", "BROOKS", "BRYAN", "BRYCE", "BRYNLEE", "BRYSON", "CADEN", "CALEB", "CALLIE", "CALVIN", "CAMDEN", "CAMERON", "CAMILA", "CARLOS", "CAROLINE", "CARSON", "CARTER", "CATHERINE", "CAYDEN", "CECILIA", "CHARLES", "CHARLIE", "CHARLIE", "CHARLOTTE", "CHASE", "CHLOE", "CHRISTIAN", "CHRISTOPHER", "CLAIRE", "CLARA", "CLAYTON", "COLE", "COLIN", "COLTON", "CONNOR", "COOPER", "CORA", "DAISY", "DAKOTA", "DALEYZA", "DAMIAN", "DANIEL", "DANIELA", "DAVID", "DAWSON", "DEAN", "DECLAN", "DELANEY", "DELILAH", "DEREK", "DESTINY", "DIANA", "DIEGO", "DOMINIC", "DYLAN", "EASTON", "EDEN", "EDWARD", "ELEANOR", "ELENA", "ELI", "ELIANA", "ELIAS", "ELIJAH", "ELISE", "ELIZA", "ELIZABETH", "ELLA", "ELLIANA", "ELLIE", "ELLIOT", "ELLIOTT", "ELOISE", "EMERSON", "EMERSYN", "EMERY", "EMILIA", "EMILIANO", "EMILY", "EMMA", "EMMANUEL", "EMMETT", "ERIC", "ESTHER", "ETHAN", "EVA", "EVAN", "EVELYN", "EVERETT", "EVERLY", "EZEKIEL", "EZRA", "FAITH", "FELIX", "FINLEY", "FINN", "FIONA", "GABRIEL", "GABRIELLA", "GAEL", "GAVIN", "GENESIS", "GENEVIEVE", "GEORGE", "GEORGIA", "GIANNA", "GIOVANNI", "GRACE", "GRACIE", "GRAHAM", "GRANT", "GRAYSON", "GREYSON", "GRIFFIN", "HADLEY", "HAILEY", "HANNAH", "HARLEY", "HARMONY", "HARPER", "HARRISON", "HAYDEN", "HAYDEN", "HAZEL", "HENRY", "HOLDEN", "HUDSON", "HUNTER", "IAN", "IRIS", "ISAAC", "ISABEL", "ISABELLA", "ISABELLE", "ISAIAH", "ISLA", "ISRAEL", "IVAN", "IVY", "JACE", "JACK", "JACKSON", "JACOB", "JADE", "JADEN", "JAKE", "JAMES", "JAMESON", "JASMINE", "JASON", "JASPER", "JAVIER", "JAX", "JAXON", "JAXSON", "JAYCE", "JAYDEN", "JAYLA", "JEREMIAH", "JEREMY", "JESSE", "JESSICA", "JESUS", "JOANNA", "JOCELYN", "JOEL", "JOHN", "JONAH", "JONATHAN", "JORDAN", "JORDYN", "JORGE", "JOSE", "JOSEPH", "JOSEPHINE", "JOSHUA", "JOSIAH", "JOSIE", "JOSUE", "JUAN", "JUDAH", "JUDE", "JULIA", "JULIAN", "JULIANA", "JULIANNA", "JULIET", "JULIETTE", "JUNE", "JUSTIN", "KADEN", "KAI", "KAIDEN", "KALEB", "KARTER", "KATHERINE", "KAYDEN", "KAYLA", "KAYLEE", "KENDALL", "KENNEDY", "KENNETH", "KEVIN", "KHLOE", "KILLIAN", "KIMBERLY", "KING", "KINGSTON", "KINSLEY", "KNOX", "KYLE", "KYLIE", "KYRIE", "LAILA", "LANDON", "LAUREN", "LAYLA", "LEAH", "LEILA", "LEILANI", "LEO", "LEON", "LEONARDO", "LEVI", "LIAM", "LILA", "LILIANA", "LILLIAN", "LILLY", "LILY", "LINCOLN", "LOGAN", "LOLA", "LONDON", "LONDYN", "LORENZO", "LUCA", "LUCAS", "LUCIA", "LUCY", "LUIS", "LUKAS", "LUKE", "LUNA", "LYDIA", "LYLA", "MACKENZIE", "MADDOX", "MADELINE", "MADELYN", "MADISON", "MAGGIE", "MAKAYLA", "MALACHI", "MALIA", "MARCUS", "MARGARET", "MARIA", "MARIAH", "MARK", "MARLEY", "MARY", "MASON", "MATEO", "MATIAS", "MATTEO", "MATTHEW", "MAVERICK", "MAX", "MAXIMUS", "MAXWELL", "MAYA", "MCKENZIE", "MELANIE", "MELODY", "MESSIAH", "MIA", "MICAH", "MICHAEL", "MICHELLE", "MIGUEL", "MILA", "MILES", "MILO", "MOLLY", "MORGAN", "MYA", "MYLES", "NAOMI", "NATALIA", "NATALIE", "NATHAN", "NATHANIEL", "NEVAEH", "NICHOLAS", "NICOLAS", "NICOLE", "NOAH", "NOELLE", "NOLAN", "NORA", "NORAH", "NOVA", "OLIVER", "OLIVIA", "OMAR", "OSCAR", "OWEN", "PAIGE", "PAISLEY", "PARKER", "PARKER", "PATRICK", "PAUL", "PAXTON", "PAYTON", "PENELOPE", "PETER", "PEYTON", "PIPER", "PRESLEY", "PRESTON", "QUINN", "RACHEL", "RAELYNN", "REAGAN", "REBECCA", "REESE", "REMI", "REMINGTON", "RHETT", "RICHARD", "RILEY", "RIVER", "ROBERT", "ROMAN", "ROSALIE", "ROSE", "ROWAN", "ROWAN", "RUBY", "RYAN", "RYDER", "RYKER", "RYLEE", "RYLEIGH", "SADIE", "SAMANTHA", "SAMUEL", "SANTIAGO", "SARA", "SARAH", "SAVANNAH", "SAWYER", "SAWYER", "SCARLETT", "SEBASTIAN", "SELENA", "SERENITY", "SIENNA", "SILAS", "SKYLAR", "SLOANE", "SOFIA", "SOPHIA", "SOPHIE", "STELLA", "STEVEN", "SUMMER", "SYDNEY", "TAYLOR", "TEAGAN", "TESSA", "THEODORE", "THIAGO", "THOMAS", "TIMOTHY", "TRINITY", "TRISTAN", "TUCKER", "TYLER", "VALENTINA", "VALERIA", "VALERIE", "VANESSA", "VICTOR", "VICTORIA", "VINCENT", "VIOLET", "VIVIAN", "WAYLON", "WESLEY", "WESTON", "WILLIAM", "WILLOW", "WYATT", "XANDER", "XAVIER", "XIMENA", "ZACHARY", "ZANDER", "ZANE", "ZAYDEN", "ZION", "ZOE", "ZOEY"};

vector<Data *> x[26][26][26][26];

int getTestCase(list<Data *> &l)
{
    if (l.front()->lastName == l.back()->lastName && l.front()->firstName == l.back()->firstName)
    {
        return 4;
    }
    else if (l.front()->lastName[0] == 'A' && l.back()->lastName[0] == 'Z' && l.front()->firstName[0] == 'A' && l.back()->firstName[0] == 'Z')
    {
        return 3;
    }
    else
    {
        return 1;
    }
}

void initializeBins()
{
    list<Data *> temp;
    for (int i = 0; i < 500; i++)
    {
        lastNameBins[sortedLastNames[i]] = temp;
    }
    for (int i = 0; i < 500; i++)
    {
        firstNameBins[sortedFirstNames[i]] = temp;
    }
}

bool compare(Data *d1, Data *d2)
{
    int lastNameCmp = strcmp(d1->lastName.c_str(), d2->lastName.c_str());

    if (lastNameCmp != 0)
    {
        return lastNameCmp < 0;
    }

    int firstNameCmp = strcmp(d1->firstName.c_str(), d2->firstName.c_str());

    if (firstNameCmp != 0)
    {
        return firstNameCmp < 0;
    }

    return strcmp(d1->ssn.c_str(), d2->ssn.c_str()) < 0;
}

void t1t2(list<Data *> &l)
{
    vector<Data *> ACOSTA;
    vector<Data *> ADAMS;
    vector<Data *> ADKINS;
    vector<Data *> AGUILAR;
    vector<Data *> AGUIRRE;
    vector<Data *> ALEXANDER;
    vector<Data *> ALLEN;
    vector<Data *> ALVARADO;
    vector<Data *> ALVAREZ;
    vector<Data *> ANDERSON;
    vector<Data *> ANDREWS;
    vector<Data *> ARMSTRONG;
    vector<Data *> ARNOLD;
    vector<Data *> AUSTIN;
    vector<Data *> AVILA;
    vector<Data *> AYALA;
    vector<Data *> BAILEY;
    vector<Data *> BAKER;
    vector<Data *> BALDWIN;
    vector<Data *> BANKS;
    vector<Data *> BARBER;
    vector<Data *> BARKER;
    vector<Data *> BARNES;
    vector<Data *> BARNETT;
    vector<Data *> BARRETT;
    vector<Data *> BARTON;
    vector<Data *> BATES;
    vector<Data *> BECK;
    vector<Data *> BECKER;
    vector<Data *> BELL;
    vector<Data *> BENNETT;
    vector<Data *> BENSON;
    vector<Data *> BERRY;
    vector<Data *> BISHOP;
    vector<Data *> BLACK;
    vector<Data *> BLAIR;
    vector<Data *> BLAKE;
    vector<Data *> BOWEN;
    vector<Data *> BOWMAN;
    vector<Data *> BOYD;
    vector<Data *> BRADLEY;
    vector<Data *> BRADY;
    vector<Data *> BREWER;
    vector<Data *> BROOKS;
    vector<Data *> BROWN;
    vector<Data *> BRYANT;
    vector<Data *> BURGESS;
    vector<Data *> BURKE;
    vector<Data *> BURNS;
    vector<Data *> BURTON;
    vector<Data *> BUSH;
    vector<Data *> BUTLER;
    vector<Data *> BYRD;
    vector<Data *> CABRERA;
    vector<Data *> CALDERON;
    vector<Data *> CALDWELL;
    vector<Data *> CAMACHO;
    vector<Data *> CAMPBELL;
    vector<Data *> CAMPOS;
    vector<Data *> CANNON;
    vector<Data *> CARDENAS;
    vector<Data *> CARLSON;
    vector<Data *> CARPENTER;
    vector<Data *> CARR;
    vector<Data *> CARRILLO;
    vector<Data *> CARROLL;
    vector<Data *> CARTER;
    vector<Data *> CASTANEDA;
    vector<Data *> CASTILLO;
    vector<Data *> CASTRO;
    vector<Data *> CERVANTES;
    vector<Data *> CHAMBERS;
    vector<Data *> CHAN;
    vector<Data *> CHANDLER;
    vector<Data *> CHANG;
    vector<Data *> CHAPMAN;
    vector<Data *> CHAVEZ;
    vector<Data *> CHEN;
    vector<Data *> CHRISTENSEN;
    vector<Data *> CLARK;
    vector<Data *> CLARKE;
    vector<Data *> COHEN;
    vector<Data *> COLE;
    vector<Data *> COLEMAN;
    vector<Data *> COLLINS;
    vector<Data *> COLON;
    vector<Data *> CONTRERAS;
    vector<Data *> COOK;
    vector<Data *> COOPER;
    vector<Data *> CORTEZ;
    vector<Data *> COX;
    vector<Data *> CRAIG;
    vector<Data *> CRAWFORD;
    vector<Data *> CROSS;
    vector<Data *> CRUZ;
    vector<Data *> CUMMINGS;
    vector<Data *> CUNNINGHAM;
    vector<Data *> CURRY;
    vector<Data *> CURTIS;
    vector<Data *> DANIEL;
    vector<Data *> DANIELS;
    vector<Data *> DAVIDSON;
    vector<Data *> DAVIS;
    vector<Data *> DAWSON;
    vector<Data *> DAY;
    vector<Data *> DEAN;
    vector<Data *> DELACRUZ;
    vector<Data *> DELEON;
    vector<Data *> DELGADO;
    vector<Data *> DENNIS;
    vector<Data *> DIAZ;
    vector<Data *> DIXON;
    vector<Data *> DOMINGUEZ;
    vector<Data *> DOUGLAS;
    vector<Data *> DOYLE;
    vector<Data *> DUNCAN;
    vector<Data *> DUNN;
    vector<Data *> DURAN;
    vector<Data *> EDWARDS;
    vector<Data *> ELLIOTT;
    vector<Data *> ELLIS;
    vector<Data *> ERICKSON;
    vector<Data *> ESPINOZA;
    vector<Data *> ESTRADA;
    vector<Data *> EVANS;
    vector<Data *> FARMER;
    vector<Data *> FERGUSON;
    vector<Data *> FERNANDEZ;
    vector<Data *> FIELDS;
    vector<Data *> FIGUEROA;
    vector<Data *> FISCHER;
    vector<Data *> FISHER;
    vector<Data *> FITZGERALD;
    vector<Data *> FLEMING;
    vector<Data *> FLETCHER;
    vector<Data *> FLORES;
    vector<Data *> FORD;
    vector<Data *> FOSTER;
    vector<Data *> FOWLER;
    vector<Data *> FOX;
    vector<Data *> FRANCIS;
    vector<Data *> FRANCO;
    vector<Data *> FRANK;
    vector<Data *> FRANKLIN;
    vector<Data *> FRAZIER;
    vector<Data *> FREEMAN;
    vector<Data *> FUENTES;
    vector<Data *> FULLER;
    vector<Data *> GALLAGHER;
    vector<Data *> GALLEGOS;
    vector<Data *> GARCIA;
    vector<Data *> GARDNER;
    vector<Data *> GARNER;
    vector<Data *> GARRETT;
    vector<Data *> GARZA;
    vector<Data *> GEORGE;
    vector<Data *> GIBSON;
    vector<Data *> GILBERT;
    vector<Data *> GILL;
    vector<Data *> GOMEZ;
    vector<Data *> GONZALES;
    vector<Data *> GONZALEZ;
    vector<Data *> GOODMAN;
    vector<Data *> GOODWIN;
    vector<Data *> GORDON;
    vector<Data *> GRAHAM;
    vector<Data *> GRANT;
    vector<Data *> GRAVES;
    vector<Data *> GRAY;
    vector<Data *> GREEN;
    vector<Data *> GREENE;
    vector<Data *> GREGORY;
    vector<Data *> GRIFFIN;
    vector<Data *> GRIFFITH;
    vector<Data *> GROSS;
    vector<Data *> GUERRA;
    vector<Data *> GUERRERO;
    vector<Data *> GUTIERREZ;
    vector<Data *> GUZMAN;
    vector<Data *> HAIL;
    vector<Data *> HALE;
    vector<Data *> HALL;
    vector<Data *> HAMILTON;
    vector<Data *> HAMMOND;
    vector<Data *> HAMPTON;
    vector<Data *> HANSEN;
    vector<Data *> HANSON;
    vector<Data *> HARDY;
    vector<Data *> HARMON;
    vector<Data *> HARPER;
    vector<Data *> HARRINGTON;
    vector<Data *> HARRIS;
    vector<Data *> HARRISON;
    vector<Data *> HART;
    vector<Data *> HARVEY;
    vector<Data *> HAWKINS;
    vector<Data *> HAYES;
    vector<Data *> HAYNES;
    vector<Data *> HENDERSON;
    vector<Data *> HENRY;
    vector<Data *> HERNANDEZ;
    vector<Data *> HERRERA;
    vector<Data *> HICKS;
    vector<Data *> HIGGINS;
    vector<Data *> HILL;
    vector<Data *> HINES;
    vector<Data *> HODGES;
    vector<Data *> HOFFMAN;
    vector<Data *> HOLLAND;
    vector<Data *> HOLMES;
    vector<Data *> HOLT;
    vector<Data *> HOPKINS;
    vector<Data *> HORTON;
    vector<Data *> HOWARD;
    vector<Data *> HOWELL;
    vector<Data *> HUANG;
    vector<Data *> HUBBARD;
    vector<Data *> HUDSON;
    vector<Data *> HUGHES;
    vector<Data *> HUNT;
    vector<Data *> HUNTER;
    vector<Data *> INGRAM;
    vector<Data *> JACKSON;
    vector<Data *> JACOBS;
    vector<Data *> JAMES;
    vector<Data *> JENKINS;
    vector<Data *> JENNINGS;
    vector<Data *> JENSEN;
    vector<Data *> JIMENEZ;
    vector<Data *> JOHNSON;
    vector<Data *> JOHNSTON;
    vector<Data *> JONES;
    vector<Data *> JORDAN;
    vector<Data *> JOSEPH;
    vector<Data *> JUAREZ;
    vector<Data *> KELLER;
    vector<Data *> KELLEY;
    vector<Data *> KELLY;
    vector<Data *> KENNEDY;
    vector<Data *> KHAN;
    vector<Data *> KIM;
    vector<Data *> KING;
    vector<Data *> KLEIN;
    vector<Data *> KNIGHT;
    vector<Data *> LAMBERT;
    vector<Data *> LANE;
    vector<Data *> LARA;
    vector<Data *> LARSON;
    vector<Data *> LAWRENCE;
    vector<Data *> LAWSON;
    vector<Data *> LE;
    vector<Data *> LEE;
    vector<Data *> LEON;
    vector<Data *> LEONARD;
    vector<Data *> LEWIS;
    vector<Data *> LI;
    vector<Data *> LIN;
    vector<Data *> LITTLE;
    vector<Data *> LIU;
    vector<Data *> LOGAN;
    vector<Data *> LONG;
    vector<Data *> LOPEZ;
    vector<Data *> LOVE;
    vector<Data *> LOWE;
    vector<Data *> LUCAS;
    vector<Data *> LUNA;
    vector<Data *> LYNCH;
    vector<Data *> LYONS;
    vector<Data *> MACK;
    vector<Data *> MALDONADO;
    vector<Data *> MALONE;
    vector<Data *> MANN;
    vector<Data *> MANNING;
    vector<Data *> MARQUEZ;
    vector<Data *> MARSHALL;
    vector<Data *> MARTIN;
    vector<Data *> MARTINEZ;
    vector<Data *> MASON;
    vector<Data *> MATTHEWS;
    vector<Data *> MAXWELL;
    vector<Data *> MAY;
    vector<Data *> MCCARTHY;
    vector<Data *> MCCOY;
    vector<Data *> MCDANIEL;
    vector<Data *> MCDONALD;
    vector<Data *> MCGEE;
    vector<Data *> MCKINNEY;
    vector<Data *> MCLAUGHLIN;
    vector<Data *> MEDINA;
    vector<Data *> MEJIA;
    vector<Data *> MENDEZ;
    vector<Data *> MENDOZA;
    vector<Data *> MEYER;
    vector<Data *> MILES;
    vector<Data *> MILLER;
    vector<Data *> MILLS;
    vector<Data *> MIRANDA;
    vector<Data *> MITCHELL;
    vector<Data *> MOLINA;
    vector<Data *> MONTGOMERY;
    vector<Data *> MONTOYA;
    vector<Data *> MOORE;
    vector<Data *> MORALES;
    vector<Data *> MORAN;
    vector<Data *> MORENO;
    vector<Data *> MORGAN;
    vector<Data *> MORRIS;
    vector<Data *> MORRISON;
    vector<Data *> MOSS;
    vector<Data *> MULLINS;
    vector<Data *> MUNOZ;
    vector<Data *> MURPHY;
    vector<Data *> MURRAY;
    vector<Data *> MYERS;
    vector<Data *> NAVARRO;
    vector<Data *> NEAL;
    vector<Data *> NELSON;
    vector<Data *> NEWMAN;
    vector<Data *> NEWTON;
    vector<Data *> NGUYEN;
    vector<Data *> NICHOLS;
    vector<Data *> NORMAN;
    vector<Data *> NORRIS;
    vector<Data *> NUNEZ;
    vector<Data *> OBRIEN;
    vector<Data *> OCHOA;
    vector<Data *> OCONNOR;
    vector<Data *> OLIVER;
    vector<Data *> OLSON;
    vector<Data *> ORTEGA;
    vector<Data *> ORTIZ;
    vector<Data *> OWENS;
    vector<Data *> PACHECO;
    vector<Data *> PADILLA;
    vector<Data *> PAGE;
    vector<Data *> PALMER;
    vector<Data *> PARK;
    vector<Data *> PARKER;
    vector<Data *> PARKS;
    vector<Data *> PARSONS;
    vector<Data *> PATEL;
    vector<Data *> PATTERSON;
    vector<Data *> PAUL;
    vector<Data *> PAYNE;
    vector<Data *> PEARSON;
    vector<Data *> PENA;
    vector<Data *> PEREZ;
    vector<Data *> PERKINS;
    vector<Data *> PERRY;
    vector<Data *> PERSON;
    vector<Data *> PETERS;
    vector<Data *> PETERSON;
    vector<Data *> PHAM;
    vector<Data *> PHILLIPS;
    vector<Data *> PIERCE;
    vector<Data *> PORTER;
    vector<Data *> POTTER;
    vector<Data *> POWELL;
    vector<Data *> POWERS;
    vector<Data *> PRICE;
    vector<Data *> QUINN;
    vector<Data *> RAMIREZ;
    vector<Data *> RAMOS;
    vector<Data *> RAMSEY;
    vector<Data *> RAY;
    vector<Data *> REED;
    vector<Data *> REESE;
    vector<Data *> REEVES;
    vector<Data *> REID;
    vector<Data *> REYES;
    vector<Data *> REYNOLDS;
    vector<Data *> RHODES;
    vector<Data *> RICE;
    vector<Data *> RICHARDS;
    vector<Data *> RICHARDSON;
    vector<Data *> RILEY;
    vector<Data *> RIOS;
    vector<Data *> RIVAS;
    vector<Data *> RIVERA;
    vector<Data *> ROBBINS;
    vector<Data *> ROBERTS;
    vector<Data *> ROBERTSON;
    vector<Data *> ROBINSON;
    vector<Data *> ROBLES;
    vector<Data *> RODGERS;
    vector<Data *> RODRIGUEZ;
    vector<Data *> ROGERS;
    vector<Data *> ROJAS;
    vector<Data *> ROMAN;
    vector<Data *> ROMERO;
    vector<Data *> ROSALES;
    vector<Data *> ROSE;
    vector<Data *> ROSS;
    vector<Data *> ROWE;
    vector<Data *> RUIZ;
    vector<Data *> RUSSELL;
    vector<Data *> RYAN;
    vector<Data *> SALAZAR;
    vector<Data *> SALINAS;
    vector<Data *> SANCHEZ;
    vector<Data *> SANDERS;
    vector<Data *> SANDOVAL;
    vector<Data *> SANTIAGO;
    vector<Data *> SANTOS;
    vector<Data *> SAUNDERS;
    vector<Data *> SCHMIDT;
    vector<Data *> SCHNEIDER;
    vector<Data *> SCHROEDER;
    vector<Data *> SCHULTZ;
    vector<Data *> SCHWARTZ;
    vector<Data *> SCOTT;
    vector<Data *> SERRANO;
    vector<Data *> SHARP;
    vector<Data *> SHAW;
    vector<Data *> SHELTON;
    vector<Data *> SHERMAN;
    vector<Data *> SILVA;
    vector<Data *> SIMMONS;
    vector<Data *> SIMON;
    vector<Data *> SIMPSON;
    vector<Data *> SIMS;
    vector<Data *> SINGH;
    vector<Data *> SMITH;
    vector<Data *> SNYDER;
    vector<Data *> SOLIS;
    vector<Data *> SOTO;
    vector<Data *> SPENCER;
    vector<Data *> STANLEY;
    vector<Data *> STEELE;
    vector<Data *> STEPHENS;
    vector<Data *> STEVENS;
    vector<Data *> STEVENSON;
    vector<Data *> STEWART;
    vector<Data *> STONE;
    vector<Data *> STRICKLAND;
    vector<Data *> SULLIVAN;
    vector<Data *> SUTTON;
    vector<Data *> SWANSON;
    vector<Data *> TATE;
    vector<Data *> TAYLOR;
    vector<Data *> TERRY;
    vector<Data *> THOMAS;
    vector<Data *> THOMPSON;
    vector<Data *> THORNTON;
    vector<Data *> TODD;
    vector<Data *> TORRES;
    vector<Data *> TOWNSEND;
    vector<Data *> TRAN;
    vector<Data *> TRUJILLO;
    vector<Data *> TUCKER;
    vector<Data *> TURNER;
    vector<Data *> VALDEZ;
    vector<Data *> VALENCIA;
    vector<Data *> VARGAS;
    vector<Data *> VASQUEZ;
    vector<Data *> VAUGHN;
    vector<Data *> VAZQUEZ;
    vector<Data *> VEGA;
    vector<Data *> VELASQUEZ;
    vector<Data *> WADE;
    vector<Data *> WAGNER;
    vector<Data *> WALKER;
    vector<Data *> WALLACE;
    vector<Data *> WALSH;
    vector<Data *> WALTERS;
    vector<Data *> WALTON;
    vector<Data *> WANG;
    vector<Data *> WARD;
    vector<Data *> WARNER;
    vector<Data *> WARREN;
    vector<Data *> WASHINGTON;
    vector<Data *> WATERS;
    vector<Data *> WATKINS;
    vector<Data *> WATSON;
    vector<Data *> WATTS;
    vector<Data *> WEAVER;
    vector<Data *> WEBB;
    vector<Data *> WEBER;
    vector<Data *> WEBSTER;
    vector<Data *> WELCH;
    vector<Data *> WELLS;
    vector<Data *> WEST;
    vector<Data *> WHEELER;
    vector<Data *> WHITE;
    vector<Data *> WILLIAMS;
    vector<Data *> WILLIAMSON;
    vector<Data *> WILLIS;
    vector<Data *> WILSON;
    vector<Data *> WISE;
    vector<Data *> WOLF;
    vector<Data *> WOLFE;
    vector<Data *> WONG;
    vector<Data *> WOOD;
    vector<Data *> WOODS;
    vector<Data *> WRIGHT;
    vector<Data *> WU;
    vector<Data *> YANG;
    vector<Data *> YOUNG;
    vector<Data *> ZHANG;
    vector<Data *> ZIMMERMAN;

    for (auto &data : l)
    {
        switch (index)
        {
        case 0:
            ACOSTA.push_back(data);
            break;
        case 1:
            ADAMS.push_back(data);
            break;
        case 2:
            ADKINS.push_back(data);
            break;
        case 3:
            AGUILAR.push_back(data);
            break;
        case 4:
            AGUIRRE.push_back(data);
            break;
        case 5:
            ALEXANDER.push_back(data);
            break;
        case 6:
            ALLEN.push_back(data);
            break;
        case 7:
            ALVARADO.push_back(data);
            break;
        case 8:
            ALVAREZ.push_back(data);
            break;
        case 9:
            ANDERSON.push_back(data);
            break;
        case 10:
            ANDREWS.push_back(data);
            break;
        case 11:
            ARMSTRONG.push_back(data);
            break;
        case 12:
            ARNOLD.push_back(data);
            break;
        case 13:
            AUSTIN.push_back(data);
            break;
        case 14:
            AVILA.push_back(data);
            break;
        case 15:
            AYALA.push_back(data);
            break;
        case 16:
            BAILEY.push_back(data);
            break;
        case 17:
            BAKER.push_back(data);
            break;
        case 18:
            BALDWIN.push_back(data);
            break;
        case 19:
            BANKS.push_back(data);
            break;
        case 20:
            BARBER.push_back(data);
            break;
        case 21:
            BARKER.push_back(data);
            break;
        case 22:
            BARNES.push_back(data);
            break;
        case 23:
            BARNETT.push_back(data);
            break;
        case 24:
            BARRETT.push_back(data);
            break;
        case 25:
            BARTON.push_back(data);
            break;
        case 26:
            BATES.push_back(data);
            break;
        case 27:
            BECK.push_back(data);
            break;
        case 28:
            BECKER.push_back(data);
            break;
        case 29:
            BELL.push_back(data);
            break;
        case 30:
            BENNETT.push_back(data);
            break;
        case 31:
            BENSON.push_back(data);
            break;
        case 32:
            BERRY.push_back(data);
            break;
        case 33:
            BISHOP.push_back(data);
            break;
        case 34:
            BLACK.push_back(data);
            break;
        case 35:
            BLAIR.push_back(data);
            break;
        case 36:
            BLAKE.push_back(data);
            break;
        case 37:
            BOWEN.push_back(data);
            break;
        case 38:
            BOWMAN.push_back(data);
            break;
        case 39:
            BOYD.push_back(data);
            break;
        case 40:
            BRADLEY.push_back(data);
            break;
        case 41:
            BRADY.push_back(data);
            break;
        case 42:
            BREWER.push_back(data);
            break;
        case 43:
            BROOKS.push_back(data);
            break;
        case 44:
            BROWN.push_back(data);
            break;
        case 45:
            BRYANT.push_back(data);
            break;
        case 46:
            BURGESS.push_back(data);
            break;
        case 47:
            BURKE.push_back(data);
            break;
        case 48:
            BURNS.push_back(data);
            break;
        case 49:
            BURTON.push_back(data);
            break;
        case 50:
            BUSH.push_back(data);
            break;
        case 51:
            BUTLER.push_back(data);
            break;
        case 52:
            BYRD.push_back(data);
            break;
        case 53:
            CABRERA.push_back(data);
            break;
        case 54:
            CALDERON.push_back(data);
            break;
        case 55:
            CALDWELL.push_back(data);
            break;
        case 56:
            CAMACHO.push_back(data);
            break;
        case 57:
            CAMPBELL.push_back(data);
            break;
        case 58:
            CAMPOS.push_back(data);
            break;
        case 59:
            CANNON.push_back(data);
            break;
        case 60:
            CARDENAS.push_back(data);
            break;
        case 61:
            CARLSON.push_back(data);
            break;
        case 62:
            CARPENTER.push_back(data);
            break;
        case 63:
            CARR.push_back(data);
            break;
        case 64:
            CARRILLO.push_back(data);
            break;
        case 65:
            CARROLL.push_back(data);
            break;
        case 66:
            CARTER.push_back(data);
            break;
        case 67:
            CASTANEDA.push_back(data);
            break;
        case 68:
            CASTILLO.push_back(data);
            break;
        case 69:
            CASTRO.push_back(data);
            break;
        case 70:
            CERVANTES.push_back(data);
            break;
        case 71:
            CHAMBERS.push_back(data);
            break;
        case 72:
            CHAN.push_back(data);
            break;
        case 73:
            CHANDLER.push_back(data);
            break;
        case 74:
            CHANG.push_back(data);
            break;
        case 75:
            CHAPMAN.push_back(data);
            break;
        case 76:
            CHAVEZ.push_back(data);
            break;
        case 77:
            CHEN.push_back(data);
            break;
        case 78:
            CHRISTENSEN.push_back(data);
            break;
        case 79:
            CLARK.push_back(data);
            break;
        case 80:
            CLARKE.push_back(data);
            break;
        case 81:
            COHEN.push_back(data);
            break;
        case 82:
            COLE.push_back(data);
            break;
        case 83:
            COLEMAN.push_back(data);
            break;
        case 84:
            COLLINS.push_back(data);
            break;
        case 85:
            COLON.push_back(data);
            break;
        case 86:
            CONTRERAS.push_back(data);
            break;
        case 87:
            COOK.push_back(data);
            break;
        case 88:
            COOPER.push_back(data);
            break;
        case 89:
            CORTEZ.push_back(data);
            break;
        case 90:
            COX.push_back(data);
            break;
        case 91:
            CRAIG.push_back(data);
            break;
        case 92:
            CRAWFORD.push_back(data);
            break;
        case 93:
            CROSS.push_back(data);
            break;
        case 94:
            CRUZ.push_back(data);
            break;
        case 95:
            CUMMINGS.push_back(data);
            break;
        case 96:
            CUNNINGHAM.push_back(data);
            break;
        case 97:
            CURRY.push_back(data);
            break;
        case 98:
            CURTIS.push_back(data);
            break;
        case 99:
            DANIEL.push_back(data);
            break;
        case 100:
            DANIELS.push_back(data);
            break;
        case 101:
            DAVIDSON.push_back(data);
            break;
        case 102:
            DAVIS.push_back(data);
            break;
        case 103:
            DAWSON.push_back(data);
            break;
        case 104:
            DAY.push_back(data);
            break;
        case 105:
            DEAN.push_back(data);
            break;
        case 106:
            DELACRUZ.push_back(data);
            break;
        case 107:
            DELEON.push_back(data);
            break;
        case 108:
            DELGADO.push_back(data);
            break;
        case 109:
            DENNIS.push_back(data);
            break;
        case 110:
            DIAZ.push_back(data);
            break;
        case 111:
            DIXON.push_back(data);
            break;
        case 112:
            DOMINGUEZ.push_back(data);
            break;
        case 113:
            DOUGLAS.push_back(data);
            break;
        case 114:
            DOYLE.push_back(data);
            break;
        case 115:
            DUNCAN.push_back(data);
            break;
        case 116:
            DUNN.push_back(data);
            break;
        case 117:
            DURAN.push_back(data);
            break;
        case 118:
            EDWARDS.push_back(data);
            break;
        case 119:
            ELLIOTT.push_back(data);
            break;
        case 120:
            ELLIS.push_back(data);
            break;
        case 121:
            ERICKSON.push_back(data);
            break;
        case 122:
            ESPINOZA.push_back(data);
            break;
        case 123:
            ESTRADA.push_back(data);
            break;
        case 124:
            EVANS.push_back(data);
            break;
        case 125:
            FARMER.push_back(data);
            break;
        case 126:
            FERGUSON.push_back(data);
            break;
        case 127:
            FERNANDEZ.push_back(data);
            break;
        case 128:
            FIELDS.push_back(data);
            break;
        case 129:
            FIGUEROA.push_back(data);
            break;
        case 130:
            FISCHER.push_back(data);
            break;
        case 131:
            FISHER.push_back(data);
            break;
        case 132:
            FITZGERALD.push_back(data);
            break;
        case 133:
            FLEMING.push_back(data);
            break;
        case 134:
            FLETCHER.push_back(data);
            break;
        case 135:
            FLORES.push_back(data);
            break;
        case 136:
            FORD.push_back(data);
            break;
        case 137:
            FOSTER.push_back(data);
            break;
        case 138:
            FOWLER.push_back(data);
            break;
        case 139:
            FOX.push_back(data);
            break;
        case 140:
            FRANCIS.push_back(data);
            break;
        case 141:
            FRANCO.push_back(data);
            break;
        case 142:
            FRANK.push_back(data);
            break;
        case 143:
            FRANKLIN.push_back(data);
            break;
        case 144:
            FRAZIER.push_back(data);
            break;
        case 145:
            FREEMAN.push_back(data);
            break;
        case 146:
            FUENTES.push_back(data);
            break;
        case 147:
            FULLER.push_back(data);
            break;
        case 148:
            GALLAGHER.push_back(data);
            break;
        case 149:
            GALLEGOS.push_back(data);
            break;
        case 150:
            GARCIA.push_back(data);
            break;
        case 151:
            GARDNER.push_back(data);
            break;
        case 152:
            GARNER.push_back(data);
            break;
        case 153:
            GARRETT.push_back(data);
            break;
        case 154:
            GARZA.push_back(data);
            break;
        case 155:
            GEORGE.push_back(data);
            break;
        case 156:
            GIBSON.push_back(data);
            break;
        case 157:
            GILBERT.push_back(data);
            break;
        case 158:
            GILL.push_back(data);
            break;
        case 159:
            GOMEZ.push_back(data);
            break;
        case 160:
            GONZALES.push_back(data);
            break;
        case 161:
            GONZALEZ.push_back(data);
            break;
        case 162:
            GOODMAN.push_back(data);
            break;
        case 163:
            GOODWIN.push_back(data);
            break;
        case 164:
            GORDON.push_back(data);
            break;
        case 165:
            GRAHAM.push_back(data);
            break;
        case 166:
            GRANT.push_back(data);
            break;
        case 167:
            GRAVES.push_back(data);
            break;
        case 168:
            GRAY.push_back(data);
            break;
        case 169:
            GREEN.push_back(data);
            break;
        case 170:
            GREENE.push_back(data);
            break;
        case 171:
            GREGORY.push_back(data);
            break;
        case 172:
            GRIFFIN.push_back(data);
            break;
        case 173:
            GRIFFITH.push_back(data);
            break;
        case 174:
            GROSS.push_back(data);
            break;
        case 175:
            GUERRA.push_back(data);
            break;
        case 176:
            GUERRERO.push_back(data);
            break;
        case 177:
            GUTIERREZ.push_back(data);
            break;
        case 178:
            GUZMAN.push_back(data);
            break;
        case 179:
            HAIL.push_back(data);
            break;
        case 180:
            HALE.push_back(data);
            break;
        case 181:
            HALL.push_back(data);
            break;
        case 182:
            HAMILTON.push_back(data);
            break;
        case 183:
            HAMMOND.push_back(data);
            break;
        case 184:
            HAMPTON.push_back(data);
            break;
        case 185:
            HANSEN.push_back(data);
            break;
        case 186:
            HANSON.push_back(data);
            break;
        case 187:
            HARDY.push_back(data);
            break;
        case 188:
            HARMON.push_back(data);
            break;
        case 189:
            HARPER.push_back(data);
            break;
        case 190:
            HARRINGTON.push_back(data);
            break;
        case 191:
            HARRIS.push_back(data);
            break;
        case 192:
            HARRISON.push_back(data);
            break;
        case 193:
            HART.push_back(data);
            break;
        case 194:
            HARVEY.push_back(data);
            break;
        case 195:
            HAWKINS.push_back(data);
            break;
        case 196:
            HAYES.push_back(data);
            break;
        case 197:
            HAYNES.push_back(data);
            break;
        case 198:
            HENDERSON.push_back(data);
            break;
        case 199:
            HENRY.push_back(data);
            break;
        case 200:
            HERNANDEZ.push_back(data);
            break;
        case 201:
            HERRERA.push_back(data);
            break;
        case 202:
            HICKS.push_back(data);
            break;
        case 203:
            HIGGINS.push_back(data);
            break;
        case 204:
            HILL.push_back(data);
            break;
        case 205:
            HINES.push_back(data);
            break;
        case 206:
            HODGES.push_back(data);
            break;
        case 207:
            HOFFMAN.push_back(data);
            break;
        case 208:
            HOLLAND.push_back(data);
            break;
        case 209:
            HOLMES.push_back(data);
            break;
        case 210:
            HOLT.push_back(data);
            break;
        case 211:
            HOPKINS.push_back(data);
            break;
        case 212:
            HORTON.push_back(data);
            break;
        case 213:
            HOWARD.push_back(data);
            break;
        case 214:
            HOWELL.push_back(data);
            break;
        case 215:
            HUANG.push_back(data);
            break;
        case 216:
            HUBBARD.push_back(data);
            break;
        case 217:
            HUDSON.push_back(data);
            break;
        case 218:
            HUGHES.push_back(data);
            break;
        case 219:
            HUNT.push_back(data);
            break;
        case 220:
            HUNTER.push_back(data);
            break;
        case 221:
            INGRAM.push_back(data);
            break;
        case 222:
            JACKSON.push_back(data);
            break;
        case 223:
            JACOBS.push_back(data);
            break;
        case 224:
            JAMES.push_back(data);
            break;
        case 225:
            JENKINS.push_back(data);
            break;
        case 226:
            JENNINGS.push_back(data);
            break;
        case 227:
            JENSEN.push_back(data);
            break;
        case 228:
            JIMENEZ.push_back(data);
            break;
        case 229:
            JOHNSON.push_back(data);
            break;
        case 230:
            JOHNSTON.push_back(data);
            break;
        case 231:
            JONES.push_back(data);
            break;
        case 232:
            JORDAN.push_back(data);
            break;
        case 233:
            JOSEPH.push_back(data);
            break;
        case 234:
            JUAREZ.push_back(data);
            break;
        case 235:
            KELLER.push_back(data);
            break;
        case 236:
            KELLEY.push_back(data);
            break;
        case 237:
            KELLY.push_back(data);
            break;
        case 238:
            KENNEDY.push_back(data);
            break;
        case 239:
            KHAN.push_back(data);
            break;
        case 240:
            KIM.push_back(data);
            break;
        case 241:
            KING.push_back(data);
            break;
        case 242:
            KLEIN.push_back(data);
            break;
        case 243:
            KNIGHT.push_back(data);
            break;
        case 244:
            LAMBERT.push_back(data);
            break;
        case 245:
            LANE.push_back(data);
            break;
        case 246:
            LARA.push_back(data);
            break;
        case 247:
            LARSON.push_back(data);
            break;
        case 248:
            LAWRENCE.push_back(data);
            break;
        case 249:
            LAWSON.push_back(data);
            break;
        case 250:
            LE.push_back(data);
            break;
        case 251:
            LEE.push_back(data);
            break;
        case 252:
            LEON.push_back(data);
            break;
        case 253:
            LEONARD.push_back(data);
            break;
        case 254:
            LEWIS.push_back(data);
            break;
        case 255:
            LI.push_back(data);
            break;
        case 256:
            LIN.push_back(data);
            break;
        case 257:
            LITTLE.push_back(data);
            break;
        case 258:
            LIU.push_back(data);
            break;
        case 259:
            LOGAN.push_back(data);
            break;
        case 260:
            LONG.push_back(data);
            break;
        case 261:
            LOPEZ.push_back(data);
            break;
        case 262:
            LOVE.push_back(data);
            break;
        case 263:
            LOWE.push_back(data);
            break;
        case 264:
            LUCAS.push_back(data);
            break;
        case 265:
            LUNA.push_back(data);
            break;
        case 266:
            LYNCH.push_back(data);
            break;
        case 267:
            LYONS.push_back(data);
            break;
        case 268:
            MACK.push_back(data);
            break;
        case 269:
            MALDONADO.push_back(data);
            break;
        case 270:
            MALONE.push_back(data);
            break;
        case 271:
            MANN.push_back(data);
            break;
        case 272:
            MANNING.push_back(data);
            break;
        case 273:
            MARQUEZ.push_back(data);
            break;
        case 274:
            MARSHALL.push_back(data);
            break;
        case 275:
            MARTIN.push_back(data);
            break;
        case 276:
            MARTINEZ.push_back(data);
            break;
        case 277:
            MASON.push_back(data);
            break;
        case 278:
            MATTHEWS.push_back(data);
            break;
        case 279:
            MAXWELL.push_back(data);
            break;
        case 280:
            MAY.push_back(data);
            break;
        case 281:
            MCCARTHY.push_back(data);
            break;
        case 282:
            MCCOY.push_back(data);
            break;
        case 283:
            MCDANIEL.push_back(data);
            break;
        case 284:
            MCDONALD.push_back(data);
            break;
        case 285:
            MCGEE.push_back(data);
            break;
        case 286:
            MCKINNEY.push_back(data);
            break;
        case 287:
            MCLAUGHLIN.push_back(data);
            break;
        case 288:
            MEDINA.push_back(data);
            break;
        case 289:
            MEJIA.push_back(data);
            break;
        case 290:
            MENDEZ.push_back(data);
            break;
        case 291:
            MENDOZA.push_back(data);
            break;
        case 292:
            MEYER.push_back(data);
            break;
        case 293:
            MILES.push_back(data);
            break;
        case 294:
            MILLER.push_back(data);
            break;
        case 295:
            MILLS.push_back(data);
            break;
        case 296:
            MIRANDA.push_back(data);
            break;
        case 297:
            MITCHELL.push_back(data);
            break;
        case 298:
            MOLINA.push_back(data);
            break;
        case 299:
            MONTGOMERY.push_back(data);
            break;
        case 300:
            MONTOYA.push_back(data);
            break;
        case 301:
            MOORE.push_back(data);
            break;
        case 302:
            MORALES.push_back(data);
            break;
        case 303:
            MORAN.push_back(data);
            break;
        case 304:
            MORENO.push_back(data);
            break;
        case 305:
            MORGAN.push_back(data);
            break;
        case 306:
            MORRIS.push_back(data);
            break;
        case 307:
            MORRISON.push_back(data);
            break;
        case 308:
            MOSS.push_back(data);
            break;
        case 309:
            MULLINS.push_back(data);
            break;
        case 310:
            MUNOZ.push_back(data);
            break;
        case 311:
            MURPHY.push_back(data);
            break;
        case 312:
            MURRAY.push_back(data);
            break;
        case 313:
            MYERS.push_back(data);
            break;
        case 314:
            NAVARRO.push_back(data);
            break;
        case 315:
            NEAL.push_back(data);
            break;
        case 316:
            NELSON.push_back(data);
            break;
        case 317:
            NEWMAN.push_back(data);
            break;
        case 318:
            NEWTON.push_back(data);
            break;
        case 319:
            NGUYEN.push_back(data);
            break;
        case 320:
            NICHOLS.push_back(data);
            break;
        case 321:
            NORMAN.push_back(data);
            break;
        case 322:
            NORRIS.push_back(data);
            break;
        case 323:
            NUNEZ.push_back(data);
            break;
        case 324:
            OBRIEN.push_back(data);
            break;
        case 325:
            OCHOA.push_back(data);
            break;
        case 326:
            OCONNOR.push_back(data);
            break;
        case 327:
            OLIVER.push_back(data);
            break;
        case 328:
            OLSON.push_back(data);
            break;
        case 329:
            ORTEGA.push_back(data);
            break;
        case 330:
            ORTIZ.push_back(data);
            break;
        case 331:
            OWENS.push_back(data);
            break;
        case 332:
            PACHECO.push_back(data);
            break;
        case 333:
            PADILLA.push_back(data);
            break;
        case 334:
            PAGE.push_back(data);
            break;
        case 335:
            PALMER.push_back(data);
            break;
        case 336:
            PARK.push_back(data);
            break;
        case 337:
            PARKER.push_back(data);
            break;
        case 338:
            PARKS.push_back(data);
            break;
        case 339:
            PARSONS.push_back(data);
            break;
        case 340:
            PATEL.push_back(data);
            break;
        case 341:
            PATTERSON.push_back(data);
            break;
        case 342:
            PAUL.push_back(data);
            break;
        case 343:
            PAYNE.push_back(data);
            break;
        case 344:
            PEARSON.push_back(data);
            break;
        case 345:
            PENA.push_back(data);
            break;
        case 346:
            PEREZ.push_back(data);
            break;
        case 347:
            PERKINS.push_back(data);
            break;
        case 348:
            PERRY.push_back(data);
            break;
        case 349:
            PERSON.push_back(data);
            break;
        case 350:
            PETERS.push_back(data);
            break;
        case 351:
            PETERSON.push_back(data);
            break;
        case 352:
            PHAM.push_back(data);
            break;
        case 353:
            PHILLIPS.push_back(data);
            break;
        case 354:
            PIERCE.push_back(data);
            break;
        case 355:
            PORTER.push_back(data);
            break;
        case 356:
            POTTER.push_back(data);
            break;
        case 357:
            POWELL.push_back(data);
            break;
        case 358:
            POWERS.push_back(data);
            break;
        case 359:
            PRICE.push_back(data);
            break;
        case 360:
            QUINN.push_back(data);
            break;
        case 361:
            RAMIREZ.push_back(data);
            break;
        case 362:
            RAMOS.push_back(data);
            break;
        case 363:
            RAMSEY.push_back(data);
            break;
        case 364:
            RAY.push_back(data);
            break;
        case 365:
            REED.push_back(data);
            break;
        case 366:
            REESE.push_back(data);
            break;
        case 367:
            REEVES.push_back(data);
            break;
        case 368:
            REID.push_back(data);
            break;
        case 369:
            REYES.push_back(data);
            break;
        case 370:
            REYNOLDS.push_back(data);
            break;
        case 371:
            RHODES.push_back(data);
            break;
        case 372:
            RICE.push_back(data);
            break;
        case 373:
            RICHARDS.push_back(data);
            break;
        case 374:
            RICHARDSON.push_back(data);
            break;
        case 375:
            RILEY.push_back(data);
            break;
        case 376:
            RIOS.push_back(data);
            break;
        case 377:
            RIVAS.push_back(data);
            break;
        case 378:
            RIVERA.push_back(data);
            break;
        case 379:
            ROBBINS.push_back(data);
            break;
        case 380:
            ROBERTS.push_back(data);
            break;
        case 381:
            ROBERTSON.push_back(data);
            break;
        case 382:
            ROBINSON.push_back(data);
            break;
        case 383:
            ROBLES.push_back(data);
            break;
        case 384:
            RODGERS.push_back(data);
            break;
        case 385:
            RODRIGUEZ.push_back(data);
            break;
        case 386:
            ROGERS.push_back(data);
            break;
        case 387:
            ROJAS.push_back(data);
            break;
        case 388:
            ROMAN.push_back(data);
            break;
        case 389:
            ROMERO.push_back(data);
            break;
        case 390:
            ROSALES.push_back(data);
            break;
        case 391:
            ROSE.push_back(data);
            break;
        case 392:
            ROSS.push_back(data);
            break;
        case 393:
            ROWE.push_back(data);
            break;
        case 394:
            RUIZ.push_back(data);
            break;
        case 395:
            RUSSELL.push_back(data);
            break;
        case 396:
            RYAN.push_back(data);
            break;
        case 397:
            SALAZAR.push_back(data);
            break;
        case 398:
            SALINAS.push_back(data);
            break;
        case 399:
            SANCHEZ.push_back(data);
            break;
        case 400:
            SANDERS.push_back(data);
            break;
        case 401:
            SANDOVAL.push_back(data);
            break;
        case 402:
            SANTIAGO.push_back(data);
            break;
        case 403:
            SANTOS.push_back(data);
            break;
        case 404:
            SAUNDERS.push_back(data);
            break;
        case 405:
            SCHMIDT.push_back(data);
            break;
        case 406:
            SCHNEIDER.push_back(data);
            break;
        case 407:
            SCHROEDER.push_back(data);
            break;
        case 408:
            SCHULTZ.push_back(data);
            break;
        case 409:
            SCHWARTZ.push_back(data);
            break;
        case 410:
            SCOTT.push_back(data);
            break;
        case 411:
            SERRANO.push_back(data);
            break;
        case 412:
            SHARP.push_back(data);
            break;
        case 413:
            SHAW.push_back(data);
            break;
        case 414:
            SHELTON.push_back(data);
            break;
        case 415:
            SHERMAN.push_back(data);
            break;
        case 416:
            SILVA.push_back(data);
            break;
        case 417:
            SIMMONS.push_back(data);
            break;
        case 418:
            SIMON.push_back(data);
            break;
        case 419:
            SIMPSON.push_back(data);
            break;
        case 420:
            SIMS.push_back(data);
            break;
        case 421:
            SINGH.push_back(data);
            break;
        case 422:
            SMITH.push_back(data);
            break;
        case 423:
            SNYDER.push_back(data);
            break;
        case 424:
            SOLIS.push_back(data);
            break;
        case 425:
            SOTO.push_back(data);
            break;
        case 426:
            SPENCER.push_back(data);
            break;
        case 427:
            STANLEY.push_back(data);
            break;
        case 428:
            STEELE.push_back(data);
            break;
        case 429:
            STEPHENS.push_back(data);
            break;
        case 430:
            STEVENS.push_back(data);
            break;
        case 431:
            STEVENSON.push_back(data);
            break;
        case 432:
            STEWART.push_back(data);
            break;
        case 433:
            STONE.push_back(data);
            break;
        case 434:
            STRICKLAND.push_back(data);
            break;
        case 435:
            SULLIVAN.push_back(data);
            break;
        case 436:
            SUTTON.push_back(data);
            break;
        case 437:
            SWANSON.push_back(data);
            break;
        case 438:
            TATE.push_back(data);
            break;
        case 439:
            TAYLOR.push_back(data);
            break;
        case 440:
            TERRY.push_back(data);
            break;
        case 441:
            THOMAS.push_back(data);
            break;
        case 442:
            THOMPSON.push_back(data);
            break;
        case 443:
            THORNTON.push_back(data);
            break;
        case 444:
            TODD.push_back(data);
            break;
        case 445:
            TORRES.push_back(data);
            break;
        case 446:
            TOWNSEND.push_back(data);
            break;
        case 447:
            TRAN.push_back(data);
            break;
        case 448:
            TRUJILLO.push_back(data);
            break;
        case 449:
            TUCKER.push_back(data);
            break;
        case 450:
            TURNER.push_back(data);
            break;
        case 451:
            VALDEZ.push_back(data);
            break;
        case 452:
            VALENCIA.push_back(data);
            break;
        case 453:
            VARGAS.push_back(data);
            break;
        case 454:
            VASQUEZ.push_back(data);
            break;
        case 455:
            VAUGHN.push_back(data);
            break;
        case 456:
            VAZQUEZ.push_back(data);
            break;
        case 457:
            VEGA.push_back(data);
            break;
        case 458:
            VELASQUEZ.push_back(data);
            break;
        case 459:
            WADE.push_back(data);
            break;
        case 460:
            WAGNER.push_back(data);
            break;
        case 461:
            WALKER.push_back(data);
            break;
        case 462:
            WALLACE.push_back(data);
            break;
        case 463:
            WALSH.push_back(data);
            break;
        case 464:
            WALTERS.push_back(data);
            break;
        case 465:
            WALTON.push_back(data);
            break;
        case 466:
            WANG.push_back(data);
            break;
        case 467:
            WARD.push_back(data);
            break;
        case 468:
            WARNER.push_back(data);
            break;
        case 469:
            WARREN.push_back(data);
            break;
        case 470:
            WASHINGTON.push_back(data);
            break;
        case 471:
            WATERS.push_back(data);
            break;
        case 472:
            WATKINS.push_back(data);
            break;
        case 473:
            WATSON.push_back(data);
            break;
        case 474:
            WATTS.push_back(data);
            break;
        case 475:
            WEAVER.push_back(data);
            break;
        case 476:
            WEBB.push_back(data);
            break;
        case 477:
            WEBER.push_back(data);
            break;
        case 478:
            WEBSTER.push_back(data);
            break;
        case 479:
            WELCH.push_back(data);
            break;
        case 480:
            WELLS.push_back(data);
            break;
        case 481:
            WEST.push_back(data);
            break;
        case 482:
            WHEELER.push_back(data);
            break;
        case 483:
            WHITE.push_back(data);
            break;
        case 484:
            WILLIAMS.push_back(data);
            break;
        case 485:
            WILLIAMSON.push_back(data);
            break;
        case 486:
            WILLIS.push_back(data);
            break;
        case 487:
            WILSON.push_back(data);
            break;
        case 488:
            WISE.push_back(data);
            break;
        case 489:
            WOLF.push_back(data);
            break;
        case 490:
            WOLFE.push_back(data);
            break;
        case 491:
            WONG.push_back(data);
            break;
        case 492:
            WOOD.push_back(data);
            break;
        case 493:
            WOODS.push_back(data);
            break;
        case 494:
            WRIGHT.push_back(data);
            break;
        case 495:
            WU.push_back(data);
            break;
        case 496:
            YANG.push_back(data);
            break;
        case 497:
            YOUNG.push_back(data);
            break;
        case 498:
            ZHANG.push_back(data);
            break;
        case 499:
            ZIMMERMAN.push_back(data);
            break;
        }
    }
    // const unsigned int ascii = 65;

    // for (auto &data : l)
    // {
    //     int i = (data->lastName[0] - ascii);
    //     int j = (data->lastName[1] - ascii);
    //     int k = (data->firstName[0] - ascii);
    //     int l = (data->firstName[1] - ascii);

    //     x[i][j][k][l].push_back(data);
    // }

    // list<Data *>::iterator it = l.begin();

    // for (int i = 0; i < 26; i++)
    // {
    //     for (int j = 0; j < 26; j++)
    //     {
    //         for (int k = 0; k < 26; k++)
    //         {
    //             for (int l = 0; l < 26; l++)
    //             {
    //                 std::sort(x[i][j][k][l].begin(), x[i][j][k][l].end(), compare);

    //                 for (auto data : x[i][j][k][l])
    //                 {
    //                     *it = data;
    //                     ++it;
    //                 }
    //             }
    //         }
    //     }
    // }
}

void t3(list<Data *> &l)
{
    Data *allData[1010000];
    int i = 0;
    for (auto &data : l)
    {
        allData[i] = data;
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        int k = j;

        while (allData[j]->firstName == allData[k]->firstName && allData[j]->lastName == allData[k]->firstName)
        {
            k++;
        }
    }
}

void generateSwitchStatement(string sortedLastNames[500])
{
    ofstream output("output.txt");

    // Write the data
    for (int i = 0; i < 500; i++)
    {
        output << "case " << i << ":\n";
        output << sortedLastNames[i] << ".push_back(data);\n break;\n";
        //output << "vector<Data *> " << sortedLastNames[i] << ";\n";
    }

    output.close();
}

void sortDataList(list<Data *> &l)
{
    generateSwitchStatement(sortedLastNames);
    // switch (getTestCase(l))
    // {
    // case 1:
    //     t1t2(l);
    //     break;
    // case 3:
    //     t3(l);
    //     break;
    // case 4:
    //     cout << "coming soon";
    //     break;
    // }
}

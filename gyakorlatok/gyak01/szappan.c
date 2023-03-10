//ez csak ilyen gyakorló feladat grafika órára
// A circle példához hasonlóan készítendő el.

// Készítsünk egy programot, amellyel téglatestek adatait lehet kezelni!

// Definiáljunk egy struktúrát (például Cuboid vagy Brick néven), amely tartalmazza a téglatest 3 élének a hosszát!

// Definiáljunk egy függvényt, amellyel ellenőrzött módon be lehet állítani egyszerre a 3 él hosszát (például set_size néven)!

// Definiáljunk egy függvényt, amelyik kiszámítja a téglatest térfogatát (például calc_volume), és egy másikat amelyik a felszínét (például calc_surface)!

// Definiáljunk egy függvényt, amelyik a téglalapot megvizsgálja, hogy van-e négyzet alakú lapja!
#include <stdio.h>
#include <string.h>

typedef struct														{
	double x														;
	double y														;
	double z														;
																	} 
	Szappan															;


void set_size(double, double, double, Szappan*)						;
void print_s_area( Szappan*)										;
void print_v_area( Szappan*)										;
void print_if_square( Szappan*)										;

int main() 															{

Szappan sz, sz2														;
printf("\n Jo napot\n")												;
set_size(4, 2, 3, &sz)												;
print_s_area(&sz)													;
print_v_area(&sz)													;
print_if_square(&sz)												;

printf("\n Masik szappan\n")										;
set_size(4, 4, 3, &sz2)												;
print_s_area(&sz2)													;
print_v_area(&sz2)													;
print_if_square(&sz2)												;
printf("\n \n Viszlat\n")											;

return 0															;
																	}


void set_size(double x, double y, double z, Szappan *sz) 			{

if( (x * y) >= 0 & (x * z) >= 0 )									{
	sz -> x = x														;
	sz -> y = y														;
	sz -> z = z														;
																	}
																	}


void print_s_area( Szappan* sz) 									{

double s_Area = 2 * (sz->x * sz->y + sz->x * sz->z + sz->y * sz->z)	;
printf("\n A szappan felulete = %.2f\n", s_Area)					;
																	}


void print_v_area( Szappan* sz) 									{

double v_Area = sz->x * sz->y * sz->z								;
printf("\n A szappan ennyi helyet foglal el = %.2f\n", v_Area)		;
																	}


void print_if_square( Szappan* sz)									{

if(sz -> x == sz -> y | sz -> y == sz -> z)							{
	printf("\n Van negyzet oldala.")								;				
																	}
																	}





 

 
	
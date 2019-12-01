#include "list.h"
#include "polynom.h"

using namespace std;

void main() {
	List<string> l;
	/*l.push_back("2");
	l.push_back("3x");
	l.push_back("4x^2");
	l.push_back("5x^3");
	l.pop_back();
	l.insert("6x^4", 3);
	l.remove(2);

	l.print();
	*/
	
	Polynom p1("-2x^2 + 3x - 3 + x^19 + 6x^5 + 1 - 15x");
	//Polynom p2("1 + 2x - 2x^2"); 
	//Polynom p3("1 - 2x + 3x^3");
	Polynom p4("3x^3 -2 + 3x^2"); 
	Polynom p5("-x^2 + 2");
	p4.print(); p5.print();
	cout << endl;
	
	p1 = p4 + p5;
	cout << "+:  ";
	p1.print();

	p1 = p4 - p5;
	cout << "-:  ";
	p1.print();

	p1 = p4 * p5;
	cout << "*:  ";
	p1.print();

	cout << "x=0: " << p1.calc(0) << endl;

	system("pause");
}
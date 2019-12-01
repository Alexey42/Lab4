#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include "list.h"
using namespace std;

class Monom {
public:
	double coef = 0;
	int pow = 0;

	Monom() {}

	Monom(double c, int p):coef(c), pow(p) {}

	Monom* operator=(int x) {
		if (x == 0) {
			coef = 0;
			pow = 0;
		}
		return this;
	}

	bool operator==(Monom &m) {
		if (coef == m.coef && pow == m.pow) return true;
		else return false;
	}

	bool operator!=(Monom &m) {
		if (coef != m.coef || pow != m.pow) return true;
		else return false;
	}

	friend ostream& operator<<(ostream &out, const Monom &m) {
		out << m.coef << "x^" << m.pow;
		return out;
	}
};


class Polynom: public List<Monom> {
	string input = " ";
	double x = 0;
	
public:
	Polynom() {}

	Polynom(string in):input(in) {
		parse();
	}

	Polynom(string in, double x):input(in), x(x) {
		parse();
		calc(x);
	}

	void parse() {
		// в temp будет накапливаться очередной моном
		string temp = "";
		int pow = 1; double coef = 0;
		
		for (int i = 0; i < input.size() + 1; i++) {
			if (input[i] == ' ') continue;

			if (isdigit(input[i]) || input[i] == 'x' || input[i] == '^') {
				temp.push_back(input[i]);
				continue;
			}

			if (input[i] == '+' || input[i] == '-' || input[i] == '\0') {
				pow = 1; coef = 0;
				
				// извлечение коэффициента монома
				try { coef = stod(temp); }
				catch (...) { 
					if (temp[0] == 'x') coef = 1;
					else if (temp[0] == '-' && temp[1] == 'x') coef = -1;
					else if (i == 0 && (isdigit(input[1]) || input[1] == 'x')) {
						temp.push_back('-'); continue;
					}
					else return; 
				}
					 
				// извлечение степени монома
				if (temp.find('x') == -1) pow = 0;
				else if (temp.find('^') != -1) pow = stoi(temp.substr(temp.find('^') + 1, temp.size() - temp.find('^')));
				if (pow < 0) return;

				Monom m(coef, pow);
				push_back(m);
				temp.clear();
				if (input[i] == '-') temp.push_back('-');
			}

			else return;
		}
		normalize();
	}

	double calc(double x) {
		Node<Monom> *temp = head;
		double res = 0;
		for (temp = head; temp; temp = temp->next) res += temp->data.coef * pow(x, temp->data.pow);
		return res;
	}
		 
	Polynom operator+(const Polynom &p) {
		Polynom* res = new Polynom(*this);
		Node<Monom> *t = p.head;

		for (t = p.head; t; t = t->next) res->push_back(Monom(t->data.coef, t->data.pow));
		res->normalize();
		return *res;
	}

	Polynom operator-(const Polynom &p) {
		Polynom* res = new Polynom(*this);
		Node<Monom> *t = p.head;

		for (t = p.head; t; t = t->next) res->push_back(Monom(t->data.coef*-1, t->data.pow));
		res->normalize();
		return *res;
	}

	Polynom operator*(const Polynom &p) {
		Polynom* res = new Polynom();
		Node<Monom> *t1 = head;
		Node<Monom> *t2 = p.head;
		double coef = 0; int pow = 0;

		for (t1 = head; t1; t1 = t1->next) {
			for (t2 = p.head; t2; t2 = t2->next) {
				coef = t1->data.coef * t2->data.coef;
				pow = t1->data.pow + t2->data.pow;
				if (coef != 0) res->push_back(Monom(coef, pow));			
			}
		}
		res->normalize();
		return *res;
	}

	void print() {
		if (size >= 1) {
			Node<Monom>* temp = head;
			Node<Monom>* temp2 = head;
			// сортировка мономов
			for (temp = head; temp->next; temp = temp->next) {
				for (temp2 = head; temp2->next; temp2 = temp2->next) {
					if (temp2->data.pow > temp2->next->data.pow) iter_swap(&temp2->next->data, &temp2->data);
				}
			}

			for (temp = head; temp; temp = temp->next) {
				if (temp->data.coef == -1 && temp->data.pow != 0) cout << '-';
				if (temp->data.coef > 1 || temp->data.coef < -1 || temp->data.pow == 0) cout << temp->data.coef;
				if (temp->data.pow == 1) cout << "x";
				if (temp->data.pow > 1) cout << "x^" << temp->data.pow;
				if (temp->next != 0 && temp->next->data.coef > 0) cout << "+";
			}
			cout << endl;
		}
	}

	void normalize() {
		Node<Monom> *t1 = head;
		Node<Monom> *t2;
		// сложение мономов с одинаковыми степенями
		for (t1 = head; t1; t1 = t1->next) {
			for (t2 = t1->next; t2; t2 = t2->next) {
				if (t1->data.pow == t2->data.pow) {
					t1->data.coef += t2->data.coef;
					t2 = remove(t2->data);
				}				
			}			
		}
		// удаление нолей
		for (t1 = head; t1; t1 = t1->next) {
			if (t1->data.coef == 0) t1 = remove(t1->data);
			if (size == 0) break;			
		}
	}

};
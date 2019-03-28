# include <iostream>
# include <string>
# include <sstream>

using namespace std;

string convert2digit(int);
string convert3digit(int);
string convert6digit(int);
string convertCurrency(double);

const string EMPTY = "";
const string X[] = { EMPTY, "one ", "two ", "three ", "four ", "five ", "six ", "seven ", "eight ", "nine ", "ten ", "eleven ", "twelve ", "thirteen ", "fourteen ", "fifteen ", "sixteen ", "seventeen ", "eighteen ", "nineteen " };
const string Y[] = { EMPTY, EMPTY, "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety " };

int main() {

	double numCurrency;
	do {
		cout << "please input currency number only between 0 - 999999.99: ";
		cin >> numCurrency;
	} while (numCurrency > 999999.99 || numCurrency < 0);


	string strCurrency = convertCurrency(numCurrency);
	cout << strCurrency << endl;

	system("pause");
	return 0;
}

string convertCurrency(double number)
{
	// transfer number to the string
	string strNumber = to_string(number);
	int pos = strNumber.find(".");
	string s1 = strNumber.substr(0, pos);
	string s2 = strNumber.substr(pos + 1, 2);

	stringstream ss1, ss2;
	long n1, n2; // n1 is the integer part and n2 is the fractional part
	ss1 << s1;
	ss1 >> n1;
	ss2 << s2;
	ss2 >> n2;

	string result = "";

	// 1-dollar; more than one for dollars
	if (n1 > 0) {
		result = convert6digit(n1);
		if (n1 == 1) {
			result = result + "dollar";
		}
		else {
			result = result + "dollars";
		}
	}

	// add " " after dollar(s) when it has decimal part
	if (n1 > 0 && n2 > 0) {
		result = result + " ";
	}

	// cent and cents
	if (n2 > 0) {
		result = result + convert2digit(n2);
		if (n2 == 1) {
			result += "cent";
		}
		else {
			result += "cents";
		}
	}

	if (n1== 0 && n2==0) {
		result = "zero dollar";
	}

	return result;
}

// transfer the number under 20 to words
string convert2digit(int n)
{
	string result = "";

	if (n < 20) {
		result = X[n];
	}
	else {
		result = Y[n / 10] + X[n % 10];
	}

	return result;
}


// transfer 3 digits number to the words, also need to use the 'convert2digit'
string convert3digit(int n)
{
	string result = "";

	int n1 = n / 100; // the third number on the left of .
	int n2 = n % 100; // the first second number on the left of .

					  // only when the number larger than 99, using the word "hundred"
	if (n1 > 0) {
		result = X[n1] + "hundred ";
	}

	// using “and” 
	if (n1 > 0 && n2 > 0) {
		result = result + "and ";
	}

	// ...hundred and....
	result = result + convert2digit(n2);

	return result;
}


// transfer 3 digits number to the words, also need to use the 'convert2digit'
string convert6digit(int n)
{
	string result = "";

	int n1 = n / 1000; // more than 4 digits
	int n2 = n % 1000; // under 4 digits

					   // only when the number has at least four digits, using the word "thousand"
	if (n1 > 0) {
		result = convert3digit(n1);
		result = result + "thousand ";
	}

	// adding "and" after "thousand"
	if (n1 > 0 && n2 < 100) {
		result = result + "and ";
	}

	// add the remaining words
	result = result + convert3digit(n2);

	
	return result;
	
}
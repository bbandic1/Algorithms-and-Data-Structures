#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void Goldbach(int n, int& p, int& q) {
	if (n%2==1) throw "Number is not even"; // Check if the number is odd
	if (n<=2) throw "Number <= 2"; // Check if the number is less than or equal to 2
	if (n==4) {
		p=2; q=2; return; // Special case for 4
	}
	
	p=q=0;
	vector<int> prosti;
	
	for (int i(2); i<n; i++) { // Find all prime numbers less than n
		bool found=true;
		for (int j(2); j<i; j++)
			if (i%j==0) found=false; // Check if i is not prime
		if (found) prosti.push_back(i); // Add prime number to the list
	}
	
	for (int i(0); i<prosti.size(); i++) { // Check pairs of prime numbers
		for (int j(0); j<prosti.size(); j++) {
			if (prosti[i]+prosti[j] == n) { // Check if the sum equals n
				p=prosti[i];
				q=prosti[j];
			}
		}
	}
	
	if (p==0) throw "Hypothesis does not hold"; // If no such pair is found
}

void Goldbach2(int n, int& p, int& q) {
	if (n%2==1) throw "Number is not even"; // Check if the number is odd
	if (n<=2) throw "Number <= 2"; // Check if the number is less than or equal to 2
	if (n==4) {
		p=2; q=2; return; // Special case for 4
	}
	
	for (int i(2); i<n/2; i++) { // Find a pair of primes whose sum is n
		bool found=true;
		for (int j(2); j<i/2; j++)
			if (i%j==0) { found=false; break; } // Check if i is not prime
		if (!found) continue;
		for (int j(2); j<(n-i)/2; j++)
			if ((n-i)%j==0) { found=false; break; } // Check if (n-i) is not prime
		if (!found) continue;
		p=i;
		q=(n-i);
		return; // Found a valid pair
	}
	throw "Hypothesis does not hold"; // If no such pair is found
}

int main() {
	int n,p,q;
	cout<<"Enter n: ";
	cin>>n; // User input for n
	try {
		clock_t vrijeme1 = clock(); // Start time
		
		Goldbach(n,p,q); // Call Goldbach function
		
		clock_t vrijeme2 = clock(); // End time
		
		int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
		cout<<"Execution time: "<<ukvrijeme<<" ms."<<endl; // Print execution time
		
		cout<<"p="<<p<<" q="<<q<<endl; // Print result
		
	} catch (const char e[]) {
		cout<<"Error: "<<e<<endl; // Print error message
	}
	return 0;
}

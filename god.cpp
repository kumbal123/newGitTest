#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <algorithm>
using namespace std;
class PPerson{
  public:
  	string name;
  	string addr;
  	string account;
  	int sumIncome;
  	int sumExpense;

  	PPerson( void );

};

PPerson::PPerson():
	name (""),
	addr (""),
	account (""),
	sumIncome (0),
	sumExpense (0)
{
}

class CIterator{
  public:
  	CIterator( const vector<PPerson> vec );
    bool                     AtEnd                         ( void ) const;
    void                     Next                          ( void );
    string                   Name                          ( void ) const;
    string                   Addr                          ( void ) const;
    string                   Account                       ( void ) const;
  private:
  	long unsigned int pos;
  	long unsigned int size;
    vector<PPerson> vec;
};

CIterator::CIterator( const vector<PPerson> vec ){
	this -> vec = vec;
	this -> pos = 0;
	this -> size = vec.size();
}

bool                     CIterator::AtEnd                         ( ) const{
	return pos == size;
}

void                     CIterator::Next                          ( ){
	this -> pos += 1;
}

string                   CIterator::Name                          ( ) const{
	return vec[pos].name;
}

string                   CIterator::Addr                          ( ) const{
	return vec[pos].addr;
}

string                   CIterator::Account                       ( ) const{
	return vec[pos].account;
}


bool ComparePersonNameAddr ( const PPerson & ppl1, const PPerson & ppl2 ){
	if( ppl1.name != ppl2.name )
		return ppl1.name < ppl2.name;
	return ppl1.addr < ppl2.addr;
}

bool ComparePersonAcc ( const PPerson & ppl1, const PPerson & ppl2 ){
	return ppl1.account < ppl2.account;
}


class CTaxRegister
{
  public:

  	CTaxRegister( void );
	
  	bool Birth  ( const string & name, const string & addr, const string & account );

	bool  Death ( const string & name, const string & addr );


	bool  Income ( const string & account, int amount );


	bool Income ( const string & name, const string & addr, int amount );


	bool Expense ( const string & account, int amount );


	bool Expense ( const string & name, const string & addr, int amount );


	bool Audit ( const string & name, const string & addr, string & account, int & sumIncome, int & sumExpense ) const;

	CIterator ListByName  ( void ) const;
  private:
    vector<PPerson> vec;
};

CTaxRegister::CTaxRegister (){

}


bool CTaxRegister::Birth  ( const string & name, const string & addr, const string & account ){
	PPerson person;
	person.name = name;
	person.addr = addr;
	person.account = account;
	
	if( vec.end() - vec.begin() == 0 ){
		vec.push_back( person );		
		return true;
	}
    
    auto it = lower_bound( vec.begin(), vec.end(), person, ComparePersonNameAddr );
    int pos = it - vec.begin();

    if( (vec[pos].name == name && vec[pos].addr == addr) )
		return false;

    for( long unsigned int k = 0; k < vec.size(); k++ ){
    	if( vec[k].account == account ){
    		return false;
    	}
    }

	vec.insert( it, person );
	return true;
}

bool  CTaxRegister::Death ( const string & name, const string & addr ){
	PPerson person;
	person.name = name;
	person.addr = addr;

	auto it = lower_bound( vec.begin(), vec.end(), person, ComparePersonNameAddr );
	int pos = it - vec.begin();
	if( !(vec[pos].name == name && vec[pos].addr == addr) )
		return false;

	vec.erase( it );
	return true;
}

bool  CTaxRegister::Income ( const string & account, int amount ){
	for( long unsigned int k = 0; k < vec.size(); k++ ){
		if( vec[k].account == account ){
			vec[k].sumIncome += amount;
			return true;
		}
	}

	return false;
}

bool CTaxRegister::Income ( const string & name, const string & addr, int amount ){
	PPerson person;
	person.name = name;
	person.addr = addr;

	auto it = lower_bound( vec.begin(), vec.end(), person, ComparePersonNameAddr );
	int pos = it - vec.begin();

	if( !(vec[pos].name == name && vec[pos].addr == addr) )
		return false;

	vec[pos].sumIncome += amount;
	return true;
}

bool CTaxRegister::Expense ( const string & account, int amount ){
	for( long unsigned int k = 0; k < vec.size(); k++ ){
		if( vec[k].account == account ){
			vec[k].sumExpense += amount;
			return true;
		}
	}
	return false;
}


bool CTaxRegister::Expense ( const string & name, const string & addr, int amount ){
	PPerson person;
	person.name = name;
	person.addr = addr;

	auto it = lower_bound( vec.begin(), vec.end(), person, ComparePersonNameAddr );
	int pos = it - vec.begin();

	if( !(vec[pos].name == name && vec[pos].addr == addr) )
		return false;

	vec[pos].sumExpense += amount;
	return true;
}

bool CTaxRegister::Audit ( const string & name, const string & addr, string & account, int & sumIncome, int & sumExpense ) const{
	PPerson person;
	person.name = name;
	person.addr = addr;
	auto it = lower_bound( vec.begin(), vec.end(), person, ComparePersonNameAddr );
	int pos = it - vec.begin();
	if( !(vec[pos].name == name && vec[pos].addr == addr) )
		return false;

	account = vec[pos].account;
	sumIncome = vec[pos].sumIncome;
	sumExpense = vec[pos].sumExpense;
	return true;
}

CIterator CTaxRegister::ListByName  ( void ) const{
	CIterator iterator = CIterator(vec);
	return iterator;
}

int main ( void ){

string acct;
  int    sumIncome, sumExpense;
  CTaxRegister b1;
  assert ( b1 . Birth ( "John Smith", "Oak Road 23", "123/456/789" ) );
  assert ( b1 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" ) );
  assert ( b1 . Birth ( "Peter Hacker", "Main Street 17", "634oddT" ) );
  assert ( b1 . Birth ( "John Smith", "Main Street 17", "Z343rwZ" ) );
  assert ( b1 . Income ( "Xuj5#94", 1000 ) );
  assert ( b1 . Income ( "634oddT", 2000 ) );
  assert ( b1 . Income ( "123/456/789", 3000 ) );
  assert ( b1 . Income ( "634oddT", 4000 ) );
  assert ( b1 . Income ( "Peter Hacker", "Main Street 17", 2000 ) );
  assert ( b1 . Expense ( "Jane Hacker", "Main Street 17", 2000 ) );
  assert ( b1 . Expense ( "John Smith", "Main Street 17", 500 ) );
  assert ( b1 . Expense ( "Jane Hacker", "Main Street 17", 1000 ) );
  assert ( b1 . Expense ( "Xuj5#94", 1300 ) );
  
  assert ( b1 . Audit ( "John Smith", "Oak Road 23", acct, sumIncome, sumExpense ) );
  assert ( acct == "123/456/789" );
  assert ( sumIncome == 3000 );
  assert ( sumExpense == 0 );
  assert ( b1 . Audit ( "Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense ) );
  assert ( acct == "Xuj5#94" );
  assert ( sumIncome == 1000 );
  assert ( sumExpense == 4300 );
  assert ( b1 . Audit ( "Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense ) );
  assert ( acct == "634oddT" );
  assert ( sumIncome == 8000 );
  assert ( sumExpense == 0 );
  assert ( b1 . Audit ( "John Smith", "Main Street 17", acct, sumIncome, sumExpense ) );
  assert ( acct == "Z343rwZ" );
  assert ( sumIncome == 0 );
  assert ( sumExpense == 500 );

  CIterator it = b1 . ListByName ();
  assert ( ! it . AtEnd ()
           && it . Name () == "Jane Hacker"
           && it . Addr () == "Main Street 17"
           && it . Account () == "Xuj5#94" );
  it . Next ();
  assert ( ! it . AtEnd ()
           && it . Name () == "John Smith"
           && it . Addr () == "Main Street 17"
           && it . Account () == "Z343rwZ" );
  it . Next ();
  assert ( ! it . AtEnd ()
           && it . Name () == "John Smith"
           && it . Addr () == "Oak Road 23"
           && it . Account () == "123/456/789" );
  it . Next ();
  assert ( ! it . AtEnd ()
           && it . Name () == "Peter Hacker"
           && it . Addr () == "Main Street 17"
           && it . Account () == "634oddT" );
  it . Next ();
  assert ( it . AtEnd () );

  assert ( b1 . Death ( "John Smith", "Main Street 17" ) );

  CTaxRegister b2;

  assert ( b2 . Birth ( "John Smith", "Oak Road 23", "123/456/789" ) );

  assert ( b2 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" ) );

  assert ( !b2 . Income ( "634oddT", 4000 ) );
  assert ( !b2 . Expense ( "John Smith", "Main Street 18", 500 ) );
  assert ( !b2 . Audit ( "John Nowak", "Second Street 23", acct, sumIncome, sumExpense ) );
  assert ( !b2 . Death ( "Peter Nowak", "5-th Avenue" ) );
  assert ( !b2 . Birth ( "Jane Hacker", "Main Street 17", "4et689A" ) );
  assert ( !b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" ) );
  assert ( b2 . Death ( "Jane Hacker", "Main Street 17" ) );
  assert ( b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" ) );

  assert ( b2 . Audit ( "Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense ) );
  assert ( acct == "Xuj5#94" );
  assert ( sumIncome == 0 );
  assert ( sumExpense == 0 );
  assert ( !b2 . Birth ( "Joe Hacker", "Elm Street 23", "AAj5#94" ) );
  

	
  cout << "=================Completed Bitch===========================" << endl;
	

	return 0;
  
}


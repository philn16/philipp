// Some usefull defines and includes
#pragma once

#include <iostream>
using std::cout;
using std::endl;


//! returns the length of an array
#define LEN(x) sizeof(x)/(long(&x[1])-long(&x[0]))

//! Usefull for printing where a failure occored in red text
#define FAILURE_MESSAGE(x) cout << "\033[31m" << x << "  " << __FILE__ << ":" << __LINE__ << "\033[39m" << endl
#define SUCESS_MESSAGE(x)  cout << "\033[32m" << x << "  " << __FILE__ << ":" << __LINE__ << "\033[39m" << endl
#define WARNING_MESSAGE(x) cout << "\033[33m" << x << "  " << __FILE__ << ":" << __LINE__ << "\033[39m" << endl








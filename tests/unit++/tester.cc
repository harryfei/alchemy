// Copyright (C) 2001 Claus Dræby
// Terms of use are in the file COPYING
#include <typeinfo>
#include <iostream>
#include "tester.h"
#include "main.h"

using namespace std;

using namespace unitpp;

void tester::summary()
{
	os << "Tests [Ok-Fail-Error]: [" << n_test.n_ok() << '-'
	<< n_test.n_fail() << '-' << n_test.n_err() << "]\n";
}
void tester::visit(test& t)
{
	try {
		if (verbose > 1)
			os << "Running: " << t.name() << endl;
		t();
		n_test.add_ok();
		write(t);
	} catch (assertion_error& e) {
		n_test.add_fail();
		write(t, e);
		if (exit_on_error)
			throw;
	} catch (exception& e) {
		n_test.add_err();
		write(t, e);
		if (exit_on_error)
			throw;
	} catch (...) {
		n_test.add_err();
		write(t, 0);
		if (exit_on_error)
			throw;
	}
}

void tester::visit(suite& t)
{
	if (verbose)
		os << "****** " << t.name() << " ******" << endl;
	accu.push(n_test);
}

void tester::visit(suite& , int)
{
	res_cnt r(accu.top());
	accu.pop();
	if (n_test.n_err() != r.n_err())
		n_suite.add_err();
	else if (n_test.n_fail() != r.n_fail())
		n_suite.add_fail();
	else
		n_suite.add_ok();
}
void tester::write(test& t)
{
	if (verbose)
		disp(t, "OK");
}
void tester::disp(test& t, const string& status)
{
	os << status << ": ";
	if (!line_fmt)
		os << t.name() << endl;
}
void tester::write(test& t, assertion_error& e)
{
	if (line_fmt)
		os << e.file() << ':' << e.line() << ':';
	disp(t, "FAIL");
	os << e << '\n';
}
void tester::write(test& t, std::exception& e)
{
	if (line_fmt)
		os << t.file() << ':' << t.line() << ':';
	disp(t, "ERROR");
	os << "     : [" << typeid(e).name() << "] " << e.what() << '\n';
}
void tester::write(test& t, int )
{
	if (line_fmt)
		os << t.file() << ':' << t.line() << ':';
	disp(t, "ERROR");
	os << "     : " << "unknown exception" << '\n';
}

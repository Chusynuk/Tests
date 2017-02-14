/**	
 *	Enginyeria del Software G1-15
 *	
 *	FILE: Exceptions.hxx	
 */

#ifndef Exceptions_hxx
#define Exceptions_hxx

#include <iostream>


class ItemNotFound : public std::exception 
{
public:

	const char * what() const throw()
	{
		return "The item does not exist";
	}

};

class CharacterNotFound : public std::exception 
{
public:

	const char * what() const throw()
	{
		return "The character does not exist";
	}

};

class LocationNotFound : public std::exception 
{
public:

	const char * what() const throw()
	{
		return "The location does not exist";
	}

};

class IncorrectMap : public std::exception 
{
public:

	const char * what() const throw()
	{
		return "Incorrect map";
	}

};

class InvalidType : public std::exception 
{
public:

	const char * what() const throw()
	{
		return "Invalid type";
	}

};

#endif


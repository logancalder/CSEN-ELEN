/*
 * Name: Logan Calder
 * Email: lcalder2022@gmail.com
 *
 * Assignment: Palindrome exercise
 */
#include <string>
#include "palindrome.h"

namespace coen79
{

	// accept a string, return whether it is palindrome
	bool isPalindrome(const std::string line)
	{
		auto left = line.begin();
		auto right = line.end();
		--right;

		while (left < right)
		{
			if (*left != *right)
			{
				return false;
			}

			++left;
			--right;
		}
		return true;
	}
}

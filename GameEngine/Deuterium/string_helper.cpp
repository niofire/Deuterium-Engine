#include "string_helper.h"
#include "d_typedef.h"
#include <fstream>



namespace deuterium
{
	void	StringHelper::trim_front(std::string& l_String)
{
	
	while(l_String.length() > 0 && l_String.find_first_of(" ") == 0)
		l_String = l_String.substr(1);
	
}

void StringHelper::trim_end(std::string& l_String)
{
	while(l_String.length() > 0 && l_String.find_last_of(" ") == l_String.size() - 1)
		l_String.erase(l_String.find_last_of(" "),1);
}

void	StringHelper::trim(std::string& l_String)
{
	//Trim front and end
	trim_front(l_String);
	trim_end(l_String);
}


bool	StringHelper::is_identical_string(std::string s1, std::string s2)
{
	return !(s1.compare(s2));
}

bool StringHelper::is_identical_string(const char* s1, const char* s2)
{
	int counter = 0;
	while(s1[counter] && s2[counter])
	{
			if(s1[counter] != s2[counter])
			{
				return false;
			}
			counter++;
	}
	return !s1[counter] && !s2[counter];
}
std::vector<std::string> StringHelper::split(char* i_string,char delimiter)
{
		std::vector<std::string> returnVec;
		int initialCounter = 0;
		std::string currentStr = "";
		for(int i = 0; i_string[i]; ++i)
		{
			currentStr += i_string[i];
			if(i_string[i] == delimiter)
			{
				returnVec.push_back(currentStr);
				currentStr = "";
				initialCounter = i;
			}
		}
		if(currentStr.length() != 0)
			returnVec.push_back(currentStr);

		return returnVec;
	}

void StringHelper::remove_all_char(std::string& str, char c)
{
	for(U32 i = 0; i < str.size(); ++i)
	{
		if(str[i] == c)
		{
			str = str.substr(0,i) + str.substr(i + 1);
			i--;
		}
		
	}
}

}
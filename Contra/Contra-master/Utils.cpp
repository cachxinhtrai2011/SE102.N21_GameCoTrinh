#include <Windows.h>

#include "Utils.h"

vector<string> split(string line, string delimeter)
{
	vector<string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}

/*
char * string to wchar_t* string.
*/
wstring ToWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring wstr(wcstring);

	// delete wcstring   // << can I ? 
	return wstr;
}

float Radius(float ax, float ay, float bx, float by)
{
	return atan((by - ay) / (bx - ax));
}

/*
	Convert char* string to wchar_t* string.
*/
LPCWSTR ToLPCWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring* w = new wstring(wcstring);

	// delete wcstring   // << can I ? 
	return w->c_str();
}

BOOL IsIntersac(LPGAMEOBJECT object, LPTREENODE node)
{
	float oleft, otop, oright, obottom;
	object->GetBoundingBox(oleft, otop, oright, obottom);
	float nleft, ntop, nright, nbottom;
	node->GetBoundingBox(nleft, ntop, nright, nbottom);
	if(oleft >= nright || nleft >= oright)
		return false;
	if (otop <= nbottom || ntop <= obottom)
		return false;
	return true;
}
BOOL IsIntersac(float left, float top, float right, float bottom, LPTREENODE node)
{

	float nleft, ntop, nright, nbottom;
	node->GetBoundingBox(nleft, ntop, nright, nbottom);
	if (left >= nright || nleft >= right)
		return false;
	if (top <= nbottom || ntop <= bottom)
		return false;
	return true;
}
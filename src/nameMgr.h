#ifndef _NAME_MANAGER_
#define _NAME_MANAGER_

#include <string>
using namespace std;

#define CREATE_VALUE(NAME) static const string NAME = #NAME;
#define CREATE_VALUE_WITH_VALUE(NAME, VALUE) static const string NAME = VALUE;

namespace NAME_MGR
{
	CREATE_VALUE(G_JUMP);
	CREATE_VALUE(G_ENTER);
	CREATE_VALUE(G_ELEVATOR);
	CREATE_VALUE(G_JETPACK);
}
#endif //_NAME_MANAGER_
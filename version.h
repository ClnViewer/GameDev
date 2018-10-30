#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "31";
	static const char MONTH[] = "10";
	static const char YEAR[] = "2018";
	static const char UBUNTU_VERSION_STYLE[] =  "18.10";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 0;
	static const long BUILD  = 1;
	static const long REVISION  = 5;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 1;
	#define RC_FILEVERSION 1,0,1,5
	#define RC_FILEVERSION_STRING "1, 0, 1, 5\0"
	static const char FULLVERSION_STRING [] = "1.0.1.5";
	
	//SVN Version
	static const char SVN_REVISION[] = "54";
	static const char SVN_DATE[] = "2018-10-30T00:09:04.260871Z";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 1;
	

}
#endif //VERSION_H

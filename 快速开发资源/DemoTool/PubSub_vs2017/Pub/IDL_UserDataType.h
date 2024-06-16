// Don't modify this file as it will be overwritten.
//
#include "CDR/CDR.h"
#include "ReturnCode.h"
#include "BasicTypes.h"

#ifndef IDL_UserDataType_hh
#define IDL_UserDataType_hh

#ifndef UserDataType_defined
#define UserDataType_defined

#define MAXLENG 1024
#define MD5LENG  32

struct UserDataType {
	UserDataType()
	{
		m_md5 = new byte[MD5LENG+1];
		m_md5[0] = '\0';
		m_data = new char[MAXLENG];
		m_data[0]= '\0';
	}

	UserDataType(const UserDataType  &IDL_s);

	~UserDataType(){		
		delete[] m_data;
		delete[] m_md5;
		m_data = NULL;
		m_md5 = NULL;
	}

	int StructSize()
	{
		int strSize = 0;
		strSize += sizeof(UserDataType);
		strSize += strlen(m_data);
		strSize += MD5LENG;
		return strSize;
	}
	UserDataType& operator= (const UserDataType &IDL_s);

	void Marshal(CDR *cdr) const;
	void UnMarshal(CDR *cdr);

	byte* m_md5;
	char* m_data;
  
};

typedef sequence<UserDataType> UserDataTypeSeq;

#endif




#endif /*IDL_UserDataType_hh */

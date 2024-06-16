// Don't modify this file as it will be overwritten.
//
#include "IDL_UserDataType.h"

UserDataType::UserDataType(const UserDataType &IDL_s){
  m_data = IDL_s.m_data;
  m_md5 = IDL_s.m_md5;
}

UserDataType& UserDataType::operator= (const UserDataType &IDL_s){
  if (this == &IDL_s) return *this;
  m_data = IDL_s.m_data;
  m_md5 = IDL_s.m_md5;
  return *this;
}

void UserDataType::Marshal(CDR *cdr) const {
  cdr->PutString(m_data);
  cdr->PutByteStr(m_md5,MD5LENG);
}

void UserDataType::UnMarshal(CDR *cdr){
  {
    char *IDL_str;
	byte* IDL_md5= new byte[MD5LENG + 1];
	memset(IDL_md5,0, MD5LENG + 1);
    cdr->GetString(IDL_str);
	cdr->GetByteStr(IDL_md5,MD5LENG);
    if(m_data != NULL )
    {
        delete m_data;
		m_data = NULL;
    }
	m_data = IDL_str;
	if (m_md5 != NULL)
	{
		delete m_md5;
		m_md5 = NULL;
	}
	m_md5 = IDL_md5;
  }
}


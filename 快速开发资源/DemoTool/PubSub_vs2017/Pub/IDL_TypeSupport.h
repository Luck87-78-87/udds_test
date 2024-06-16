#ifndef _IDL_TYPESUPPORT_H_INCLUDED_ 
#define _IDL_TYPESUPPORT_H_INCLUDED_

#include <string>
using std::string;
#include "IDL_DataWriter.h"
#include "IDL_DataReader.h"
#include "DDS/TypeSupport.h"
#include "md5.h"
#include "DDS/DomainParticipant.h"
#include <time.h>

class DomainParticipant;

list<string> ListData;
static void initList()
{	if (ListData.size() <= 0)
	{
		ListData.push_back("struct UserDataType{");
		ListData.push_back("string 16 m_md5;");
		ListData.push_back("string 1024 m_data;");
		ListData.push_back("};");
	}
}

class UserDataTypeTypeSupport : public TypeSupport {
public:
	static UserDataType* create_data()
	{
		return new UserDataType;
	}

	static ReturnCode_t delete_data(UserDataType* pUserDataType)
	{
		delete pUserDataType;
		pUserDataType = NULL;
		return ReturnCode_t();
	}
	static double t;
	static int nReadNum;
	//���Ķ����ݴ���
	static void print_data(UserDataType* pUserDataType,int layer = 0)
	{
		nReadNum++;
		clock_t begin = clock();
		MD5 md5(string(pUserDataType->m_data));
		if(memcpy_s(pUserDataType->m_md5, MD5LENG, md5.toString().c_str(),MD5LENG) != 0)
		{
			cout << "MD5ֵ不同！！！！" << endl;
		}
		else
		{
			cout << "MD5ֵ相同" << endl;
		}
		clock_t end = clock();
		t += (double)(end - begin) / CLOCKS_PER_SEC;

		if (t >= 1.0)
		{
			cout << "吞吐量为:" << nReadNum * string(pUserDataType->m_data).size() * 8.0 << "Mbps" << endl;
			nReadNum = 0;
			t = 0;
		}
	}

	static const char* get_type_name()
	{
		return "UserDataType";
	}

	static int register_type(DomainParticipant* participant, string type_name)
	{
		if (type_name.empty())
			type_name = get_type_name();

		initList();
		return participant->register_type(type_name,ListData);
	}
};
double UserDataTypeTypeSupport::t = 0;
int UserDataTypeTypeSupport::nReadNum = 0;

#endif

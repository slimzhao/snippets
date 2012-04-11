/*lint +e* -elib(*) -e966 -e964 -e755 -e757 -e970 */
#include "FrequentlyUsedHeaders.h"
// The following lines makes it possible that only /Yu is specified on the
// command line

// Remove #ifdef ... #endif   because VC will stop to compile, don't
// know why
//
// Comment out the following line will allow you to *NOT* use PCH file
// temporary, in such case you can try out any CC_OPTIONS which is
// incompatible with PCH
#pragma hdrstop( "FrequentlyUsedHeaders.pch" )
// ��δ�����Ҫ���Ҹոտ��� Generic programming and STL, ��Ѫ����, ����
// ���е�STL������ʵ����irdeto�ϻ����Ե���Ŀ. ��Ҫ�õ���STL�������㷨,
// ��������, for_each, vector��.
//
// ������������: 1. VC2010 �Ѿ�ʵ�����ں����ڲ���������Ϳ�����Ϊģ���
// ���Ͳ���, ����һ�� C++11 ������Ĺ���.
// ���ҪGCC֧��, ��Ҫ-std=c++0x, ��VC2010����Ҫ�������, �Ϳ���Ĭ��֧��
// .
// ��virtual������non-const��Ϊconstʱ, ����ԭ����������override�ĺ���,
// ����������к�����ȫ��ͬ������virtual����, ���ִ����ҽ�����һ�����Ͽ�
// ��������, û�뵽��ô�����������Ӧ����, ��ѵ: ��legacy������virtual��
// Ա�������const����ʱ, һ��Ҫ���������ص�����, ͬʱҲ����const, ��
// ��ú����Ͳ����Ǳ����าд���麯����. ˵���������GetType

using namespace std;
using namespace boost;

#ifdef _MSC_VER
// Press F4 to switch the warning /W4 and /W0
#pragma warning(push, 2)
#endif

// CL_OPTIONS:  /Od
// CC_OPTIONS: 

class Employee
{
public:
	enum EmployeeType { E_Employee, E_Manager };
	Employee(const char * name, int weight): name_(name), weight_(weight) { }
	virtual ~Employee() { }
	virtual EmployeeType GetType() const { return E_Employee; }
	const string & GetName() const { return name_; }
	int GetWeight() const { return weight_; }
private:
	string name_;
	int weight_;
};

class Manager: public Employee {
public:
	Manager(const char *name, int weight): Employee(name, weight) {}
	virtual EmployeeType GetType() const { return E_Manager; }
};
int main(int argc, char *argv[])
{
	argc = argc;
	argv = argv;
	// The following lines make the output to stdout and stderr are
	// line-buffered, i.e., when a "\n" is encountered, the output is
	// flushed
	setvbuf( stdout, NULL, _IONBF, 0);
	setvbuf( stderr, NULL, _IONBF, 0);
	
	// DEBUG: Un-comment the following line to debug the program.
	// ERR_MSG_BOX("Attach me to a debugger and then click OK");
	
	//
	// Begin your code here
	// 
	std::vector<Employee*> all;
	all.push_back( new Employee("zhang", 34) );
	all.push_back( new Manager("wang", 27) );
	all.push_back( new Employee("li", 21) );
	all.push_back( new Manager("zhao", 25) );


struct Sorter {
	bool operator()(Employee * x, Employee * y) {

		// ����һ���������ʵ���������Ĵ�����, ����Ҫ��: ����������
		// ��, ���������ͬ, ������ weight����, ȫ��ʹ������.
		// ��һ��������ʾ��, ��ʹ���Ƽ򵥵������߼�����, Ҳ��������ʵ��
		// ����ʱ��������.
		// ��һ������"�ջ�"��, vc��ʵ�ֻ�������ʱ����һ��assert�Ի���,
		// ˵��ʵ�ֵ�operator< ��������ȷ, �����������ļ��, ��Ϊ
		// operator<��Ҫ�Է���, Ҳ����˵���a < b����, �� b < a�Ͳ�Ӧ��
		// ������.
		// ͬ���ļ��GCC û��.
		// return x->GetType() < y->GetType() || x->GetWeight() < y->GetWeight();
#if 1
		if (x->GetType() < y->GetType() ) {
			return true;
		}
		return x->GetType() == y->GetType() && x->GetWeight() < y->GetWeight();
#endif
	}
};


struct PrintEmployee {
	void operator() (Employee * who) {
		printf("name: [%s], type: [%s], weight: %d\n", who->GetName().c_str(), 
				(who->GetType() == Employee::E_Employee) ? "Employee " : "Manager" ,
				who->GetWeight() );
	}
};

struct FreeEmployee {
	void operator() (const Employee * who) { delete who; }
};

	std::sort(all.begin(), all.end(),  Sorter() );
	for_each(all.begin(), all.end(), PrintEmployee());
	for_each(all.begin(), all.end(), FreeEmployee());
	return 0;
}


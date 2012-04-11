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
// 这段代码主要是我刚刚看了 Generic programming and STL, 心血来潮, 想以
// 书中的STL技术来实现在irdeto上机测试的题目. 主要用到的STL有排序算法,
// 函数对象, for_each, vector等.
//
// 碰到的问题有: 1. VC2010 已经实现了在函数内部定义的类型可以作为模板的
// 类型参数, 这是一项 C++11 新引入的功能.
// 如果要GCC支持, 需要-std=c++0x, 而VC2010不需要额外参数, 就可以默认支持
// .
// 将virtual函数从non-const改为const时, 导致原本派生类中override的函数,
// 成了与基类中函数完全不同的两个virtual函数, 这种错误我近日在一本书上看
// 到过警告, 没想到这么快就在我身上应验了, 教训: 向legacy代码中virtual成
// 员函数添加const修饰时, 一定要检查整个相关的子类, 同时也加上const, 否
// 则该函数就不再是被子类覆写的虚函数了. 说的是下面的GetType

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

		// 下面一行是我最初实现排序规则的错误结果, 排序要求: 先以类型排
		// 序, 如果类型相同, 则再以 weight排序, 全部使用升序.
		// 这一个错误显示了, 即使看似简单的两个逻辑条件, 也很容易在实际
		// 编码时产生错误.
		// 另一个额外"收获"是, vc的实现会在运行时弹出一个assert对话框,
		// 说明实现的operator< 函数不正确, 这是相对深入的检查, 因为
		// operator<需要自反的, 也就是说如果a < b成立, 则 b < a就不应该
		// 成立了.
		// 同样的检查GCC 没有.
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


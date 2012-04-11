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

// More effective c++ item 27中, 展示了 dynamic_cast的一个特殊用途: 找出
// 一个对象的起始地址. 如下例, B 和 C均为含有虚函数的类, D多重继承自B和
// C. 真实的对象是D, B与D共享对象的起始地址, 故意这么做是为了让C无论如何
// 也不会在对象的起始地址处, 但是, 通过dynamic_cast将c的地址转换为 void
// *后, 可以得到完整对象的起始地址, 而不是嵌在完整对象内部的基类对象C的
// 起始地址. 类似这个手法在boost库中看到一次, 但当时没注意, 没想到这是
// dynamic_cast的一个特性.
//
// 忘了在什么地方看到用dyna_cast宏代替 dynamic_cast的, 虽然只少输入了3个
// 字符, 却显得清爽的多, scott说的没错, 目前还不是宏全面引退的时候, 它有
// 时候的确很有用.
// pb: 003D5CA0, pc: 003D5CA4, pd: 003D5CA0,  p = 003D5CA0
using namespace std;
using namespace boost;

#ifdef _MSC_VER
// Press F4 to switch the warning /W4 and /W0
#pragma warning(push, 2)
#endif

// CL_OPTIONS:
// CC_OPTIONS: 

class B {public: virtual ~B() {} };
class C {public: virtual ~C() {}  };
class D: public B, public C {};
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
	B * pb = new D;
	C * pc = dynamic_cast<C*>(pb);
	D * pd = dynamic_cast<D*>(pb);
	void * p = dynamic_cast<void*>(pc);
	printf("pb: %p, pc: %p, pd: %p,  p = %p\n", pb, pc, pd, p);
	return 0;
}


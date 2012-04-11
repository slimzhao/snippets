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

// More effective c++ item 27��, չʾ�� dynamic_cast��һ��������;: �ҳ�
// һ���������ʼ��ַ. ������, B �� C��Ϊ�����麯������, D���ؼ̳���B��
// C. ��ʵ�Ķ�����D, B��D����������ʼ��ַ, ������ô����Ϊ����C�������
// Ҳ�����ڶ������ʼ��ַ��, ����, ͨ��dynamic_cast��c�ĵ�ַת��Ϊ void
// *��, ���Եõ������������ʼ��ַ, ������Ƕ�����������ڲ��Ļ������C��
// ��ʼ��ַ. ��������ַ���boost���п���һ��, ����ʱûע��, û�뵽����
// dynamic_cast��һ������.
//
// ������ʲô�ط�������dyna_cast����� dynamic_cast��, ��Ȼֻ��������3��
// �ַ�, ȴ�Ե���ˬ�Ķ�, scott˵��û��, Ŀǰ�����Ǻ�ȫ�����˵�ʱ��, ����
// ʱ���ȷ������.
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


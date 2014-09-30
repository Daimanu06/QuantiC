#include "compilation_infos.h"

//Operating system name
const char* os_name() {
#if defined(Q_OS_LINUX)
	return "GNU/Linux";
#elif defined(Q_OS_ANDROID)
	return "Android";
#elif defined(Q_OS_UNIX)
	return "unix";
#elif defined(Q_OS_OSX)
	return "OSX";
#elif defined(Q_OS_FREEBSD)
	return "FreeBSD";
#elif defined(Q_OS_SOLARIS)
	return "Oracle Solaris";
#elif defined(Q_OS_NETBSD)
	return "NetBSD";
#elif defined(Q_OS_OPENBSD)
	return "OpenBSD";
#elif defined(Q_OS_AIX)
	return "AIX";
#elif defined(Q_OS_BSD4)
	return "BSD";
#elif defined(Q_OS_HPUX)
	return "HP/UX";
#elif defined(Q_OS_WIN32)
	return "win32";
#elif defined(Q_OS_WIN_64)
	return "win64";
#elif defined(Q_OS_WINPHONE)
	return "Windows Phone";
#elif defined(Q_OS_WINRT)
	return "Windows RT";
#elif defined(Q_OS_WINCE)
	return "Windows CE";
#endif
	return "unknown";
}

// Compiler name
const char* cc_name() {
#if defined(Q_CC_GNU)
	return "GNU G++";
#elif defined(Q_CC_MSVC)
	return "Microsoft Visual Studio C/C++";
#endif
	return "unknown";
}

//processor name
const char* proc_name() {
#if defined(Q_PROCESSOR_X86_32)
	return "32 bits x86";
#elif defined(Q_PROCESSOR_X86_64)
	return "64 bits x86";
#elif defined(Q_PROCESSOR_ARM_V5)
	return "ARM v5";
#elif defined(Q_PROCESSOR_ARM_V6)
	return "ARM v6";
#elif defined(Q_PROCESSOR_ARM_V7)
	return "ARM v7";
#endif
	return "unknown";
}

//processor register size
const char* proc_register() {
#if defined(Q_PROCESSOR_X86_64)
	return "64";
#elif defined(Q_PROCESSOR_X86_32)
	return "32"
#endif
	return "unknown";
}

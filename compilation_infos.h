#ifndef COMPILATION_INFO_H
#define COMPILATION_INFO_H

#include <QtCore/QtGlobal>

#ifdef Q_OS_ANDROID
#	define OS_MOBILE
#endif
//Do the same with other mobile os (OSX, Ubuntu mobile, Windows phone)

//Operating system name
const char* os_name();

//Compiler name
const char* cc_name();

//Processor type
const char* proc_name();

//Processor register size
const char* proc_register();

#endif // COMPILATION_INFO_H

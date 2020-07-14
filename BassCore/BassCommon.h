#pragma once
#define SafeDelete(x) { if(nullptr != x) { delete x; x = nullptr; } }
#define SafeDeleteArray(x) { if(nullptr != x) { delete[] x; x = nullptr;}}
#define SafeRelease(x) { if(NULL != x) { x->Release(); x = NULL; }}

#define AutoLock(x) std::lock_guard<std::mutex> __AUTO_LOCK__##x(x)
#define AutoLockR(x) std::lock_guard<std::recursive_mutex> __AUTO_LOCKR__##x(x)

#define TO_STRING(x) _TO_STRING(x)
#define _TO_STRING(x) #x
#define NOTICE __FILE__ "(" TO_STRING(__LINE__) ") : "

#ifdef DALEXPORT
#define DALAPI __declspec(dllexport)
#else
#define DALAPI __declspec(dllimport)
#endif
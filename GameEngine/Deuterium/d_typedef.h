#ifdef DEUTERIUM_PC
typedef unsigned	__int32	U32;
typedef				__int32	S32;
typedef unsigned	__int16	U16;
typedef				__int16 S16;
typedef unsigned	__int8	U8;
typedef				__int8	S8;
#elif defined(EMSCRIPTEN)
typedef uint32_t  	U32;
typedef int32_t 	S32;
typedef	uint16_t 	U16;
typedef int16_t 	S16;
typedef	uint8_t		U8;
typedef int8_t		S8;
#elif defined(ANDROID)
#include <inttypes.h>
typedef uint32_t  	U32;
typedef int32_t 	S32;
typedef	uint16_t 	U16;
typedef int16_t 	S16;
typedef	uint8_t		U8;
typedef int8_t		S8;
#endif	// _MCVS2012_
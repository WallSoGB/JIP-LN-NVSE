#include "internal/utility.h"
#include "nvse/GameAPI.h"

const float
kFlt1d1000 = 0.001F,
kFlt1d200 = 0.005F,
kFlt1d100 = 0.01F,
kFltPId180 = 0.01745329238F,
kFlt1d10 = 0.1F,
kFltHalf = 0.5F,
kFltOne = 1.0F,
kFltPId2 = 1.5707963268F,
kFlt10 = 10.0F,
kFlt180dPI = 57.2957795F,
kFlt100 = 100.0F,
kFlt200 = 200.0F,
kFlt1000 = 1000.0F,
kFltMax = FLT_MAX;

const double
kDblPId180 = 0.017453292519943295,
kDbl180dPI = 57.29577951308232088;

alignas(16) const UInt32
kSSERemoveSignMaskPS[] = {0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF},
kSSEChangeSignMaskPS[] = {0x80000000, 0x80000000, 0x80000000, 0x80000000},
kSSEDiscard4thPS[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000};

alignas(16) const UInt64
kSSERemoveSignMaskPD[] = {0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF},
kSSEChangeSignMaskPD[] = {0x8000000000000000, 0x8000000000000000};

alignas(16) const char
kLwrCaseConverter[] =
{
	'\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
	'\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
	'\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
	'\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
	'\x40', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
	'\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
	'\x60', '\x61', '\x62', '\x63', '\x64', '\x65', '\x66', '\x67', '\x68', '\x69', '\x6A', '\x6B', '\x6C', '\x6D', '\x6E', '\x6F',
	'\x70', '\x71', '\x72', '\x73', '\x74', '\x75', '\x76', '\x77', '\x78', '\x79', '\x7A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
	'\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
	'\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x96', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
	'\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xA8', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
	'\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
	'\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
	'\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF',
	'\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
	'\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF'
},
kUprCaseConverter[] =
{
	'\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C', '\x0D', '\x0E', '\x0F',
	'\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17', '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
	'\x20', '\x21', '\x22', '\x23', '\x24', '\x25', '\x26', '\x27', '\x28', '\x29', '\x2A', '\x2B', '\x2C', '\x2D', '\x2E', '\x2F',
	'\x30', '\x31', '\x32', '\x33', '\x34', '\x35', '\x36', '\x37', '\x38', '\x39', '\x3A', '\x3B', '\x3C', '\x3D', '\x3E', '\x3F',
	'\x40', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F',
	'\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5A', '\x5B', '\x5C', '\x5D', '\x5E', '\x5F',
	'\x60', '\x41', '\x42', '\x43', '\x44', '\x45', '\x46', '\x47', '\x48', '\x49', '\x4A', '\x4B', '\x4C', '\x4D', '\x4E', '\x4F',
	'\x50', '\x51', '\x52', '\x53', '\x54', '\x55', '\x56', '\x57', '\x58', '\x59', '\x5A', '\x7B', '\x7C', '\x7D', '\x7E', '\x7F',
	'\x80', '\x81', '\x82', '\x83', '\x84', '\x85', '\x86', '\x87', '\x88', '\x89', '\x8A', '\x8B', '\x8C', '\x8D', '\x8E', '\x8F',
	'\x90', '\x91', '\x92', '\x93', '\x94', '\x95', '\x96', '\x97', '\x98', '\x99', '\x9A', '\x9B', '\x9C', '\x9D', '\x9E', '\x9F',
	'\xA0', '\xA1', '\xA2', '\xA3', '\xA4', '\xA5', '\xA6', '\xA7', '\xA8', '\xA9', '\xAA', '\xAB', '\xAC', '\xAD', '\xAE', '\xAF',
	'\xB0', '\xB1', '\xB2', '\xB3', '\xB4', '\xB5', '\xB6', '\xB7', '\xB8', '\xB9', '\xBA', '\xBB', '\xBC', '\xBD', '\xBE', '\xBF',
	'\xC0', '\xC1', '\xC2', '\xC3', '\xC4', '\xC5', '\xC6', '\xC7', '\xC8', '\xC9', '\xCA', '\xCB', '\xCC', '\xCD', '\xCE', '\xCF',
	'\xD0', '\xD1', '\xD2', '\xD3', '\xD4', '\xD5', '\xD6', '\xD7', '\xD8', '\xD9', '\xDA', '\xDB', '\xDC', '\xDD', '\xDE', '\xDF',
	'\xE0', '\xE1', '\xE2', '\xE3', '\xE4', '\xE5', '\xE6', '\xE7', '\xE8', '\xE9', '\xEA', '\xEB', '\xEC', '\xED', '\xEE', '\xEF',
	'\xF0', '\xF1', '\xF2', '\xF3', '\xF4', '\xF5', '\xF6', '\xF7', '\xF8', '\xF9', '\xFA', '\xFB', '\xFC', '\xFD', '\xFE', '\xFF'
};

memcpy_t MemCopy = memcpy, MemMove = memmove;

#define FAST_SLEEP_COUNT 10000UL

__declspec(naked) PrimitiveCS *PrimitiveCS::Enter()
{
	__asm
	{
		push	ebx
		mov		ebx, ecx
		call	GetCurrentThreadId
		cmp		[ebx], eax
		jnz		doSpin
	done:
		mov		eax, ebx
		pop		ebx
		retn
		NOP_0xA
	doSpin:
		mov		ecx, eax
		xor		eax, eax
		lock cmpxchg [ebx], ecx
		test	eax, eax
		jz		done
		push	esi
		push	edi
		mov		esi, ecx
		mov		edi, FAST_SLEEP_COUNT
	spinHead:
		dec		edi
		mov		edx, edi
		shr		edx, 0x1F
		push	edx
		call	Sleep
		xor		eax, eax
		lock cmpxchg [ebx], esi
		test	eax, eax
		jnz		spinHead
		pop		edi
		pop		esi
		mov		eax, ebx
		pop		ebx
		retn
	}
}

__declspec(naked) void LightCS::Enter()
{
	__asm
	{
		push	ebx
		mov		ebx, ecx
		call	GetCurrentThreadId
		cmp		[ebx], eax
		jnz		doSpin
		inc		dword ptr [ebx+4]
		pop		ebx
		retn
		NOP_0x9
	doSpin:
		mov		ecx, eax
		xor		eax, eax
		lock cmpxchg [ebx], ecx
		test	eax, eax
		jz		done
		push	esi
		push	edi
		mov		esi, ecx
		mov		edi, FAST_SLEEP_COUNT
	spinHead:
		dec		edi
		mov		edx, edi
		shr		edx, 0x1F
		push	edx
		call	Sleep
		xor		eax, eax
		lock cmpxchg [ebx], esi
		test	eax, eax
		jnz		spinHead
		pop		edi
		pop		esi
	done:
		mov		dword ptr [ebx+4], 1
		pop		ebx
		retn
	}
}

__declspec(naked) TESForm* __stdcall LookupFormByRefID(UInt32 refID)
{
	__asm
	{
		mov		ecx, ds:[0x11C54C0]
		mov		eax, [esp+4]
		xor		edx, edx
		div		dword ptr [ecx+4]
		mov		eax, [ecx+8]
		mov		eax, [eax+edx*4]
		test	eax, eax
		jz		done
		mov		edx, [esp+4]
		ALIGN 16
	iterHead:
		cmp		[eax+4], edx
		jz		found
		mov		eax, [eax]
		test	eax, eax
		jnz		iterHead
		retn	4
	found:
		mov		eax, [eax+8]
	done:
		retn	4
	}
}

__declspec(naked) UInt32 __vectorcall cvtd2ui(double value)
{
	__asm
	{
		lea		eax, [esp-8]
		movq	qword ptr [eax], xmm0
		fld		qword ptr [eax]
		fisttp	qword ptr [eax]
		mov		eax, [eax]
		retn
	}
}

__declspec(naked) double __vectorcall cvtui2d(UInt32 value)
{
	__asm
	{
		push	0
		push	ecx
		fild	qword ptr [esp]
		fstp	qword ptr [esp]
		movq	xmm0, qword ptr [esp]
		add		esp, 8
		retn
	}
}

__declspec(naked) void __fastcall cvtui2d(UInt32 value, double *result)
{
	__asm
	{
		mov		[edx], ecx
		mov		dword ptr [edx+4], 0
		fild	qword ptr [edx]
		fstp	qword ptr [edx]
		retn
	}
}

__declspec(naked) int __vectorcall ifloor(float value)
{
	__asm
	{
		movd	eax, xmm0
		test	eax, eax
		jns		isPos
		push	0x3FA0
		ldmxcsr	[esp]
		cvtss2si	eax, xmm0
		mov		byte ptr [esp+1], 0x1F
		ldmxcsr	[esp]
		pop		ecx
		retn
	isPos:
		cvttss2si	eax, xmm0
		retn
	}
}

__declspec(naked) int __vectorcall iceil(float value)
{
	__asm
	{
		movd	eax, xmm0
		test	eax, eax
		js		isNeg
		push	0x5FA0
		ldmxcsr	[esp]
		cvtss2si	eax, xmm0
		mov		byte ptr [esp+1], 0x1F
		ldmxcsr	[esp]
		pop		ecx
		retn
	isNeg:
		cvttss2si	eax, xmm0
		retn
	}
}

__declspec(noinline) char *GetStrArgBuffer()
{
	thread_local char *s_strBuffer = NULL;
	if (!s_strBuffer)
		s_strBuffer = (char*)_aligned_malloc(0x20000, 0x10);
	return s_strBuffer;
}

__declspec(naked) void __fastcall NiReleaseObject(NiRefObject *toRelease)
{
	__asm
	{
		lock dec dword ptr [ecx+4]
		jg		done
		mov		eax, [ecx]
		call	dword ptr [eax+4]
	done:
		retn
	}
}

__declspec(naked) NiRefObject** __stdcall NiReleaseAddRef(void *toRelease, NiRefObject *toAdd)
{
	__asm
	{
		mov		eax, [esp+4]
		mov		ecx, [eax]
		cmp		ecx, [esp+8]
		jz		done
		test	ecx, ecx
		jz		doAdd
		lock dec dword ptr [ecx+4]
		jg		doAdd
		mov		eax, [ecx]
		call	dword ptr [eax+4]
		mov		eax, [esp+4]
	doAdd:
		mov		ecx, [esp+8]
		mov		[eax], ecx
		test	ecx, ecx
		jz		done
		lock inc dword ptr [ecx+4]
	done:
		retn	8
	}
}

__declspec(naked) UInt32 __fastcall RGBHexToDec(UInt32 rgb)
{
	__asm
	{
		movzx	eax, cl
		imul	eax, 0xF4240
		movzx	edx, ch
		imul	edx, 0x3E8
		add		eax, edx
		shr		ecx, 0x10
		add		eax, ecx
		retn
	}
}

__declspec(naked) UInt32 __fastcall RGBDecToHex(UInt32 rgb)
{
	__asm
	{
		push	ebx
		mov		eax, ecx
		mov		ecx, 0xF4240
		xor		edx, edx
		div		ecx
		mov		ebx, eax
		mov		eax, edx
		mov		ecx, 0x3E8
		xor		edx, edx
		div		ecx
		shl		eax, 8
		add		eax, ebx
		shl		edx, 0x10
		add		eax, edx
		pop		ebx
		retn
	}
}

__declspec(naked) UInt32 __fastcall StrLen(const char *str)
{
	__asm
	{
		test	ecx, ecx
		jz		nullPtr
		push	ecx
		test	ecx, 3
		jz		iter4
		ALIGN 16
	iter1:
		mov		al, [ecx]
		inc		ecx
		test	al, al
		jz		done1
		test	ecx, 3
		jnz		iter1
		ALIGN 16
	iter4:
		mov		eax, [ecx]
		mov		edx, 0x7EFEFEFF
		add		edx, eax
		not		eax
		xor		eax, edx
		add		ecx, 4
		test	eax, 0x81010100
		jz		iter4
		mov		eax, [ecx-4]
		test	al, al
		jz		done4
		test	ah, ah
		jz		done3
		test	eax, 0xFF0000
		jz		done2
		test	eax, 0xFF000000
		jnz		iter4
	done1:
		lea		eax, [ecx-1]
		pop		ecx
		sub		eax, ecx
		retn
	done2:
		lea		eax, [ecx-2]
		pop		ecx
		sub		eax, ecx
		retn
	done3:
		lea		eax, [ecx-3]
		pop		ecx
		sub		eax, ecx
		retn
	done4:
		lea		eax, [ecx-4]
		pop		ecx
		sub		eax, ecx
		retn
	nullPtr:
		xor		eax, eax
		retn
	}
}

__declspec(naked) bool __fastcall MemCmp(const void *ptr1, const void *ptr2, UInt32 bsize)
{
	__asm
	{
		push	esi
		push	edi
		mov		esi, ecx
		mov		edi, edx
		mov		ecx, [esp+0xC]
		shr		ecx, 2
		repe cmpsd
		setz	al
		pop		edi
		pop		esi
		retn	4
	}
}

__declspec(naked) void __fastcall MemZero(void *dest, UInt32 bsize)
{
	__asm
	{
		test	ecx, ecx
		jz		done
		shr		edx, 2
		jz		done
		push	edi
		mov		edi, ecx
		xor		eax, eax
		mov		ecx, edx
		rep stosd
		pop		edi
	done:
		retn
	}
}

__declspec(naked) char* __fastcall StrCopy(char *dest, const char *src)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		nullTerm
		push	ecx
		mov		ecx, edx
		call	StrLen
		pop		edx
		push	eax
		inc		eax
		push	eax
		push	ecx
		push	edx
		call	MemMove
		add		esp, 0xC
		pop		ecx
		add		eax, ecx
		retn
	nullTerm:
		mov		[eax], 0
	done:
		retn
	}
}

__declspec(naked) char* __fastcall StrNCopy(char *dest, const char *src, UInt32 length)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		nullTerm
		cmp		dword ptr [esp+4], 0
		jz		nullTerm
		push	esi
		mov		esi, ecx
		mov		ecx, edx
		call	StrLen
		mov		edx, [esp+8]
		cmp		edx, eax
		cmova	edx, eax
		push	edx
		push	ecx
		push	esi
		add		esi, edx
		call	MemMove
		add		esp, 0xC
		mov		eax, esi
		pop		esi
	nullTerm:
		mov		[eax], 0
	done:
		retn	4
	}
}

__declspec(naked) char* __fastcall StrLenCopy(char *dest, const char *src, UInt32 length)
{
	__asm
	{
		mov		eax, ecx
		test	ecx, ecx
		jz		done
		test	edx, edx
		jz		nullTerm
		mov		ecx, [esp+4]
		test	ecx, ecx
		jz		nullTerm
		push	ecx
		push	edx
		push	eax
		call	MemMove
		add		esp, 0xC
		add		eax, [esp+4]
	nullTerm:
		mov		[eax], 0
	done:
		retn	4
	}
}

__declspec(naked) char* __fastcall StrCat(char *dest, const char *src)
{
	__asm
	{
		test	ecx, ecx
		jz		nullPtr
		push	edx
		call	StrLen
		pop		edx
		add		ecx, eax
		jmp		StrCopy
	nullPtr:
		xor		eax, eax
		retn
	}
}

__declspec(noinline) char __fastcall StrCompare(const char *lstr, const char *rstr)
{
	if (!lstr) return rstr ? -1 : 0;
	if (!rstr) return 1;
	UInt8 lchr, rchr;
	while (*lstr)
	{
		lchr = kLwrCaseConverter[*(UInt8*)lstr];
		rchr = kLwrCaseConverter[*(UInt8*)rstr];
		if (lchr == rchr)
		{
			lstr++;
			rstr++;
			continue;
		}
		return (lchr < rchr) ? -1 : 1;
	}
	return *rstr ? -1 : 0;
}

__declspec(noinline) char __fastcall StrBeginsCS(const char *lstr, const char *rstr)
{
	if (!lstr || !rstr) return 0;
	UInt32 length = StrLen(rstr);
	while (length >= 4)
	{
		if (*(UInt32*)lstr != *(UInt32*)rstr)
			return 0;
		lstr += 4;
		rstr += 4;
		length -= 4;
	}
	while (length)
	{
		if (*lstr != *rstr)
			return 0;
		lstr++;
		rstr++;
		length--;
	}
	return *lstr ? 1 : 2;
}

__declspec(noinline) char __fastcall StrBeginsCI(const char *lstr, const char *rstr)
{
	if (!lstr || !rstr) return 0;
	UInt32 length = StrLen(rstr);
	while (length)
	{
		if (kLwrCaseConverter[*(UInt8*)lstr] != kLwrCaseConverter[*(UInt8*)rstr])
			return 0;
		lstr++;
		rstr++;
		length--;
	}
	return *lstr ? 1 : 2;
}

__declspec(noinline) void __fastcall FixPath(char *str)
{
	UInt8 curr;
	while (curr = *str)
	{
		if (curr == '\\')
			*str = '/';
		else *str = kLwrCaseConverter[curr];
		str++;
	}
}

__declspec(noinline) void __fastcall StrToLower(char *str)
{
	UInt8 curr;
	while (curr = *str)
	{
		*str = kLwrCaseConverter[curr];
		str++;
	}
}

__declspec(noinline) void __fastcall StrToUpper(char *str)
{
	UInt8 curr;
	while (curr = *str)
	{
		*str = kUprCaseConverter[curr];
		str++;
	}
}

__declspec(naked) void __fastcall ReplaceChr(char *str, char from, char to)
{
	__asm
	{
	iterHead:
		mov		al, [ecx]
		test	al, al
		jz		done
		inc		ecx
		cmp		al, dl
		jnz		iterHead
		mov		al, [esp+4]
		mov		[ecx-1], al
		jmp		iterHead
		ALIGN 16
	done:
		retn	4
	}
}

__declspec(naked) char* __fastcall FindChr(const char *str, char chr)
{
	__asm
	{
	iterHead:
		mov		al, [ecx]
		test	al, al
		jz		retnNULL
		cmp		al, dl
		jz		found
		inc		ecx
		jmp		iterHead
		ALIGN 16
	found:
		mov		eax, ecx
		retn
		ALIGN 16
	retnNULL:
		xor		eax, eax
		retn
	}
}

__declspec(naked) char* __fastcall FindChrR(const char *str, UInt32 length, char chr)
{
	__asm
	{
		lea		eax, [ecx+edx]
		mov		dl, [esp+4]
		ALIGN 16
	iterHead:
		cmp		eax, ecx
		jz		retnNULL
		dec		eax
		mov		dh, [eax]
		cmp		dl, dh
		jnz		iterHead
		retn	4
		ALIGN 16
	retnNULL:
		xor		eax, eax
		retn	4
	}
}

__declspec(noinline) char* __fastcall SubStrCI(const char *srcStr, const char *subStr)
{
	int srcLen = StrLen(srcStr);
	if (!srcLen) return NULL;
	int subLen = StrLen(subStr);
	if (!subLen) return NULL;
	srcLen -= subLen;
	if (srcLen < 0) return NULL;
	int index;
	do
	{
		index = 0;
		while (true)
		{
			if (kLwrCaseConverter[*(UInt8*)(srcStr + index)] != kLwrCaseConverter[*(UInt8*)(subStr + index)])
				break;
			if (++index == subLen)
				return const_cast<char*>(srcStr);
		}
		srcStr++;
	}
	while (--srcLen >= 0);
	return NULL;
}

__declspec(naked) char* __fastcall SlashPos(const char *str)
{
	__asm
	{
	iterHead:
		mov		dl, [ecx]
		test	dl, dl
		jz		retnNULL
		cmp		dl, '\\'
		jz		found
		cmp		dl, '/'
		jz		found
		inc		ecx
		jmp		iterHead
		ALIGN 16
	found:
		mov		eax, ecx
		retn
		ALIGN 16
	retnNULL:
		xor		eax, eax
		retn
	}
}

__declspec(naked) char* __fastcall SlashPosR(const char *str)
{
	__asm
	{
		call	StrLen
		add		eax, ecx
		ALIGN 16
	iterHead:
		cmp		eax, ecx
		jz		retnNULL
		dec		eax
		mov		dl, [eax]
		cmp		dl, '\\'
		jz		found
		cmp		dl, '/'
		jnz		iterHead
	found:
		retn
		ALIGN 16
	retnNULL:
		xor		eax, eax
		retn
	}
}

__declspec(noinline) char* __fastcall GetNextToken(char *str, char delim)
{
	if (!str) return NULL;
	bool found = false;
	char chr;
	while (chr = *str)
	{
		if (chr == delim)
		{
			*str = 0;
			found = true;
		}
		else if (found)
			break;
		str++;
	}
	return str;
}

__declspec(noinline) char* __fastcall GetNextToken(char *str, const char *delims)
{
	if (!str) return NULL;
	bool table[0x100];
	MemZero(table, 0x100);
	UInt8 curr;
	while (curr = *delims)
	{
		table[curr] = true;
		delims++;
	}
	bool found = false;
	while (curr = *str)
	{
		if (table[curr])
		{
			*str = 0;
			found = true;
		}
		else if (found)
			break;
		str++;
	}
	return str;
}

__declspec(naked) char* __fastcall CopyString(const char *key)
{
	__asm
	{
		call	StrLen
		inc		eax
		push	eax
		push	ecx
		push	eax
		call	malloc
		pop		ecx
		push	eax
		call	MemCopy
		add		esp, 0xC
		retn
	}
}

__declspec(naked) char* __fastcall CopyCString(const char *src)
{
	__asm
	{
		call	StrLen
		test	eax, eax
		jz		done
		inc		eax
		push	eax
		push	ecx
		push	eax
		GAME_HEAP_ALLOC
		push	eax
		call	MemCopy
		add		esp, 0xC
	done:
		retn
	}
}

__declspec(naked) char* __fastcall IntToStr(char *str, int num)
{
	__asm
	{
		push	esi
		push	edi
		test	edx, edx
		jns		skipNeg
		neg		edx
		mov		[ecx], '-'
		inc		ecx
	skipNeg:
		mov		esi, ecx
		mov		edi, ecx
		mov		eax, edx
		mov		ecx, 0xA
		ALIGN 16
	workIter:
		xor		edx, edx
		div		ecx
		add		dl, '0'
		mov		[esi], dl
		inc		esi
		test	eax, eax
		jnz		workIter
		mov		[esi], 0
		mov		eax, esi
		ALIGN 16
	swapIter:
		dec		esi
		cmp		esi, edi
		jbe		done
		mov		dl, [esi]
		mov		cl, [edi]
		mov		[esi], cl
		mov		[edi], dl
		inc		edi
		jmp		swapIter
	done:
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) char* __vectorcall FltToStr(char *str, double value)
{
	static const double kDbl1Mil = 1000000.0;
	static const int kIntDivisors[] = {10, 100, 1000, 10000, 100000};
	__asm
	{
		pxor	xmm1, xmm1
		comisd	xmm0, xmm1
		jnz		nonZero
		mov		word ptr [ecx], '0'
		lea		eax, [ecx+1]
		retn
	nonZero:
		ja		isPos
		andpd	xmm0, kSSERemoveSignMaskPD
		mov		[ecx], '-'
		inc		ecx
	isPos:
		push	esi
		push	edi
		lea		eax, [esp-8]
		movq	qword ptr [eax], xmm0
		fld		qword ptr [eax]
		fld		st
		fisttp	qword ptr [eax]
		mov		esi, [eax]
		fild	qword ptr [eax]
		fsubp	st(1), st
		fstp	qword ptr [eax]
		movq	xmm0, qword ptr [eax]
		/*roundsd	xmm2, xmm0, 3
		lea		eax, [esp-8]
		movq	qword ptr [eax], xmm2
		fld		qword ptr [eax]
		fisttp	qword ptr [eax]
		mov		esi, [eax]
		test	esi, esi
		jz		noInt
		subsd	xmm0, xmm2
	noInt:*/
		xor		edi, edi
		comisd	xmm0, xmm1
		jz		noFrac
		mulsd	xmm0, kDbl1Mil
		cvtsd2si	edi, xmm0
		cmp		edi, 0xF4240
		jnz		noFrac
		xor		edi, edi
		inc		esi
	noFrac:
		test	esi, esi
		jz		zeroInt
		mov		edx, esi
		call	IntToStr
		mov		ecx, eax
		jmp		doneInt
	zeroInt:
		mov		[ecx], '0'
		inc		ecx
	doneInt:
		test	edi, edi
		jz		done
		mov		[ecx], '.'
		inc		ecx
		mov		edx, edi
		mov		esi, offset kIntDivisors
		mov		edi, 4
		ALIGN 16
	fracIter:
		mov		eax, edx
		xor		edx, edx
		div		dword ptr [esi+edi*4]
		add		al, '0'
		mov		[ecx], al
		inc		ecx
		test	edx, edx
		jz		done
		dec		edi
		jns		fracIter
		add		dl, '0'
		mov		[ecx], dl
		inc		ecx
	done:
		mov		[ecx], 0
		mov		eax, ecx
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) int __fastcall StrToInt(const char *str)
{
	__asm
	{
		push	esi
		push	edi
		xor		eax, eax
		test	ecx, ecx
		jz		done
		mov		esi, ecx
		xor		ecx, ecx
		xor		edi, edi
		cmp		[esi], '-'
		setz	dl
		jnz		charIter
		inc		esi
		ALIGN 16
	charIter:
		mov		cl, [esi]
		sub		cl, '0'
		cmp		cl, 9
		ja		iterEnd
		lea		eax, [eax+eax*4]
		lea		eax, [ecx+eax*2]
		cmp		eax, edi
		jl		overflow
		mov		edi, eax
		inc		esi
		jmp		charIter
		ALIGN 16
	iterEnd:
		test	dl, dl
		jz		done
		neg		eax
	done:
		pop		edi
		pop		esi
		retn
	overflow:
		movzx	eax, dl
		add		eax, 0x7FFFFFFF
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) UInt32 __fastcall StrToUInt(const char *str)
{
	__asm
	{
		push	esi
		push	edi
		xor		eax, eax
		test	ecx, ecx
		jz		done
		mov		esi, ecx
		xor		ecx, ecx
		xor		edi, edi
		cmp		[esi], '-'
		setz	dl
		jnz		charIter
		inc		esi
		ALIGN 16
	charIter:
		mov		cl, [esi]
		sub		cl, '0'
		cmp		cl, 9
		ja		iterEnd
		lea		eax, [eax+eax*4]
		lea		eax, [ecx+eax*2]
		cmp		eax, edi
		jb		overflow
		mov		edi, eax
		inc		esi
		jmp		charIter
		ALIGN 16
	iterEnd:
		test	dl, dl
		jz		done
		neg		eax
	done:
		pop		edi
		pop		esi
		retn
	overflow:
		movzx	eax, dl
		dec		eax
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) double __vectorcall StrToDbl(const char *str)
{
	static const double kValueBounds[] = {4294967296, -4294967296}, kFactor10Div[] = {1.0e-09, 1.0e-08, 1.0e-07, 1.0e-06, 1.0e-05, 0.0001, 0.001, 0.01, 0.1};
	__asm
	{
		push	esi
		push	edi
		pxor	xmm0, xmm0
		test	ecx, ecx
		jz		done
		mov		esi, ecx
		xor		eax, eax
		xor		ecx, ecx
		xor		edi, edi
		cmp		[esi], '-'
		setz	dl
		jnz		intIter
		inc		esi
		ALIGN 16
	intIter:
		mov		cl, [esi]
		sub		cl, '0'
		cmp		cl, 9
		ja		intEnd
		lea		eax, [eax+eax*4]
		lea		eax, [ecx+eax*2]
		cmp		eax, edi
		jb		overflow
		mov		edi, eax
		inc		esi
		jmp		intIter
		ALIGN 16
	intEnd:
		test	eax, eax
		jz		noInt
		movd	xmm0, eax
		cvtdq2pd	xmm0, xmm0
		jns		noOverflow
		addsd	xmm0, kValueBounds
	noOverflow:
		shl		dl, 1
		xor		eax, eax
	noInt:
		cmp		cl, 0xFE
		jnz		addSign
		mov		dh, 9
		ALIGN 16
	fracIter:
		inc		esi
		mov		cl, [esi]
		sub		cl, '0'
		cmp		cl, 9
		ja		fracEnd
		lea		eax, [eax+eax*4]
		lea		eax, [ecx+eax*2]
		dec		dh
		jnz		fracIter
	fracEnd:
		test	eax, eax
		jz		addSign
		movd	xmm1, eax
		cvtdq2pd	xmm1, xmm1
		shl		dl, 1
		mov		cl, dh
		mulsd	xmm1, kFactor10Div[ecx*8]
		addsd	xmm0, xmm1
	addSign:
		test	dl, 6
		jz		done
		orpd	xmm0, kSSEChangeSignMaskPD
	done:
		pop		edi
		pop		esi
		retn
	overflow:
		movzx	eax, dl
		movq	xmm0, kValueBounds[eax*8]
		pop		edi
		pop		esi
		retn
	}
}

__declspec(naked) char* __fastcall UIntToHex(char *str, UInt32 num)
{
	static const char kCharAtlas[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	__asm
	{
		bsr		eax, edx
		jz		isZero
		push	esi
		shr		eax, 2
		lea		esi, [ecx+eax+1]
		push	esi
		xor		eax, eax
		ALIGN 16
	workIter:
		mov		al, dl
		and		al, 0xF
		mov		cl, kCharAtlas[eax]
		dec		esi
		mov		[esi], cl
		shr		edx, 4
		jnz		workIter
		pop		eax
		mov		[eax], 0
		pop		esi
		retn
		ALIGN 16
	isZero:
		mov		word ptr [ecx], '0'
		lea		eax, [ecx+1]
		retn
	}
}

__declspec(naked) UInt32 __fastcall HexToUInt(const char *str)
{
	__asm
	{
		push	esi
		call	StrLen
		test	eax, eax
		jz		done
		lea		esi, [ecx+eax]
		mov		ch, al
		xor		eax, eax
		xor		cl, cl
	hexToInt:
		dec		esi
		movsx	edx, byte ptr [esi]
		sub		dl, '0'
		js		done
		cmp		dl, 9
		jle		doAdd
		or		dl, 0x20
		cmp		dl, '1'
		jl		done
		cmp		dl, '6'
		jg		done
		sub		dl, 0x27
	doAdd:
		shl		edx, cl
		add		eax, edx
		add		cl, 4
		dec		ch
		jnz		hexToInt
	done:
		pop		esi
		retn
	}
}

__declspec(noinline) UInt8 *AuxBuffer::Get(UInt32 bufIdx, UInt32 reqSize)
{
	thread_local AuxBuffer s_auxBuffers[3];
	AuxBuffer *auxBuf = &s_auxBuffers[bufIdx];
	if (auxBuf->size < reqSize)
	{
		auxBuf->size = reqSize;
		if (auxBuf->ptr)
			_aligned_free(auxBuf->ptr);
		auxBuf->ptr = (UInt8*)_aligned_malloc(reqSize, 0x10);
	}
	else if (!auxBuf->ptr)
		auxBuf->ptr = (UInt8*)_aligned_malloc(auxBuf->size, 0x10);
	return auxBuf->ptr;
}

DString::DString(const char *from)
{
	length = StrLen(from);
	if (length)
	{
		alloc = AlignNumAlloc<char>(length + 1);
		str = (char*)Pool_Alloc(alloc);
		memcpy(str, from, length + 1);
	}
	else
	{
		str = NULL;
		alloc = 0;
	}
}

DString::DString(const DString &from)
{
	length = from.length;
	if (length)
	{
		alloc = AlignNumAlloc<char>(length + 1);
		str = (char*)Pool_Alloc(alloc);
		memcpy(str, from.str, length + 1);
	}
	else
	{
		str = NULL;
		alloc = 0;
	}
}

DString::DString(UInt16 _alloc) : length(0)
{
	if (_alloc)
	{
		alloc = AlignNumAlloc<char>(_alloc + 1);
		str = (char*)Pool_Alloc(alloc);
		*str = 0;
	}
	else
	{
		str = NULL;
		alloc = 0;
	}
}

void DString::Reserve(UInt16 size)
{
	if (alloc > size) return;
	UInt16 newAlloc = AlignNumAlloc<char>(size + 1);
	char *newStr = (char*)Pool_Alloc(newAlloc);
	if (str)
	{
		if (length) memcpy(newStr, str, length);
		Pool_Free(str, alloc);
	}
	str = newStr;
	str[length] = 0;
	alloc = newAlloc;
}

DString& DString::operator=(const char *other)
{
	if (str != other)
	{
		length = StrLen(other);
		if (length)
		{
			if (alloc <= length)
			{
				if (str) Pool_Free(str, alloc);
				alloc = AlignNumAlloc<char>(length + 1);
				str = (char*)Pool_Alloc(alloc);
			}
			memcpy(str, other, length + 1);
		}
		else if (str)
			*str = 0;
	}
	return *this;
}

DString& DString::operator=(const DString &other)
{
	if (this != &other)
	{
		length = other.length;
		if (length)
		{
			if (alloc <= length)
			{
				if (str) Pool_Free(str, alloc);
				alloc = AlignNumAlloc<char>(length + 1);
				str = (char*)Pool_Alloc(alloc);
			}
			memcpy(str, other.str, length + 1);
		}
		else if (str)
			*str = 0;
	}
	return *this;
}

DString& DString::operator+=(char chr)
{
	Reserve(length + 1);
	*(UInt16*)(str + length) = chr;
	length++;
	return *this;
}

DString& DString::operator+=(const char *other)
{
	UInt16 otherLen = StrLen(other);
	if (otherLen)
	{
		UInt16 newLen = length + otherLen;
		Reserve(newLen);
		memcpy(str + length, other, otherLen + 1);
		length = newLen;
	}
	return *this;
}

DString& DString::operator+=(const DString &other)
{
	if (other.length)
	{
		UInt16 newLen = length + other.length;
		Reserve(newLen);
		memcpy(str + length, other.str, other.length + 1);
		length = newLen;
	}
	return *this;
}

bool DString::operator==(const char *other)
{
	return !strcmp(str, other);
}

bool DString::operator==(const DString &other)
{
	return !strcmp(str, other.str);
}

DString& DString::Insert(UInt16 index, char chr)
{
	if (index >= length)
		return this->operator+=(chr);
	Reserve(length + 1);
	memmove(str + index + 1, str + index, length - index + 1);
	str[index] = chr;
	length++;
	return *this;
}

DString& DString::Insert(UInt16 index, const char *other)
{
	if (index >= length)
		return this->operator+=(other);
	UInt16 otherLen = StrLen(other);
	if (otherLen)
	{
		UInt16 newLen = length + otherLen;
		Reserve(newLen);
		memmove(str + index + otherLen, str + index, length - index + 1);
		memcpy(str + index, other, otherLen);
		length = newLen;
	}
	return *this;
}

DString& DString::Insert(UInt16 index, const DString &other)
{
	if (index >= length)
		return this->operator+=(other);
	if (other.length)
	{
		UInt16 newLen = length + other.length;
		Reserve(newLen);
		memmove(str + index + other.length, str + index, length - index + 1);
		memcpy(str + index, other.str, other.length);
		length = newLen;
	}
	return *this;
}

DString& DString::Erase(UInt16 index, UInt16 count)
{
	if (index < length)
	{
		UInt16 endIdx = index + count;
		if (endIdx < length)
		{
			memmove(str + index, str + endIdx, length - endIdx + 1);
			length -= count;
		}
		else
		{
			str[index] = 0;
			length = index;
		}
	}
	return *this;
}

DString& DString::Replace(UInt16 bgnIdx, const char *other)
{
	if (bgnIdx >= length)
		return this->operator+=(other);
	UInt16 otLen = StrLen(other);
	if (otLen)
	{
		UInt16 endIdx = bgnIdx + otLen;
		if (endIdx > length)
		{
			Reserve(endIdx);
			length = endIdx;
		}
		memcpy(str + bgnIdx, other, otLen);
	}
	else length = bgnIdx;
	str[length] = 0;
	return *this;
}

DString& DString::Replace(UInt16 bgnIdx, const DString &other)
{
	if (bgnIdx >= length)
		return this->operator+=(other);
	if (other.length)
	{
		UInt16 endIdx = bgnIdx + other.length;
		if (endIdx > length)
		{
			Reserve(endIdx);
			length = endIdx;
		}
		memcpy(str + bgnIdx, other.str, other.length);
	}
	else length = bgnIdx;
	str[length] = 0;
	return *this;
}

DString DString::SubString(UInt16 bgnIdx, UInt16 endIdx)
{
	char *resStr = NULL;
	UInt16 resLen = 0, resAlloc = 0;
	if (bgnIdx < length)
	{
		if (endIdx > length)
			endIdx = length;
		resLen = endIdx - bgnIdx;
		if (resLen)
		{
			resAlloc = AlignNumAlloc<char>(resLen + 1);
			resStr = (char*)Pool_Alloc(resAlloc);
			memcpy(resStr, str + bgnIdx, resLen);
			resStr[resLen] = 0;
		}
	}
	return DString(resStr, resLen, resAlloc);
}

DString DString::ToLower()
{
	if (!length) return DString();
	UInt16 resAlloc = AlignNumAlloc<char>(length + 1);
	char *resStr = (char*)Pool_Alloc(resAlloc);
	memcpy(resStr, str, length + 1);
	StrToLower(resStr);
	return DString(resStr, length, resAlloc);
}

DString DString::ToUpper()
{
	if (!length) return DString();
	UInt16 resAlloc = AlignNumAlloc<char>(length + 1);
	char *resStr = (char*)Pool_Alloc(resAlloc);
	memcpy(resStr, str, length + 1);
	StrToUpper(resStr);
	return DString(resStr, length, resAlloc);
}

DString operator+(const DString &lStr, char rChr)
{
	UInt16 resLen = lStr.length + 1, resAlloc = AlignNumAlloc<char>(resLen + 1);
	char *resStr = (char*)Pool_Alloc(resAlloc);
	if (lStr.length) memcpy(resStr, lStr.str, lStr.length);
	*(UInt16*)(resStr + lStr.length) = rChr;
	return DString(resStr, resLen, resAlloc);
}

DString operator+(const DString &lStr, const char *rStr)
{
	char *resStr = NULL;
	UInt16 rLen = StrLen(rStr), resLen = lStr.length + rLen, resAlloc = 0;
	if (resLen)
	{
		resAlloc = AlignNumAlloc<char>(resLen + 1);
		resStr = (char*)Pool_Alloc(resAlloc);
		if (lStr.length) memcpy(resStr, lStr.str, lStr.length);
		if (rLen) memcpy(resStr + lStr.length, rStr, rLen);
		resStr[resLen] = 0;
	}
	return DString(resStr, resLen, resAlloc);
}

DString operator+(const char *lStr, const DString &rStr)
{
	char *resStr = NULL;
	UInt16 lLen = StrLen(lStr), resLen = lLen + rStr.length, resAlloc = 0;
	if (resLen)
	{
		resAlloc = AlignNumAlloc<char>(resLen + 1);
		resStr = (char*)Pool_Alloc(resAlloc);
		if (lLen) memcpy(resStr, lStr, lLen);
		if (rStr.length) memcpy(resStr + lLen, rStr.str, rStr.length);
		resStr[resLen] = 0;
	}
	return DString(resStr, resLen, resAlloc);
}

bool __fastcall FileExists(const char *filePath)
{
	UInt32 attr = GetFileAttributes(filePath);
	return (attr != INVALID_FILE_ATTRIBUTES) && !(attr & FILE_ATTRIBUTE_DIRECTORY);
}

FileStream::FileStream(const char *filePath)
{
	theFile = fopen(filePath, "rb");
}

FileStream::FileStream(const char *filePath, UInt32 inOffset)
{
	theFile = fopen(filePath, "rb");
	if (theFile)
	{
		fseek(theFile, 0, SEEK_END);
		if (ftell(theFile) < inOffset)
			Close();
		else fseek(theFile, inOffset, SEEK_SET);
	}
}

bool FileStream::Open(const char *filePath)
{
	if (theFile) fclose(theFile);
	theFile = fopen(filePath, "rb");
	return theFile != NULL;
}

bool FileStream::OpenAt(const char *filePath, UInt32 inOffset)
{
	if (theFile) fclose(theFile);
	theFile = fopen(filePath, "rb");
	if (!theFile) return false;
	fseek(theFile, 0, SEEK_END);
	if (ftell(theFile) < inOffset)
	{
		Close();
		return false;
	}
	fseek(theFile, inOffset, SEEK_SET);
	return true;
}

bool FileStream::OpenWrite(char *filePath, bool append)
{
	if (theFile) fclose(theFile);
	if (FileExists(filePath))
	{
		if (append)
		{
			theFile = fopen(filePath, "ab");
			if (!theFile) return false;
			fputc('\n', theFile);
			//fflush(theFile);
			return true;
		}
	}
	else MakeAllDirs(filePath);
	theFile = fopen(filePath, "wb");
	return theFile != NULL;
}

UInt32 FileStream::GetLength()
{
	fseek(theFile, 0, SEEK_END);
	UInt32 result = ftell(theFile);
	rewind(theFile);
	return result;
}

void FileStream::SetOffset(UInt32 inOffset)
{
	fseek(theFile, 0, SEEK_END);
	if (ftell(theFile) > inOffset)
		fseek(theFile, inOffset, SEEK_SET);
}

char FileStream::ReadChar()
{
	return (char)fgetc(theFile);
}

void FileStream::ReadBuf(void *outData, UInt32 inLength)
{
	fread(outData, inLength, 1, theFile);
}

void FileStream::WriteChar(char chr)
{
	fputc(chr, theFile);
	//fflush(theFile);
}

void FileStream::WriteStr(const char *inStr)
{
	fputs(inStr, theFile);
	//fflush(theFile);
}

void FileStream::WriteBuf(const void *inData, UInt32 inLength)
{
	fwrite(inData, inLength, 1, theFile);
	//fflush(theFile);
}

int FileStream::WriteFmtStr(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int iWritten = vfprintf(theFile, fmt, args);
	va_end(args);
	//fflush(theFile);
	return iWritten;
}

void FileStream::MakeAllDirs(char *fullPath)
{
	char *traverse = fullPath, curr;
	while (curr = *traverse)
	{
		if ((curr == '\\') || (curr == '/'))
		{
			*traverse = 0;
			CreateDirectory(fullPath, NULL);
			*traverse = '\\';
		}
		traverse++;
	}
}

bool DebugLog::Create(const char *filePath)
{
	theFile = _fsopen(filePath, "wb", 0x20);
	return theFile != NULL;
}

const char kIndentLevelStr[] = "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

void DebugLog::Message(const char *msgStr)
{
	if (!theFile) return;
	if (indent < 40)
		fputs(kIndentLevelStr + indent, theFile);
	fputs(msgStr, theFile);
	fputc('\n', theFile);
	fflush(theFile);
}

void DebugLog::FmtMessage(const char *fmt, va_list args)
{
	if (!theFile) return;
	if (indent < 40)
		fputs(kIndentLevelStr + indent, theFile);
	vfprintf(theFile, fmt, args);
	fputc('\n', theFile);
	fflush(theFile);
}

DebugLog s_log, s_debug;

void PrintLog(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	s_log.FmtMessage(fmt, args);
	va_end(args);
}

void PrintDebug(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	s_debug.FmtMessage(fmt, args);
	va_end(args);
}

__declspec(naked) LineIterator::LineIterator(const char *filePath, char *buffer)
{
	__asm
	{
		push	ebx
		mov		ebx, ecx
		mov		edx, [esp+0xC]
		mov		[ebx], edx
		push	'br'
		push	esp
		push	dword ptr [esp+0x10]
		call	fopen
		add		esp, 0xC
		test	eax, eax
		jz		openFail
		push	esi
		push	edi
		push	SEEK_END
		push	0
		push	eax
		call	fseek
		call	ftell
		mov		edi, eax
		call	rewind
		push	1
		push	edi
		push	dword ptr [ebx]
		call	fread
		add		esp, 0xC
		call	fclose
		add		esp, 0xC
		mov		esi, [ebx]
		mov		word ptr [esi+edi], 0x300
		dec		esi
		ALIGN 16
	iterHead:
		dec		edi
		js		iterEnd
		inc		esi
		mov		al, [esi]
		cmp		al, '\r'
		ja		iterHead
		jz		nullTerm
		cmp		al, '\n'
		jnz		iterHead
	nullTerm:
		mov		[esi], 0
		jmp		iterHead
		NOP_0x9
	iterEnd:
		mov		esi, [ebx]
	findBgn:
		cmp		[esi], 0
		jnz		done
		inc		esi
		jmp		findBgn
		ALIGN 16
	done:
		mov		[ebx], esi
		pop		edi
		pop		esi
		pop		ebx
		retn	8
		ALIGN 16
	openFail:
		mov		edx, [ebx]
		mov		[edx], 3
		pop		ebx
		retn	8
	}
}

UInt32 __fastcall FileToBuffer(const char *filePath, char *buffer)
{
	FileStream srcFile(filePath);
	if (!srcFile) return 0;
	UInt32 length = srcFile.GetLength();
	if (length)
	{
		if (length > kMaxMessageLength)
			length = kMaxMessageLength;
		srcFile.ReadBuf(buffer, length);
		buffer[length] = 0;
	}
	return length;
}

__declspec(naked) void __stdcall SafeWrite8(UInt32 addr, UInt32 data)
{
	__asm
	{
#if LOG_HOOKS
		push	1
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	4
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		mov		eax, [esp+8]
		mov		edx, [esp+0xC]
		mov		[eax], dl
		mov		edx, [esp]
		push	esp
		push	edx
		push	4
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	8
	}
}

__declspec(naked) void __stdcall SafeWrite16(UInt32 addr, UInt32 data)
{
	__asm
	{
#if LOG_HOOKS
		push	2
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	4
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		mov		eax, [esp+8]
		mov		edx, [esp+0xC]
		mov		[eax], dx
		mov		edx, [esp]
		push	esp
		push	edx
		push	4
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	8
	}
}

__declspec(naked) void __stdcall SafeWrite32(UInt32 addr, UInt32 data)
{
	__asm
	{
#if LOG_HOOKS
		push	4
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	4
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		mov		eax, [esp+8]
		mov		edx, [esp+0xC]
		mov		[eax], edx
		mov		edx, [esp]
		push	esp
		push	edx
		push	4
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	8
	}
}

__declspec(naked) void __stdcall SafeWriteBuf(UInt32 addr, void *data, UInt32 len)
{
	__asm
	{
#if LOG_HOOKS
		push	dword ptr [esp+0xC]
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	dword ptr [esp+0x18]
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		push	dword ptr [esp+0x10]
		push	dword ptr [esp+0x10]
		push	dword ptr [esp+0x10]
		call	MemCopy
		add		esp, 0xC
		mov		edx, [esp]
		push	esp
		push	edx
		push	dword ptr [esp+0x18]
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	0xC
	}
}

__declspec(naked) void __stdcall WriteRelJump(UInt32 jumpSrc, UInt32 jumpTgt)
{
	__asm
	{
#if LOG_HOOKS
		push	5
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	5
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		mov		eax, [esp+8]
		mov		edx, [esp+0xC]
		sub		edx, eax
		sub		edx, 5
		mov		byte ptr [eax], 0xE9
		mov		[eax+1], edx
		mov		edx, [esp]
		push	esp
		push	edx
		push	5
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	8
	}
}

__declspec(naked) void __stdcall WriteRelCall(UInt32 jumpSrc, UInt32 jumpTgt)
{
	__asm
	{
#if LOG_HOOKS
		push	5
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	5
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		mov		eax, [esp+8]
		mov		edx, [esp+0xC]
		sub		edx, eax
		sub		edx, 5
		mov		byte ptr [eax], 0xE8
		mov		[eax+1], edx
		mov		edx, [esp]
		push	esp
		push	edx
		push	5
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	8
	}
}

__declspec(naked) void __stdcall WritePushRetRelJump(UInt32 baseAddr, UInt32 retAddr, UInt32 jumpTgt)
{
	__asm
	{
#if LOG_HOOKS
		push	0xA
		push	dword ptr [esp+8]
		call	StoreOriginalData
#endif
		push	ecx
		push	esp
		push	PAGE_EXECUTE_READWRITE
		push	0xA
		push	dword ptr [esp+0x14]
		call	VirtualProtect
		mov		eax, [esp+8]
		mov		edx, [esp+0xC]
		mov		byte ptr [eax], 0x68
		mov		[eax+1], edx
		mov		edx, [esp+0x10]
		sub		edx, eax
		sub		edx, 0xA
		mov		byte ptr [eax+5], 0xE9
		mov		[eax+6], edx
		mov		edx, [esp]
		push	esp
		push	edx
		push	0xA
		push	eax
		call	VirtualProtect
		pop		ecx
		retn	0xC
	}
}

void __fastcall GetTimeStamp(char *buffer)
{
	time_t rawTime = time(NULL);
	tm timeInfo;
	localtime_s(&timeInfo, &rawTime);
	sprintf_s(buffer, 0x10, "%02d-%02d-%02d", timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
}

UInt64 GetTimeMs64()
{
	FILETIME ft;
	LARGE_INTEGER li;
	GetSystemTimeAsFileTime(&ft);
	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	UInt64 ret = li.QuadPart;
	ret -= 116444736000000000LL;
	ret /= 10000;
	return ret;
}

struct ControlName
{
	UInt32		unk00;
	const char	*name;
	UInt32		unk0C;
};

Setting **g_keyNames = (Setting**)0x11D52F0;
Setting **g_mouseButtonNames = (Setting**)0x11D5240;
Setting **g_joystickNames = (Setting**)0x11D51B0;

const char* __fastcall GetDXDescription(UInt32 keyID)
{
	if (keyID <= 220)
	{
		if (g_keyNames[keyID])
			return g_keyNames[keyID]->data.str;
	}
	else if (keyID <= 255);
	else if (keyID <= 263)
	{
		if (g_mouseButtonNames[keyID - 256])
			return g_mouseButtonNames[keyID - 256]->data.str;
	}
	else if (keyID == 264)
		return "WheelUp";
	else if (keyID == 265)
		return "WheelDown";

	return "<no key>";
}

__declspec(naked) UInt32 __fastcall ByteSwap(UInt32 dword)
{
	__asm
	{
		mov		eax, ecx
		bswap	eax
		retn
	}
}

void DumpMemImg(void *data, UInt32 size, UInt8 extra)
{
	UInt32 *ptr = (UInt32*)data;
	//Console_Print("Output");
	PrintDebug("\nDumping  %08X\n", ptr);
	for (UInt32 iter = 0; iter < size; iter += 4, ptr++)
	{
		if (!extra) PrintDebug("%03X\t\t%08X\t", iter, *ptr);
		else if (extra == 1) PrintDebug("%03X\t\t%08X\t[%08X]\t", iter, *ptr, ByteSwap(*ptr));
		else if (extra == 2) PrintDebug("%04X\t\t%08X\t%f", iter, *ptr, *(float*)ptr);
		else if (extra == 3) PrintDebug("%03X\t\t%08X\t[%08X]\t%f", iter, *ptr, ByteSwap(*ptr), *(float*)ptr);
	}
}
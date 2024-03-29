/*  wcecompat: Windows CE C Runtime Library "compatibility" library.
 *
 *  Copyright (C) 2001-2002 Essemer Pty Ltd.  All rights reserved.
 *  http://www.essemer.com.au/
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <process.h>
#include <windows.h>

uintptr_t __cdecl _beginthread(void( *start_address )( void * ),
   unsigned stack_size, void *arglist )
{
	DWORD thrdaddr;
	return reinterpret_cast<uintptr_t>(CreateThread(
      NULL,
      stack_size,
      reinterpret_cast<DWORD (*)(void*)>(start_address),
      arglist,
      0,
      reinterpret_cast<DWORD*>(&thrdaddr)));
}

uintptr_t _beginthreadex( 
   void *security,
   unsigned stack_size,
   unsigned ( *start_address )( void * ),
   void *arglist,
   unsigned initflag,
   unsigned *thrdaddr)
{
	return reinterpret_cast<uintptr_t>(CreateThread(
      reinterpret_cast<SECURITY_ATTRIBUTES*>(security),
      stack_size,
      reinterpret_cast<DWORD (*)(void*)>(start_address),
      arglist,
      initflag,
      reinterpret_cast<DWORD*>(thrdaddr)));
}

void __cdecl _endthread(void)
{
	ExitThread(-1);
}

void __cdecl _endthreadex(unsigned retval)
{
	ExitThread(retval);
}

int __cdecl _getpid(void)
{
	return (int)GetCurrentProcessId();
}

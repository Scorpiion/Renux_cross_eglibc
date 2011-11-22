/* Get file-specific information about descriptor FD.  Linux version.
   Copyright (C) 1991,1995,1996,1998-2003,2008,2010
   Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <fcntl.h>
#include "pathconf.h"

static long int posix_fpathconf (int fd, int name);

/* Define this first, so it can be inlined.  */
#define __fpathconf static posix_fpathconf
#include <sysdeps/posix/fpathconf.c>


/* Get file-specific information about descriptor FD.  */
long int
__fpathconf (fd, name)
     int fd;
     int name;
{
  struct statfs fsbuf;
  int r;

  switch (name)
    {
    case _PC_LINK_MAX:
      return __statfs_link_max (__fstatfs (fd, &fsbuf), &fsbuf);

    case _PC_FILESIZEBITS:
      return __statfs_filesize_max (__fstatfs (fd, &fsbuf), &fsbuf);

    case _PC_2_SYMLINKS:
      return __statfs_symlinks (__fstatfs (fd, &fsbuf), &fsbuf);

    case _PC_CHOWN_RESTRICTED:
      return __statfs_chown_restricted (__fstatfs (fd, &fsbuf), &fsbuf);

    case _PC_PIPE_BUF:
      r = __fcntl (fd, F_GETPIPE_SZ);
      if (r > 0)
	return r;
      /* FALLTHROUGH */

    default:
      return posix_fpathconf (fd, name);
    }
}

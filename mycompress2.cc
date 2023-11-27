/*
 * little wrapper to glue C and C++ together...
 *
 * Christian Leber <christian@leber.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#define TRUE 1
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <zlib.h>
#include <endian.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/mman.h>

#include "mksquashfs.h"
#include <squashfs_fs.h>


#include "portable.h"
#include "pngex.h"
#include "compress.h"
#include "siglock.h"
#include <netinet/in.h>
   
#include "lib/mng.h"
#include "lib/endianrw.h"
 
#include <iostream>
#include <iomanip> 
   
#include <cstdio>


extern "C" unsigned int mycompress2(unsigned char *d, unsigned char *s, int size, int block_size, int data_block)
{
	unsigned c_byte = block_size << 1;
	unsigned int res;

	//if(!uncompressed && (res = compress2(d, &c_byte, s, size, 9)) != Z_OK) {
	res = compress_zlib(shrink_extreme, d, c_byte, s, size);
	if(res!=1)
	{
//		if(res == Z_MEM_ERROR)
//			BAD_ERROR("zlib::compress failed, not enough room in output buffer\n");
//		FIXME
		printf("ERROR");
		exit(0);
	}

	return (unsigned int) c_byte;
}


/*******************************************************************************
** Copyright (c) 2007 Krell Institute. All Rights Reserved.
**
** This library is free software; you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by the Free
** Software Foundation; either version 2.1 of the License, or (at your option)
** any later version.
**
** This library is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation, Inc.,
** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*******************************************************************************/

/** @file
 *
 * Definition of the openss_send() function for offline collectors.
 *
 */

#include <rpc/rpc.h>

#include <stdio.h>

extern char *OpenSS_rawdata;

/**
 * Write blob data.
 *
 * Writes blob data to the file named by OpenSS_rawdata.
 * Any header generation and data encoding is
 * performed by OpenSS_Send() or OpenSS_SendRecord().
 * Here the data is treated purely as a buffer of
 * bytes to be written.
 *
 * @param size    Size of the data to be sent (in bytes).
 * @param data    Pointer to the data to be written.
 * @return        Integer "1" if succeeded or "0" if failed.
 */
int
openss_send(const unsigned size, const void* data)
{
     /* TODO: need to add error checking to the file writing code */
#ifndef NDEBUG
    if ( (getenv("OPENSS_DEBUG_OFFLINE") != NULL)) {
	fprintf(stderr,"OFFLINE openss_send: size=%d, data=%p, file=%s\n",
           size, data,OpenSS_rawdata);
    }
#endif

    fflush(stderr);

    FILE *outfile = fopen(OpenSS_rawdata, "a");
    size_t res = fwrite(data, sizeof(char), size, outfile);
    fclose(outfile);
    return 1;
}

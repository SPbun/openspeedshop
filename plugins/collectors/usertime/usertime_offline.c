/*******************************************************************************
** Copyright (c) The Krell Institute (2007). All Rights Reserved.
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
 * Declaration and definition of the UserTime sampling collector's runtime
 * (offline support).
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "RuntimeAPI.h"
#include "blobs.h"
#include "usertime_offline.h"
#include "OpenSS_FileIO.h"
#include <values.h>

#if __WORDSIZE == 64
#define OSS_TIME_END __LONG_MAX__ * 2UL + 1;
#else
#define OSS_TIME_END __LONG_LONG_MAX__ * 2ULL + 1;
#endif

void offline_start_sampling(const char* arguments)
{
    /* TODO: handle experiment parameters */
#if 0
    usertime_start_sampling_args args;
    memset(&args, 0, sizeof(args));
    args.collector=1;
    args.sampling_rate=100000;
    args.thread=getpid();
    /* how to handle
       Blob arguments(reinterpret_cast<xdrproc_t>(xdr_usertime_start_sampling_args), &args);
    */
#endif

    OpenSS_CreateFilePrefix("usertime");
    OpenSS_CreateOutfile("openss-dsos");
    int retval = OpenSS_GetDLInfo(getpid(), NULL);

    usertime_start_sampling(arguments);
}

void offline_stop_sampling(const char* arguments)
{
    /* call the collector specific stop sampling funcion. This writes any data */
    /* blobs to the specific openss-raw file (exp-collector-pid-tid.openss-raw). */
    usertime_stop_sampling(arguments);

}

void offline_record_dso(const char* dsoname, uint64_t begin, uint64_t end, uint8_t is_dlopen)
{
    /* Create an OpenSS_Data header for this object. */
    /* These values must match values used for data headers. */
    /* Initialize the dso blob's header */
    /* Passing &(tls.header) to OpenSS_InitializeDataHeader */
    /* was not safe on ia64 systems.  */
    OpenSS_DataHeader local_dso_header;
    OpenSS_InitializeDataHeader(/*experiment*/ 0,
				/*collector*/ 1,
				&(local_dso_header));
    memcpy(&tlsobj.header, &local_dso_header, sizeof(OpenSS_DataHeader));

    tlsobj.header.time_begin = OpenSS_GetTime();
    if (is_dlopen) {
	tlsobj.header.time_end = OSS_TIME_END;
    } else {
	tlsobj.header.time_end = OpenSS_GetTime();
    }

    /* create an OpenSS_Obj blob for the dso named dsoname. */
    /* record the full path and the address range as found */
    /* in the /proc/<pid>/maps file */
    tlsobj.objs.objname=strdup(dsoname);
    tlsobj.objs.addr_begin=begin;
    tlsobj.objs.addr_end=end;


#ifndef NDEBUG
    if (getenv("OPENSS_DEBUG_COLLECTOR") != NULL) {
	fprintf(stderr,"offline_record_dso: record %s to %s\n",
		dsoname,OpenSS_outfile);
    }
#endif

    OpenSS_CreateFilePrefix("usertime");
    OpenSS_CreateOutfile("openss-dsos");
    OpenSS_Send(&(tlsobj.header),
		(xdrproc_t)xdr_openss_objects,
		&(tlsobj.objs));
}

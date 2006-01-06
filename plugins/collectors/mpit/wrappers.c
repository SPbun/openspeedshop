/*******************************************************************************
** Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
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
 * MPI function wrappers for the MPI extended event tracing collector.
 *
 */

#include "RuntimeAPI.h"
#include "runtime.h"

#include <mpi.h>



/*
 * MPI_Irecv
 */

int mpit_PMPI_Irecv(void* buf, int count, MPI_Datatype datatype, int source, 
		    int tag, MPI_Comm comm, MPI_Request* request)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();
    retval = PMPI_Irecv(buf, count, datatype, source, tag, comm, request);
    event.stop_time = OpenSS_GetTime();
    event.source = source;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Irecv));
    return retval;
}

/*
 * MPI_Recv
 */
int mpit_PMPI_MPI_Recv(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int source, 
    int tag, 
    MPI_Comm comm, 
    MPI_Status *status)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_MPI_Recv(buf, count, datatype, source,  tag, comm, status);

    event.stop_time = OpenSS_GetTime();
    event.source = source;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_MPI_Recv));

    return retval;
}
  
/*
 * MPI_Iprobe
 */
int mpit_PMPI_Iprobe(
    int source, 
    int tag, 
    MPI_Comm comm, 
    int *flag, 
    MPI_Status *status)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Iprobe(source, tag, comm, flag, status);

    event.stop_time = OpenSS_GetTime();
    event.source = source;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    event.tag = tag;
    event.communicator = comm;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Iprobe));

    return retval;
}
  
/*
 * MPI_probe
 */
int mpit_PMPI_probe(
    int source, 
    int tag, 
    MPI_Comm comm, 
    MPI_Status *status)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_probe(source, tag, comm, status);

    event.stop_time = OpenSS_GetTime();
    event.source = source;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    event.tag = tag;
    event.communicator = comm;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_probe));

    return retval;
}
  


/*
 * MPI_Isend
 */

int mpit_PMPI_Isend(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest,
    int tag, 
    MPI_Comm comm, 
    MPI_Request* request)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Isend(buf, count, datatype, dest, tag, comm, request);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    event.destination = dest;
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Isend));

    return retval;
}

/*
 * MPI_Bsend
 */
int mpit_PMPI_Bsend(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Bsend(buf, count, datatype, dest, tag, comm);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Bsend));

    return retval;
}
  
/*
 * MPI_Ibsend
 */
int mpit_PMPI_Ibsend(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm, 
    MPI_Request *request)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Ibsend(buf, count, datatype, dest, tag, comm, request);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Ibsend));

    return retval;
}
  
/*
 * MPI_Irsend
 */
int mpit_PMPI_Irsend(    
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm, 
    MPI_Request *request)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Irsend(buf, count, datatype, dest, tag, comm, request);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Irsend));

    return retval;
}
    
/*
 * MPI_Issend
 */
int mpit_PMPI_Issend(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm, 
    MPI_Request *request)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Issend(buf, count, datatype, dest, tag, comm, request);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Issend));

    return retval;
}
  
/*
 * MPI_Rsend
 */
int mpit_PMPI_Rsend(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Rsend(buf, count, datatype, dest, tag, comm);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Rsend));

    return retval;
}
  
/*
 * MPI_Send
 */
int mpit_PMPI_Send(
    void* buf, 
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Send(buf, count, datatype, dest, tag, comm);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Send));

    return retval;
}
  
/*
 * MPI_Ssend
 */
int mpit_PMPI_Ssend(
    void* buf,
    int count, 
    MPI_Datatype datatype, 
    int dest, 
    int tag, 
    MPI_Comm comm)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Ssend(buf, count, datatype, dest, tag, comm);

    event.stop_time = OpenSS_GetTime();
    event.destination = dest;
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.source));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.tag = tag;
    event.communicator = comm;
    event.datatype = datatype;

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Ssend));

    return retval;
}
  
/*
 * MPI_Waitall
 */
int mpit_PMPI_Waitall(
    int count, 
    MPI_Request *array_of_requests, 
    MPI_Status *status)
{
    int retval, datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Waitall(count, array_of_requests, status);

    event.stop_time = OpenSS_GetTime();
    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));

    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Waitall));

    return retval;
}

/*
 * MPI_Finalize
 */

int mpit_PMPI_Finalize()
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Finalize();

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Finalize));

    return retval;
}

/*
 * MPI_Waitsome
 
    What do I do with out and in count?
    
 */

int mpit_PMPI_Waitsome(
    int incount, 
    MPI_Request *array_of_requests, 
    int *outcount, 
    int *array_of_indices, 
    MPI_Status *array_of_statuses
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Waitsome( incount, array_of_requests, 
    	    	    	    outcount, array_of_indices, 
			    array_of_statuses);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Waitsome));

    return retval;
}

/*
 * MPI_Testsome
 
    What do I do with out and in count?
    
 */

int mpit_PMPI_Testsome(
    int incount, 
    MPI_Request *array_of_requests, 
    int *outcount, 
    int *array_of_indices, 
    MPI_Status *array_of_statuses
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Testsome( incount, array_of_requests, 
    	    	    	    outcount, array_of_indices, 
			    array_of_statuses);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Testsome));

    return retval;
}

/*
 * MPI_Waitany
 */

int mpit_PMPI_Waitany(
    int count,   
    MPI_Request *array_of_requests, 
    int *index, 
    MPI_Status *status
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Waitany(count,  array_of_requests, index, status);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Waitany));

    return retval;
}

/*
 * MPI_Unpack
 
    Which size do I use, insize or outsize?
    I'm going to use outsize.
 */

int mpit_PMPI_Unpack(
    void* inbuf, 
    int insize, 
    int *position, 
    void *outbuf, 
    int outcount, 
    MPI_Datatype datatype, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Unpack(inbuf, insize, position, outbuf, 
    	    	    	 outcount, datatype, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = outcount * datatype_size;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Unpack));

    return retval;
}

/*
 * MPI_Wait
 */

int mpit_PMPI_Wait(
    MPI_Request *request, 
    MPI_Status *status
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Wait(request, status);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Wait));

    return retval;
}

/*
 * MPI_Testany
 */

int mpit_PMPI_Testany(
    int count,
    MPI_Request *array_of_requests,
    int *index,
    int *flag,
    MPI_Status *status
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Testany(count,array_of_requests, index, flag, status);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Testany));

    return retval;
}

/*
 * MPI_Testall
 */

int mpit_PMPI_Testall(
    int count,
    MPI_Request *array_of_requests, 
    int *flag, 
    MPI_Status *status
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Testall(count, array_of_requests, flag, status);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Testall));

    return retval;
}

/*
 * MPI_Test
 */

int mpit_PMPI_Test(
    MPI_Request *request, 
    int *flag, 
    MPI_Status *status
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Test(request, flag, status);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Test));

    return retval;
}

/*
 * MPI_Scan
 */

int mpit_PMPI_Scan(
    void* sendbuf, 
    void* recvbuf, 
    int count, 
    MPI_Datatype datatype, 
    MPI_Op op, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Scan(sendbuf, recvbuf, count, datatype, op, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Scan));

    return retval;
}

/*
 * MPI_Request_free
 */

int mpit_PMPI_Request_free(
    MPI_Request *request
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Request_free(request);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Request_free));

    return retval;
}

/*
 * MPI_Reduce_scatter
 
    This is questionable with recvcounts.
    
 */

int mpit_PMPI_Reduce_scatter(
    void* sendbuf, 
    void* recvbuf, 
    int *recvcounts, 
    MPI_Datatype datatype, 
    MPI_Op op, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Reduce_scatter(sendbuf, recvbuf, recvcounts,  datatype, op, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = *recvcounts * datatype_size;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Reduce_scatter));

    return retval;
}

/*
 * MPI_Reduce
 */

int mpit_PMPI_Reduce(
    void* sendbuf, 
    void* recvbuf, 
    int count, 
    MPI_Datatype datatype, 
    MPI_Op op, 
    int root, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Reduce));

    return retval;
}

/*
 * MPI_Pack
 */

int mpit_PMPI_Pack(
    void* inbuf, 
    int incount, 
    MPI_Datatype datatype, 
    void *outbuf, 
    int outsize, 
    int *position, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Pack( inbuf, incount, datatype, outbuf, 
    	    	    	outsize, position, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = incount * datatype_size;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Pack));

    return retval;
}

/*
 * MPI_Init
 */

int mpit_PMPI_Init(
    int *argc, 
    char ***argv
    )
{
    int retval;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Init(argc, argv);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Init));

    return retval;
}

/*
 * MPI_Get_count
 */

int mpit_PMPI_Get_count(
    MPI_Status *status, MPI_Datatype datatype, int *count
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Get_count(status, datatype, count);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = *count * datatype_size;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Get_count));

    return retval;
}

/*
 * MPI_Gatherv
 */

int mpit_PMPI_Gatherv(
    void* sendbuf, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void* recvbuf, 
    int *recvcounts, 
    int *displs, 
    MPI_Datatype recvtype, 
    int root, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Gatherv(sendbuf, sendcount, sendtype, recvbuf, 
    	    	    	  recvcounts, displs, recvtype, root, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(recvtype, &datatype_size);
    event.size = *recvcounts * datatype_size;
    event.communicator = comm;
    event.datatype = recvtype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Gatherv));

    return retval;
}

/*
 * MPI_Gather
 */

int mpit_PMPI_Gather(
    void* sendbuf, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void* recvbuf, 
    int recvcount, 
    MPI_Datatype recvtype, 
    int root, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Gather(sendbuf, sendcount, sendtype, 
    	    	    	 recvbuf, recvcount, recvtype, 
			 root, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(recvtype, &datatype_size);
    event.size = recvcount * datatype_size;
    event.communicator = comm;
    event.datatype = recvtype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Gather));

    return retval;
}

/*
 * MPI_Cancel
 */

int mpit_PMPI_Cancel(
    MPI_Request *request
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Cancel(request);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Cancel));

    return retval;
}

/*
 * MPI_Bcast
 */

int mpit_PMPI_Bcast(
    void* buffer, 
    int count, 
    MPI_Datatype datatype, 
    int root, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Bcast(buffer, count, datatype, root, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Bcast));

    return retval;
}

/*
 * MPI_Barrier
 */

int mpit_PMPI_Barrier(
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Barrier(comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    event.communicator = comm;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Barrier));

    return retval;
}

/*
 * MPI_Alltoallv
 */

int mpit_PMPI_Alltoallv(
    void* sendbuf, 
    int *sendcounts, 
    int *sdispls, 
    MPI_Datatype sendtype, 
    void* recvbuf, 
    int *recvcounts, 
    int *rdispls, 
    MPI_Datatype recvtype, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Alltoallv(sendbuf, sendcounts, sdispls, 
    	    	    	    sendtype, recvbuf, recvcounts, 
			    rdispls, recvtype, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(recvtype, &datatype_size);
    event.size = *recvcounts * datatype_size;
    event.communicator = comm;
    event.datatype = recvtype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Alltoallv));

    return retval;
}

/*
 * MPI_Alltoall
 */

int mpit_PMPI_Alltoall(
    void* sendbuf, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void* recvbuf, 
    int recvcount, 
    MPI_Datatype recvtype, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Alltoall( sendbuf, sendcount, sendtype, 
    	    	    	    recvbuf, recvcount, recvtype, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(recvtype, &datatype_size);
    event.size = recvcount * datatype_size;
    event.communicator = comm;
    event.datatype = recvtype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Alltoall));

    return retval;
}

/*
 * MPI_Allreduce
 */

int mpit_PMPI_Allreduce(
    void* sendbuf, 
    void* recvbuf, 
    int count, 
    MPI_Datatype datatype, 
    MPI_Op op, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(datatype, &datatype_size);
    event.size = count * datatype_size;
    event.communicator = comm;
    event.datatype = datatype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Allreduce));

    return retval;
}

/*
 * MPI_Allgatherv
 */

int mpit_PMPI_Allgatherv(
    void* sendbuf, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void* recvbuf, 
    int *recvcounts, 
    int *displs, 
    MPI_Datatype recvtype, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Allgatherv(sendbuf, sendcount, sendtype, 
    	    	    	     recvbuf, recvcounts, displs, 
			     recvtype, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(recvtype, &datatype_size);
    event.size = *recvcounts * datatype_size;
    event.communicator = comm;
    event.datatype = recvtype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Allgatherv));

    return retval;
}

/*
 * MPI_Allgather
 */

int mpit_PMPI_Allgather(
    void* sendbuf, 
    int sendcount, 
    MPI_Datatype sendtype, 
    void* recvbuf, 
    int recvcount, 
    MPI_Datatype recvtype, 
    MPI_Comm comm
    )
{
    int retval;
    int datatype_size;
    mpit_event event;
    
    mpit_start_event(&event);
    event.start_time = OpenSS_GetTime();

    retval = PMPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, 
    	    	    	    recvcount, recvtype, comm);

    event.stop_time = OpenSS_GetTime();

    PMPI_Comm_rank(MPI_COMM_WORLD, &(event.destination));
    PMPI_Type_size(recvtype, &datatype_size);
    event.size = recvcount * datatype_size;
    event.communicator = comm;
    event.datatype = recvtype;
    mpit_record_event(&event, OpenSS_GetAddressOfFunction(PMPI_Allgather));

    return retval;
}


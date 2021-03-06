////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

/** @file
 *
 * Declaration and definition of the Job type.
 *
 */

#ifndef _OpenSpeedShop_Framework_Job_
#define _OpenSpeedShop_Framework_Job_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <utility>
#include <vector>



namespace OpenSpeedShop { namespace Framework {

    /**
     * Job description.
     *
     * List of host/pid pairs describing the processes in a job. No specific
     * relationship is implied by the term "job". This type exists merely as
     * a convenience when passing around a list of host/pid pairs. E.g. when
     * describing the processes in an MPI application.
     *
     * @ingroup Implementation
     */
    typedef std::vector<std::pair<std::string, pid_t> > Job;
    
} }



#endif

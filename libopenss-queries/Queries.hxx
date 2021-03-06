////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
// Copyright (c) 2006-2018 Krell Institute All Rights Reserved.
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
 * Declaration of the Queries namespace.
 *
 */

#ifndef _OpenSpeedShop_Queries_
#define _OpenSpeedShop_Queries_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ToolAPI.hxx"

#include <functional>
#include <map>
#include <string>
#include <vector>



namespace OpenSpeedShop {

    /**
     * Enclosing namespace for the <em>Open|SpeedShop</em> query library.
     *
     * Namespace containing procedural functions for performing higher-level
     * queries on experiments generated by the <em>Open|SpeedShop</em> framework
     * library. There is nothing "magical" about these functions. They use the
     * same API that is available directly to every tool. The intention is
     * simply to promote re-use by providing some of the more commonly used 
     * queries.
     */
    namespace Queries
    {

	Framework::ThreadGroup MakeThreadGroup(const Framework::Thread&);

	/**
	 * Strict weak ordering predicate for linked objects.
	 *
	 * Defines a strict weak ordering predicate for linked objects that
	 * works properly even when the two linked objects are in different
	 * experiment databases. This predicate is slower than the less-than
	 * operator for linked objects, but is useful when comparing across
	 * experiments.
	 */
	struct CompareLinkedObjects :
	    std::binary_function<const Framework::LinkedObject&,
				 const Framework::LinkedObject&,
				 bool>
	{
	    bool operator()(const Framework::LinkedObject&,
			    const Framework::LinkedObject&) const;
	};

	/**
	 * Strict weak ordering predicate for functions.
	 *
	 * Defines a strict weak ordering predicate for functions that works
	 * properly even when the two functions are in different experiment
	 * databases. This predicate is slower than the less-than operator
	 * for functions, but is useful when comparing across experiments.
	 */
	struct CompareFunctions :
	    std::binary_function<const Framework::Function&,
				 const Framework::Function&,
				 bool>
	{
	    bool operator()(const Framework::Function&,
			    const Framework::Function&,
                            bool) const;
	};

	/**
	 * Strict weak ordering predicate for statements.
	 *
	 * Defines a strict weak ordering predicate for statements that works
	 * properly even when the two statements are in different experiment
	 * databases. This predicate is slower than the less-than operator
	 * for statements, but is useful when comparing across experiments.
	 */
	struct CompareStatements :
	    std::binary_function<const Framework::Statement&,
				 const Framework::Statement&,
				 bool>
	{
	    bool operator()(const Framework::Statement&,
			    const Framework::Statement&,
                            bool ) const;
	};

	/**
	 * Strict weak ordering predicate for loops.
	 *
	 * Defines a strict weak ordering predicate for loops that works
	 * properly even when the two loops are in different experiment
	 * databases. This predicate is slower than the less-than operator
	 * for loops, but is useful when comparing across experiments.
	 */
	struct CompareLoops :
	    std::binary_function<const Framework::Loop&,
				 const Framework::Loop&,
				 bool>
	{
	    bool operator()(const Framework::Loop&,
			    const Framework::Loop&,
                            bool ) const;
	};


	/**
	 * Strict weak ordering predicate for vector instructions.
	 *
	 * Defines a strict weak ordering predicate for vector instructions 
         * that works properly even when the two vector instructions are in 
         * different experiment databases. This predicate is slower than the 
         * less-than operator for vector instructions, but is useful when 
         * comparing across experiments.
	 */
	struct CompareVectorInstrs :
	    std::binary_function<const Framework::VectorInstr&,
				 const Framework::VectorInstr&,
				 bool>
	{
	    bool operator()(const Framework::VectorInstr&,
			    const Framework::VectorInstr&,
                            bool ) const;
	};

	template <typename TS, typename TM>
	void GetMetricValues(
	    const Framework::Collector&,
	    const std::string&,
	    const Framework::TimeInterval&,
	    const Framework::ThreadGroup&,
	    const std::set<TS >&,
	    Framework::SmartPtr<
	        std::map<TS, std::map<Framework::Thread, TM > > >&
	    );



	namespace Reduction {

	    template <typename TM>
	    TM Summation(const std::map<Framework::Thread, TM >&);

	    template <typename TM>
	    TM ArithmeticMean(const std::map<Framework::Thread, TM >&);

	    template <typename TM>
	    TM Minimum(const std::map<Framework::Thread, TM >&);

	    template <typename TM>
	    TM Maximum(const std::map<Framework::Thread, TM >&);

	    template <typename TS, typename TM>
	    Framework::SmartPtr<std::map<TS, TM > > Apply(
		const Framework::SmartPtr<
	            std::map<TS, std::map<Framework::Thread, TM > > >&,
		TM (*)(const std::map<Framework::Thread, TM>&)
		);

	    template <typename TS, typename TM>
	    TM GetTotal(const Framework::SmartPtr<std::map<TS, TM > >&);

	    template <typename TS, typename TM>
	    Framework::SmartPtr<
		std::map<TS, std::map<Framework::Thread, TM > > > GetSubset(
		const Framework::SmartPtr<
	            std::map<TS, std::map<Framework::Thread, TM > > >&,
		const Framework::ThreadGroup&
		);

	}



	namespace ClusterAnalysis {

	    template <typename TS, typename TM>
	    TM ManhattanDistance(
		const std::map<TS, std::map<Framework::Thread, TM > >&,
		const Framework::Thread&,
		const Framework::Thread&
		);

	    template <typename TS, typename TM> class DistanceMatrix;
	    	    
	    template <typename TS, typename TM>
	    TM CompleteLinkageDistance(const DistanceMatrix<TS, TM >&,
				       const Framework::ThreadGroup&,
				       const Framework::ThreadGroup&);

	    template <typename TS, typename TM>
	    TM SingleLinkageDistance(const DistanceMatrix<TS, TM >&,
				     const Framework::ThreadGroup&,
				     const Framework::ThreadGroup&);

	    template <typename TS, typename TM>
	    TM AverageLinkageDistance(const DistanceMatrix<TS, TM >&,
				      const Framework::ThreadGroup&,
				      const Framework::ThreadGroup&);
	    
	    /**
	     * Clustering termination predicate (numerical #1).
	     *
	     * Defines a cluster termination predicate that terminates the
	     * formation of clusters when the number of clusters reaches a
	     * constant value (specified at object construction).
	     *
	     * @sa    http://en.wikipedia.org/wiki/Cluster_analysis#
	     *        Agglomerative_hierarchical_clustering
	     */
	    template <typename TS, typename TM>
	    struct NumberCriterion1 {

		bool operator()(const DistanceMatrix<TS, TM >&,
				const std::set<Framework::ThreadGroup>&,
				const TM&, const Framework::ThreadGroup&,
				const Framework::ThreadGroup&) const;
		
		/** Constructor from maximum cluster count. */
		NumberCriterion1(const unsigned& count) : dm_count(count) { }
		
	    private:

		/** Maximum cluster count. */
		unsigned dm_count;
		
	    };

	    /**
	     * Clustering termination predicate (distance #1).
	     *
	     * Defines a cluster termination predicate that terminates the
	     * formation of clusters when the ratio of the minimum distance
	     * between any two clusters and the maximum of those cluster's
	     * average inter-cluster distance exceeds a constant value
	     * (specified at object construction).
	     *
	     * @sa    http://en.wikipedia.org/wiki/Cluster_analysis#
	     *        Agglomerative_hierarchical_clustering
	     */
	    template <typename TS, typename TM>
	    struct DistanceCriterion1 {

		bool operator()(const DistanceMatrix<TS, TM >&,
				const std::set<Framework::ThreadGroup>&,
				const TM&, 
				const Framework::ThreadGroup&,
				const Framework::ThreadGroup&) const;
		
		/** Constructor from maximum distance ratio. */
		DistanceCriterion1(const double& ratio) : dm_ratio(ratio) { }

	    private:
		
		/** Maximum distance ratio. */
		double dm_ratio;
		
	    };

	    template <typename TS, typename TM, typename TC>
	    std::set<Framework::ThreadGroup> Apply(
		const Framework::SmartPtr<
	            std::map<TS, std::map<Framework::Thread, TM > > >&,
		TM (*)(const std::map<TS, std::map<Framework::Thread, TM > >&,
		       const Framework::Thread&, const Framework::Thread&),
		TM (*)(const DistanceMatrix<TS, TM >&,
		       const Framework::ThreadGroup&,
		       const Framework::ThreadGroup&),
		const TC&
		);

	    template <typename TS, typename TM>
	    std::set<Framework::ThreadGroup> ApplySimple(
		const Framework::SmartPtr<
	            std::map<TS, std::map<Framework::Thread, TM > > >&
		);
	    
	}



    }

}



template <typename T>
void operator+=(
    std::map<OpenSpeedShop::Framework::StackTrace, T >&,
    const std::map<OpenSpeedShop::Framework::StackTrace, T >&
    );

template <typename T>
void operator+=(std::vector<T >&, const std::vector<T >&);



#include "AdditionAssignment.txx"
#include "ClusterAnalysis.txx"
#include "GetMetricValues.txx"
#include "Reduction.txx"



#endif

/** 
 @cond
 ############################################################################
 # LGPL License                                                             #
 #                                                                          #
 # This file is part of the Machine Learning Framework.                     #
 # Copyright (c) 2010, Philipp Kraus, <philipp.kraus@flashpixx.de>          #
 # This program is free software: you can redistribute it and/or modify     #
 # it under the terms of the GNU Lesser General Public License as           #
 # published by the Free Software Foundation, either version 3 of the       #
 # License, or (at your option) any later version.                          #
 #                                                                          #
 # This program is distributed in the hope that it will be useful,          #
 # but WITHOUT ANY WARRANTY; without even the implied warranty of           #
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
 # GNU Lesser General Public License for more details.                      #
 #                                                                          #
 # You should have received a copy of the GNU Lesser General Public License #
 # along with this program. If not, see <http://www.gnu.org/licenses/>.     #
 ############################################################################
 @endcond
 **/


#ifndef __MACHINELEARNING_GENETICALGORITHM_SELECTION_ROULETTEWHEELSELECTION_HPP
#define __MACHINELEARNING_GENETICALGORITHM_SELECTION_ROULETTEWHEELSELECTION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/numeric/ublas/vector.hpp>

#include "selection.hpp"
#include "../individual/individual.hpp"
#include "../../tools/tools.h"



namespace machinelearning { namespace geneticalgorithm { namespace selection {
    
    
    namespace ublas = boost::numeric::ublas;
    
    
    /** class of the roulette-wheel-selection
     * $LastChangedDate$
     **/
    template<typename T, typename L> class roulettewheelselection : public selection<T,L>
    {
        BOOST_STATIC_ASSERT( !boost::is_integral<T>::value );
        
        public :
        
            roulettewheelselection( void );
            std::vector< boost::shared_ptr< individual::individual<L> > > getElite( const std::size_t&, const std::size_t&, const std::vector< boost::shared_ptr< individual::individual<L> > >&, const ublas::vector<T>&, const ublas::vector<std::size_t>&, const ublas::vector<std::size_t>& ) const;
        
        
        private :
        
            /** random object **/
            tools::random m_random;
        
    };
    
    
    
    /** constructor **/
    template<typename T, typename L> roulettewheelselection<T,L>::roulettewheelselection( void ) :
        m_random()
    {}
    
        
    /** returns the roulette-wheel-selection elites
     * @param p_start start value of the elite values
     * @param p_end end value of the elite values ([start, end) elite elements must be created)
     * @param p_population const reference to the population
     * @param p_fitness vector with fitnss values (index is equal to the index of the population)
     * @param p_rankIndex rank index (first index has the position of the population element, that has the smalles fitness value)
     * @param p_rank rank values (first element equal to polulation index has the rank value of the first individual)
     **/
    template<typename T, typename L> std::vector< boost::shared_ptr< individual::individual<L> > > roulettewheelselection<T,L>::getElite( const std::size_t& p_start, const std::size_t& p_end, const std::vector< boost::shared_ptr< individual::individual<L> > >& p_population, const ublas::vector<T>& p_fitness, const ublas::vector<std::size_t>& p_rankIndex, const ublas::vector<std::size_t>& p_rank ) const
    {
        const ublas::vector<T> l_probability = p_fitness / ublas::sum(p_fitness);
        std::vector< boost::shared_ptr< individual::individual<L> > > l_elite;
        
        for(std::size_t i=p_start; i < p_end; ++i) {
            
            // calculate (probabilities - values) and remove all values < 0 and get the smallest value
            const ublas::vector<T> l_diff = l_probability - m_random.get<double>(tools::random::uniform, 0.0, 1.0);
            
            // determine the first index with an element >= 0
            std::size_t n = 0;
            for(n=0; (n < l_diff.size()) && (l_diff(n) < 0); ++n);
            
            // determine smallest element (we can start with n, because the loop before stops on the first element >= 0)
            for(std::size_t j=n+1; j < l_diff.size(); ++j) {
                if (l_diff(j) < 0)
                    continue;
            
                if (l_diff(j) < l_diff(n))
                    n = j;
            }
            
            
            l_elite.push_back( p_population[n] );
        }
        
        return l_elite;
    }
    
    
};};};

#endif


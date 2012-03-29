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


%module "mdswrap"

#ifdef SWIGJAVA
%include "machinelearning/swig/target/java/java.i"
%{
#include "machinelearning/swig/target/java/java.hpp"
%}
#endif



%{
namespace swig  = machinelearning::swig;
namespace ublas = boost::numeric::ublas;
%}


%include "machinelearning/dimensionreduce/nonsupervised/mds.hpp"
%template(MDS) machinelearning::dimensionreduce::nonsupervised::mds<double>;
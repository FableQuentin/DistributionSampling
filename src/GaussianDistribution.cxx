/*=========================================================================
 *
 *  Copyright 2011-2013 The University of North Carolina at Chapel Hill
 *  All rights reserved.
 *
 *  Licensed under the MADAI Software License. You may obtain a copy of
 *  this license at
 *
 *         https://madai-public.cs.unc.edu/visualization/software-license/
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "GaussianDistribution.h"

#define _USE_MATH_DEFINES // Needed for M_PI to be defined on Windows
#include <cmath>
#undef _USE_MATH_DEFINES

#include "boost/math/distributions/normal.hpp"


namespace madai {

struct GaussianDistribution::GaussianDistributionPrivate {
  /** Underlying class from Boost library that computes the things we want. */
  boost::math::normal m_InternalDistribution;
  GaussianDistributionPrivate(double mean, double standardDeviation);
};

GaussianDistribution::GaussianDistributionPrivate
::GaussianDistributionPrivate(double mean, double standardDeviation) :
  m_InternalDistribution(mean, standardDeviation)
{
}

GaussianDistribution
::GaussianDistribution() :
  m_Mean( 0.0 ),
  m_StandardDeviation( 1.0 ),
  m_GaussianDistributionImplementation(
      new GaussianDistribution::GaussianDistributionPrivate(
          m_Mean, m_StandardDeviation))
{
}


GaussianDistribution
::~GaussianDistribution()
{
  delete m_GaussianDistributionImplementation;
}

Distribution *
GaussianDistribution
::Clone() const
{
  GaussianDistribution * d = new GaussianDistribution();
  d->SetMean(this->GetMean());
  d->SetStandardDeviation(this->GetStandardDeviation());
  return d;
}


void
GaussianDistribution
::SetMean( double mean )
{
  m_Mean = mean;

  delete m_GaussianDistributionImplementation;
  m_GaussianDistributionImplementation =
    new GaussianDistribution::GaussianDistributionPrivate(
        m_Mean, m_StandardDeviation);
}


double
GaussianDistribution
::GetMean() const
{
  return m_Mean;
}


void
GaussianDistribution
::SetStandardDeviation( double standardDeviation )
{
  m_StandardDeviation = standardDeviation;

  delete m_GaussianDistributionImplementation;
  m_GaussianDistributionImplementation =
    new GaussianDistribution::GaussianDistributionPrivate(
        m_Mean, m_StandardDeviation);
}


double
GaussianDistribution
::GetStandardDeviation() const
{
  return m_StandardDeviation;
}


double
GaussianDistribution
::GetLogProbabilityDensity( double x ) const
{
  return log( this->GetNormalizationFactor() ) + this->GetExponent( x );
}


double
GaussianDistribution
::GetGradientLogProbabilityDensity( double x ) const
{
  double diff = x - m_Mean;
  double variance = m_StandardDeviation * m_StandardDeviation;
  return ( - diff / variance );
}


double
GaussianDistribution
::GetProbabilityDensity( double x ) const
{
  //return this->GetNormalizationFactor() * exp( this->GetExponent( x ) );
  return boost::math::pdf(
      m_GaussianDistributionImplementation->m_InternalDistribution, x );
}


double
GaussianDistribution
::GetPercentile( double percentile ) const
{
  return boost::math::quantile(
      m_GaussianDistributionImplementation->m_InternalDistribution,
      percentile );
}

double
GaussianDistribution
::GetSample(madai::Random & r) const
{
  return r.Gaussian(this->m_Mean, this->m_StandardDeviation);
}

double
GaussianDistribution
::GetNormalizationFactor() const
{
  double variance = m_StandardDeviation * m_StandardDeviation;

  return (1.0 / sqrt( 2.0 * M_PI * variance ) );
}


double
GaussianDistribution
::GetExponent( double x ) const
{
  double variance = m_StandardDeviation * m_StandardDeviation;
  double exponent = -( x - m_Mean ) * ( x - m_Mean ) / ( 2.0 * variance );

  return exponent;
}


double
GaussianDistribution
::GetExpectedValue() const
{
  return m_Mean;
}

} // end namespace madai

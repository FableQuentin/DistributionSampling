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

#ifndef madai_Random_h_included
#define madai_Random_h_included

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

#include <vector>


namespace madai {

/** \class Random
 *
 * A random number generator.  contains a seed.
 */
class Random {
public:
  /** Constructor
   *
   * Uses time() for seed. */
  Random();

  /** Constructor
   *
   * \param seed Seed to initialize the random number generator.
   */
  Random(unsigned long int seed);

  /** Destructor */
  virtual ~Random();

  /** Reseed the random number generator
   *
   * \param seed Seed to reinitialize the random number generator.
   */
  virtual void Reseed(unsigned long int seed);

  /** Reseed with the current time. */
  virtual void Reseed();

  /** Returns an integer < N and >= 0 */
  virtual int Integer( int N );

  /** Returns an integer < N and >= 0 */
  virtual int operator()( int N );

  /** Returns a long < N and >= 0 */
  virtual long Integer( long N );

  /** Returns a long < N and >= 0 */
  virtual long operator()( long N );

  /** Returns a uniform random number in the range [0.0, 1.0] */
  virtual double Uniform();

  /** Returns a uniform random number in the range [min, max] */
  virtual double Uniform(double min, double max);

  /** Returns a random number from a Gaussian distribution with mean
   * 0.0 and standard deviation 1.0 */
  virtual double Gaussian();

  /** Returns a random number from a Gaussian distribution with mean
   * and standard deviation supplied as arguments */
  virtual double Gaussian(double mean, double standardDeviation);

private:
  /** Explicitly disallowed */
  Random& operator=(madai::Random &);

  /** Explicitly disallowed */
  Random(madai::Random const &);

  /** Typedefs for random number generation */
  //@{
  typedef boost::mt19937               BaseGeneratorType;
  typedef boost::uniform_int< int >    UniformIntDistributionType;
  typedef boost::uniform_int< long >   UniformLongDistributionType;
  typedef boost::uniform_real<>        UniformRealDistributionType;
  typedef boost::normal_distribution<> NormalDistributionType;
  typedef boost::variate_generator<
    BaseGeneratorType&,
    UniformRealDistributionType >      UniformRealGeneratorType;
  //@}

  /** Mersenne Twister random number generator */
  BaseGeneratorType           m_BaseGenerator;

  /** Uniform int distribution */
  UniformIntDistributionType  m_UniformIntDistribution;

  /** Uniform long distribution */
  UniformLongDistributionType  m_UniformLongDistribution;

  /** Uniform real distribution */
  UniformRealDistributionType m_UniformRealDistribution;

  /** Uniform real generator */
  UniformRealGeneratorType    m_UniformRealGenerator;

  /** Normal distribution */
  NormalDistributionType      m_NormalDistribution;

};

}

#endif // madai_Random_h_included

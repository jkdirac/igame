/* Begin CVS Header
   $Source: /fs/turing/cvs/copasi_dev/copasi/randomGenerator/Cmt19937.h,v $
   $Revision: 1.7 $
   $Name: Build-31 $
   $Author: shoops $
   $Date: 2006/07/21 18:15:48 $
   End CVS Header */

// Copyright � 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * Cmt19937 class implementing the Mersenne Twister random number generator,
 *
 * Created for Copasi by Stefan Hoops
 *
 * A C-program for MT19937, with initialization improved 2002/2/10.
 * Coded by Takuji Nishimura and Makoto Matsumoto.
 * This is a faster version by taking Shawn Cokus's optimization,
 * Matthe Bellew's simplification, Isaku Wada's real version.
 *
 * Before using, initialize the state by using init_genrand(seed)
 * or init_by_array(init_key, key_length).
 *
 * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. The names of its contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Any feedback is very welcome.
 * http://www.math.keio.ac.jp/matumoto/emt.html
 * email: matumoto@math.keio.ac.jp
 */

#ifndef COPASI_Cmt19937
#define COPASI_Cmt19937

#define Cmt19937_N 624

class Cmt19937 : public CRandom
  {
    friend CRandom * CRandom::createGenerator(CRandom::Type type,
        unsigned C_INT32 seed);

    // Attributes
  private:
    unsigned C_INT32 mState[Cmt19937_N]; /* the array for the state vector  */

    C_INT mLeft; // = 1;

    unsigned C_INT32 *mNext;

    // Operations
  protected:
    /**
     * Default/Named constructor.
     * Seeds the random number generator with the given seed.
     * @param C_INT32 seed
     */
    Cmt19937(unsigned C_INT32 seed);

    void next_state();

  public:
    /**
     * The destructor.
     */
    ~Cmt19937();

    /**
     * Initialize or reinitialize the random number generator with
     * the given seed.
     * @param unsigned C_INT32 seed (default system seed)
     */
    void initialize(unsigned C_INT32 seed = CRandom::getSystemSeed());

    /**
     * Get a random number in 0 <= n <= Modulus
     * @return unsigned C_INT32 random
     */
    unsigned C_INT32 getRandomU();

    /**
     * Get a random number in 0 <= n <= (Modulus & 0x7ffffff)
     * @return C_INT32 random
     */
    C_INT32 getRandomS();

    /**
     * Produces a uniformly distributed random number in 0 <= x <= 1.
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomCC();

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomCO();

    /**
     * Produces a uniformly distributed random number in 0 < x < 1.
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomOO();

    void init_by_array(unsigned C_INT32 init_key[],
                       C_INT32 key_length);

    C_FLOAT64 genrand_res53();        // getRandomCO() with higher resolution
  };

class Cmt19937HR : public Cmt19937
  {
    friend CRandom * CRandom::createGenerator(CRandom::Type type,
        unsigned C_INT32 seed);

    // Operations
  protected:
    /**
     * Default/Named constructor.
     * Seeds the random number generator with the given seed.
     * @param C_INT32 seed
     */
    Cmt19937HR(unsigned C_INT32 seed);

  public:
    /**
     * Produces a uniformly distributed random number in 0 <= x <= 1.
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomCC();

    /**
     * Produces a uniformly distributed random number in 0 <= x < 1.
     * Note: 0 < x <= 1 may be achieved by 1.0 - getRandomCO().
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomCO();

    /**
     * Produces a uniformly distributed random number in 0 < x < 1.
     * @return C_FLOAT64 random
     */
    C_FLOAT64 getRandomOO();
  };

#endif // COPASI_Cmt19937

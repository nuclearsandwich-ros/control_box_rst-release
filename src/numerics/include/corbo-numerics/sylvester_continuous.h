/*********************************************************************
 *
 *  Software License Agreement
 *
 *  Copyright (c) 2020,
 *  TU Dortmund - Institute of Control Theory and Systems Engineering.
 *  All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Authors: Christoph Rösmann
 *********************************************************************/

#ifndef SRC_NUMERICS_INCLUDE_CORBO_NUMERICS_SYLVESTER_CONTINUOUS_H_
#define SRC_NUMERICS_INCLUDE_CORBO_NUMERICS_SYLVESTER_CONTINUOUS_H_

#include <corbo-core/console.h>
#include <corbo-core/types.h>

namespace corbo {

/**
 * @brief Methods for dealing with continuous-time sylvester equations
 *
 * @ingroup numerics
 *
 * The Sylvester equation is given by
 * \f[
 *       A X + X B + C = 0
 * \f]
 * A, B and C are not required to be square, but must be compatible to each other.
 * In particular if size(C) = m x n, then size(A) = n x n and size(B) = m x m.
 *
 * @remarks If you want to deal with a Lyapunov equation \f$ A X + X A^T + Q = 0 \f$
 *                  you might want to refer to our specialized implementation in order to
 *                  improve efficency.
 *
 * @see SylvesterDiscrete LyapunovContinuous LyapunovDiscrete
 *
 * @author Christoph Rösmann (christoph.roesmann@tu-dortmund.de)
 *
 * @todo Add support for the generalized Sylvester equations \f$ A X E^T + E X B + C = 0 \f$.
 * @todo Allow the user to precompute the Schur decomposition for subsequent calls of solve() with varying \f$ C \f$.
 */
class SylvesterContinuous
{
 public:
    /**
     * @brief Solve continuous-time Sylvester equation
     *
     * Solve \f$ A X + X B + C = 0 \f$ w.r.t. \f$ X \f$.
     * A, B and C are not required to be square, but must be compatible to each other.
     * In particular if size(C) = m x n, then size(A) = n x n and size(B) = m x m.
     * The solution is unique if for Eigenvalues of A and B it is:
     * \f$ \alpha_i \neq -\beta_j, \forall i,j. \f$
     *
     * The solution is obtained via Schur decomposition [1-4].
     *
     * [1] R.H. Bartels, G. W. Stewart. "Algorithm 432: Solution of the matrix equation AX + XB = C".
     *     Comm. ACM. 15 (9): 820–826, 1972.
     * [2] V. Simoncini. "Computational Methods for Linear Matrix Equations".
     *     SIAM Review 58 (3): 377-441, 2016.
     * [3] https://people.kth.se/~eliasj/NLA/matrixeqs.pdf
     * [4] https://github.com/ajt60gaibb/freeLYAP
     *
     * @param[in]  A    Matrix (might be non-square)
     * @param[in]  B    Matrix (might be non-square)
     * @param[in]  C    Matrix (might be non-square)
     * @param[out] X    Solution with same size as C (size(X) must not be preallocated a-priori)
     * @return true if a finite solution is found, false otherwise.
     */
    static bool solve(const Eigen::Ref<const Eigen::MatrixXd>& A, const Eigen::Ref<const Eigen::MatrixXd>& B,
                      const Eigen::Ref<const Eigen::MatrixXd>& C, Eigen::MatrixXd& X);

    /**
     * @brief Determine if the Sylvester equation exhibits a unique solution
     *
     * The solution is unique if for Eigenvalues of A and B it is:
     * \f$ \alpha_i \neq -\beta_j, \forall i,j. \f$
     *
     * @param[in]  A    Matrix (might be non-square)
     * @param[in]  B    Matrix (might be non-square)
     * @return true if the solution is unique, false otherwise (also if A and B are not square)
     */
    static bool hasUniqueSolution(const Eigen::Ref<const Eigen::MatrixXd>& A, const Eigen::Ref<const Eigen::MatrixXd>& B);
};

}  // namespace corbo

#endif  // SRC_NUMERICS_INCLUDE_CORBO_NUMERICS_SYLVESTER_CONTINUOUS_H_

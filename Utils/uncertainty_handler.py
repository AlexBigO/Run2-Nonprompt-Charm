"""
file: uncertainty_handler.py
brief: Module with helpers for uncertainty propagation
author: Alexandre Bigot <alexandre.bigot@cern.ch>, Strasbourg University
"""

import numpy as np
from ROOT import TGraphErrors  # pylint:disable=no-name-in-module


class UncertaintyPropagator:
    """
    Class for uncertainty propagation using matrix formalism
    """

    # pylint:disable = too-many-arguments,too-many-locals,too-many-branches
    def __init__(self, x, sigma, corr_triu, name_func, coefs, is_sigma_rel=False):
        """
        Method to initialise class members

        Parameters
        ------------------------------------------------
        x: list
            Mean values of variables

        sigma: list
            Uncertainties on variables

        corr_triu: list, None
            Linear correlation factors on the top-right of the correlation matrix
            (i.e. right of the correlation matrix diagonal, diagonal excluded) row by row

        name_func: string
            Name for the function such as y = func(x). The possible options are:

            - "weighted_product"

            - "weighted_sum"

            - "simple_sum": weighted_sum with unitary weight and correlation matrix

        coefs: list
            Coefficients present in func

        is_sigma_rel: bool
            Flag sigma elements as relative uncertainties
        """

        self.x = x
        self.coefs = coefs
        self.name_func = name_func
        # initialise matrices
        n = len(sigma)
        self.m_sigma = np.zeros(shape=(n, 1))  # uncertainty matrix
        self.m_weight = np.diag([1.] * n)  # weight matrix
        self.m_corr = np.diag([1.] * n)  # correlation matrix

        # fill uncertainty matrix
        for i, sig in enumerate(sigma):
            self.m_sigma[i] = sig

        # fill weight matrix
        if name_func == "weighted_product":
            if is_sigma_rel:
                for i, coef in enumerate(coefs):
                    self.m_weight[i][i] = coef
            else:
                for i, (coef, x_i) in enumerate(zip(coefs, x)):
                    self.m_weight[i][i] = coef / x_i
        elif name_func == "weighted_sum":
            weight_tot = np.sum([coef_i * x_i for (coef_i, x_i) in zip(coefs, x)])
            if is_sigma_rel:
                for i, (coef, x_i) in enumerate(zip(coefs, x)):
                    self.m_weight[i][i] = coef * x_i / weight_tot
            else:
                for i, coef in enumerate(coefs):
                    self.m_weight[i][i] = coef / weight_tot

        # handle correlations
        self.correlation = [0] * (n - 1)
        if corr_triu is not None and name_func != "simple_sum":
            self.correlation = corr_triu

        # fill correlation matrix
        irows, icols = [], []
        for irow in range(n):
            for icol in range(irow + 1, n):
                irows.append(irow)
                icols.append(icol)
        for (irow, icol, corr) in zip(irows, icols, self.correlation):
            self.m_corr[irow][icol] = corr
            self.m_corr[icol][irow] = corr

    # def __check_input_consistency(self):
    #     """
    #     Helper method to check self consistency of inputs
    #     """

    #     print("Checking input consistency")

    def set_correlation_matrix_element(self, id_row, id_col, rho):
        """
        Method to set a given element of the correlation matrix and symmetrize it

        Parameters
        ------------------------------------------------
        id_row: int
            Matrix row index

        id_col: int
            Matrix column index

        rho: float
            Correlation factor
        """

        self.m_corr[id_row][id_col] = rho
        self.m_corr[id_col][id_row] = rho

    def get_mean(self):
        """
        Method to get the mean of the distribution
        """

        mean = 1.

        if self.name_func == "weighted_product":
            for (x, coef) in zip(self.x, self.coefs):
                mean *= x**coef
        elif self.name_func == "weighted_sum":
            mean = 0
            for (x, coef) in zip(self.x, self.coefs):
                mean += coef * x
            mean /= np.sum(self.coefs)
        elif self.name_func == "simple_sum":
            return np.sum(self.x)

        return mean

    def get_relative_variance(self):
        """
        Method to get the relative variance of the distribution
        """

        m_weighted_sigma = np.matmul(self.m_weight, self.m_sigma)
        m_corr_weighted_sigma = np.matmul(self.m_corr, m_weighted_sigma)

        return np.matmul(m_weighted_sigma.transpose(), m_corr_weighted_sigma).item(0)

    def get_relative_std_dev(self):
        """
        Method to get the relative standard deviation of the distribution
        """

        return np.sqrt(self.get_relative_variance())

    def get_variance(self, mean=None):
        """
        Method to get the variance of a distribution
        """

        if mean is not None:
            return mean**2 * self.get_relative_variance()

        return self.get_mean()**2 * self.get_relative_variance()

    def get_std_dev(self, mean=None):
        """
        Method to get the relative standard deviation of the distribution
        """

        return np.sqrt(self.get_variance(mean))


def graph_errors(name, title):
    """
    Helper method for easy definition and setting of TGraphErrors instance
    """

    graph = TGraphErrors(1)
    graph.SetName(name)
    graph.SetTitle(title)

    return graph

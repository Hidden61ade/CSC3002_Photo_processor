#include "lasso.h"
#include <iostream>
#include <cmath>
#include <cassert>

Lasso::Lasso(double lambda) : lambda_(lambda) {}

void Lasso::fit(const std::vector<std::vector<double>>& X, const std::vector<double>& y) {
    assert(X.size() == y.size());  // 确保特征矩阵和目标值大小一致

    // 规范化数据
    std::vector<std::vector<double>> X_normalized = X;
    normalize(X_normalized);

    // 初始化回归系数为0
    coefficients_ = std::vector<double>(X_normalized[0].size(), 0);

    // 执行坐标下降算法
    coordinateDescent(X_normalized, y);
}

std::vector<double> Lasso::predict(const std::vector<std::vector<double>>& X) const {
    std::vector<double> predictions;
    for (const auto& row : X) {
        double prediction = 0;
        for (size_t i = 0; i < coefficients_.size(); ++i) {
            prediction += coefficients_[i] * row[i];
        }
        predictions.push_back(prediction);
    }
    return predictions;
}

const std::vector<double>& Lasso::getCoefficients() const {
    return coefficients_;
}

void Lasso::coordinateDescent(const std::vector<std::vector<double>>& X, const std::vector<double>& y) {
    // 设置一个学习率（步长）
    double alpha = 0.01;
    // 迭代次数
    size_t maxIter = 1000;
    size_t n = X.size();
    size_t m = X[0].size();

    // 执行坐标下降
    for (size_t iter = 0; iter < maxIter; ++iter) {
        for (size_t j = 0; j < m; ++j) {
            double gradient = computeGradient(X, y, j);
            // 使用坐标下降更新回归系数
            if (gradient > lambda_) {
                coefficients_[j] = (gradient - lambda_);
            } else if (gradient < -lambda_) {
                coefficients_[j] = (gradient + lambda_);
            } else {
                coefficients_[j] = 0;
            }
        }
    }
}

double Lasso::computeGradient(const std::vector<std::vector<double>>& X, const std::vector<double>& y, int j) const {
    double gradient = 0.0;
    size_t n = X.size();
    for (size_t i = 0; i < n; ++i) {
        double error = 0;
        for (size_t k = 0; k < X[i].size(); ++k) {
            error += X[i][k] * coefficients_[k];
        }
        error -= y[i];
        gradient += error * X[i][j];
    }
    return gradient / n;
}

void Lasso::normalize(std::vector<std::vector<double>>& X) const {
    size_t n = X.size();
    size_t m = X[0].size();

    // 对每列进行标准化
    for (size_t j = 0; j < m; ++j) {
        double mean = 0;
        double stddev = 0;

        // 计算均值
        for (size_t i = 0; i < n; ++i) {
            mean += X[i][j];
        }
        mean /= n;

        // 计算标准差
        for (size_t i = 0; i < n; ++i) {
            stddev += (X[i][j] - mean) * (X[i][j] - mean);
        }
        stddev = std::sqrt(stddev / n);

        // 对列进行标准化
        for (size_t i = 0; i < n; ++i) {
            X[i][j] = (X[i][j] - mean) / stddev;
        }
    }
}

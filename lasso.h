#ifndef LASSO_H
#ifndef LASSO_H
#define LASSO_H

#include <vector>

class Lasso {
public:
    // 构造函数：接受正则化强度 lambda
    Lasso(double lambda);

    // 拟合数据：X 是特征矩阵，y 是目标值
    void fit(const std::vector<std::vector<double>>& X, const std::vector<double>& y);

    // 预测数据：X 是特征矩阵，返回预测结果
    std::vector<double> predict(const std::vector<std::vector<double>>& X) const;

    // 获取回归系数
    const std::vector<double>& getCoefficients() const;

private:
    // Lasso回归的正则化参数
    double lambda_;

    // 存储拟合的回归系数
    std::vector<double> coefficients_;

    // 执行坐标下降算法
    void coordinateDescent(const std::vector<std::vector<double>>& X, const std::vector<double>& y);

    // 计算Lasso目标函数的梯度
    double computeGradient(const std::vector<std::vector<double>>& X, const std::vector<double>& y, int j) const;

    // 用于标准化输入数据
    void normalize(std::vector<std::vector<double>>& X) const;
};

#endif

#endif // LASSO_H

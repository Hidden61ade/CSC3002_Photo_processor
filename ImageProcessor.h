// ImageProcessor.h
#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QImage>
#include <QColor>
#include <QMutex>

class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    explicit ImageProcessor(QObject *parent = nullptr);
    ~ImageProcessor();

    void adjustBrightness(QImage &image, int brightness);
    void adjustSaturation(QImage &image, qreal factor);
    void adjustVibrance(QImage &image, qreal factor);
    void adjustContrast(QImage &image, qreal factor);
    void adjustClarity(QImage &image, qreal factor);
    void adjustHighlightsShadows(QImage &image, qreal highlightsFactor, qreal shadowsFactor);
    void adjustTemperature(QImage &image, qreal temperature);
    void adjustHue(QImage &image, qreal amount);
    void featherEdges(QImage &image, int radius);
    void addGrain(QImage &image, qreal intensity);
    void adjustWhiteBalance(QImage &image, qreal redGain, qreal greenGain, qreal blueGain);

    /**
     * @brief 综合调整图像参数
     * @param image 要调整的图像
     * @param brightness 亮度调整值 (-255 到 +255)
     * @param saturationFactor 饱和度因子 (0.0 到 2.0)
     * @param vibranceFactor 鲜艳度因子 (0.0 到 2.0)
     * @param contrastFactor 对比度因子 (0.5 到 3.0)
     * @param clarityFactor 清晰度因子 (-100.0 到 +100.0)
     * @param highlightsFactor 高光因子 (0.0 到 2.0)
     * @param shadowsFactor 阴影因子 (0.0 到 2.0)
     * @param temperature 色温 (-100.0 到 +100.0)
     * @param hueAmount 色调旋转量 (-180.0 到 +180.0)
     * @param featherRadius 羽化半径 (0 到 50 像素)
     * @param grainIntensity 颗粒强度 (0.0 到 1.0)
     * @param whiteBalanceRed 白平衡红增益 (0.5 到 2.0)
     * @param whiteBalanceGreen 白平衡绿增益 (0.5 到 2.0)
     * @param whiteBalanceBlue 白平衡蓝增益 (0.5 到 2.0)
     */
    void adjustImageParameters(QImage &image,
                             int brightness,
                             qreal saturationFactor,
                             qreal vibranceFactor,
                             qreal contrastFactor,
                             qreal clarityFactor,
                             qreal highlightsFactor,
                             qreal shadowsFactor,
                             qreal temperature,
                             qreal hueAmount,
                             int featherRadius,
                             qreal grainIntensity,
                             qreal whiteBalanceRed,
                             qreal whiteBalanceGreen,
                             qreal whiteBalanceBlue);

private:
    QMutex mutex;
    
    // 辅助函数
    static inline int clamp(int value, int min = 0, int max = 255) {
        return value < min ? min : (value > max ? max : value);
    }

    // 颜色空间转换辅助函数
    void rgbToHsl(int r, int g, int b, qreal &h, qreal &s, qreal &l);
    void hslToRgb(qreal h, qreal s, qreal l, int &r, int &g, int &b);
    
signals:
    void processingProgress(int percent);
    void processingFinished(const QImage& image);
    void processingFailed(const QString& error);
};

#endif // IMAGEPROCESSOR_H

// ImageProcessor.cpp
#include "ImageProcessor.h"
#include <QColor>
#include <QtConcurrent>
#include <cmath>

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
}

ImageProcessor::~ImageProcessor()
{
}

// 综合调整函数实现
void ImageProcessor::adjustImageParameters(QImage &image, 
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
                                           qreal whiteBalanceBlue)
{
    QMutexLocker locker(&mutex); // 线程安全

    QImage processedImage = image;

    // 调整亮度
    adjustBrightness(processedImage, brightness);
    
    // 调整饱和度
    adjustSaturation(processedImage, saturationFactor);
    
    // 调整鲜艳度
    adjustVibrance(processedImage, vibranceFactor);
    
    // 调整对比度
    adjustContrast(processedImage, contrastFactor);
    
    // 调整清晰度
    adjustClarity(processedImage, clarityFactor);
    
    // 调整高光和阴影
    adjustHighlightsShadows(processedImage, highlightsFactor, shadowsFactor);
    
    // 调整色温
    adjustTemperature(processedImage, temperature);
    
    // 调整色调
    adjustHue(processedImage, hueAmount);
    
    // 应用羽化
    if (featherRadius > 0) {
        featherEdges(processedImage, featherRadius);
    }
    
    // 添加颗粒
    if (grainIntensity > 0.0) {
        addGrain(processedImage, grainIntensity);
    }
    
    // 调整白平衡
    adjustWhiteBalance(processedImage, whiteBalanceRed, whiteBalanceGreen, whiteBalanceBlue);

    // 更新原图
    image = processedImage;

    // 发射处理完成信号
    emit processingFinished(image);
}

// 亮度调整实现
void ImageProcessor::adjustBrightness(QImage &image, int brightness)
{
    if (brightness < -255 || brightness > 255) {
        emit processingFailed("亮度值超出范围 (-255 到 +255)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            int r = qBound(0, color.red() + brightness, 255);
            int g = qBound(0, color.green() + brightness, 255);
            int b = qBound(0, color.blue() + brightness, 255);

            scanLine[x] = qRgb(r, g, b);
        }
    }
}

// 饱和度调整实现
void ImageProcessor::adjustSaturation(QImage &image, qreal saturationFactor)
{
    if (saturationFactor < 0.0 || saturationFactor > 2.0) {
        emit processingFailed("饱和度因子超出范围 (0.0 到 2.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            qreal h, s, v;
            color.getHsvF(&h, &s, &v);

            s *= saturationFactor;
            s = qBound(0.0, s, 1.0);

            QColor newColor;
            newColor.setHsvF(h, s, v);

            scanLine[x] = newColor.rgb();
        }
    }
}

// 鲜艳度调整实现
void ImageProcessor::adjustVibrance(QImage &image, qreal vibranceFactor)
{
    if (vibranceFactor < 0.0 || vibranceFactor > 2.0) {
        emit processingFailed("鲜艳度因子超出范围 (0.0 到 2.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            qreal h, s, v;
            color.getHsvF(&h, &s, &v);

            if(s < 0.5) {
                s += vibranceFactor * (0.5 - s);
                s = qBound(0.0, s, 1.0);
            }

            QColor newColor;
            newColor.setHsvF(h, s, v);

            scanLine[x] = newColor.rgb();
        }
    }
}

// 对比度调整实现
void ImageProcessor::adjustContrast(QImage &image, qreal contrastFactor)
{
    if (contrastFactor < 0.5 || contrastFactor > 3.0) {
        emit processingFailed("对比度因子超出范围 (0.5 到 3.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            int r = qBound(0, static_cast<int>((color.redF() - 0.5) * contrastFactor + 0.5), 1);
            int g = qBound(0, static_cast<int>((color.greenF() - 0.5) * contrastFactor + 0.5), 1);
            int b = qBound(0, static_cast<int>((color.blueF() - 0.5) * contrastFactor + 0.5), 1);

            scanLine[x] = qRgb(r * 255, g * 255, b * 255);
        }
    }
}

// 清晰度调整实现
void ImageProcessor::adjustClarity(QImage &image, qreal clarityFactor)
{
    if (clarityFactor < -100.0 || clarityFactor > 100.0) {
        emit processingFailed("清晰度因子超出范围 (-100.0 到 +100.0)。");
        return;
    }

    // 简单实现，功能更复杂建议使用OpenCV等库
    // 这里只做简单的锐化或模糊处理
    // 反锐化掩蔽（未实现高效算法）

    // 复制原图
    QImage blurred = image;
    blurred = image.copy();

    // 简单均值模糊
    QImage temp = image.copy();
    for(int y = 1; y < image.height()-1; ++y) {
        for(int x = 1; x < image.width()-1; ++x) {
            QColor sum(0, 0, 0);
            for(int ky = -1; ky <=1; ++ky) {
                for(int kx = -1; kx <=1; ++kx) {
                    QColor pixel(temp.pixel(x + kx, y + ky));
                    sum.setRed(sum.red() + pixel.red());
                    sum.setGreen(sum.green() + pixel.green());
                    sum.setBlue(sum.blue() + pixel.blue());
                }
            }
            sum.setRed(sum.red() / 9);
            sum.setGreen(sum.green() / 9);
            sum.setBlue(sum.blue() / 9);
            blurred.setPixel(x, y, sum.rgb());
        }
    }

    // 反锐化掩蔽
    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanOrig = reinterpret_cast<QRgb*>(image.scanLine(y));
        QRgb *scanBlur = reinterpret_cast<QRgb*>(blurred.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor orig(scanOrig[x]);
            QColor blur(scanBlur[x]);

            int r = qBound(0, static_cast<int>((orig.red() - blur.red()) * clarityFactor / 100.0 + orig.red()), 255);
            int g = qBound(0, static_cast<int>((orig.green() - blur.green()) * clarityFactor / 100.0 + orig.green()), 255);
            int b = qBound(0, static_cast<int>((orig.blue() - blur.blue()) * clarityFactor / 100.0 + orig.blue()), 255);

            scanOrig[x] = qRgb(r, g, b);
        }
    }
}

// 高光和阴影调整实现
void ImageProcessor::adjustHighlightsShadows(QImage &image, qreal highlightsFactor, qreal shadowsFactor)
{
    if (highlightsFactor < 0.0 || highlightsFactor > 2.0 || shadowsFactor < 0.0 || shadowsFactor > 2.0) {
        emit processingFailed("高光或阴影因子超出范围 (0.0 到 2.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            qreal h, s, v;
            color.getHsvF(&h, &s, &v);

            if(v > 0.7) { // 高光阈值
                v *= highlightsFactor;
                v = qBound(0.0, v, 1.0);
            }

            if(v < 0.3) { // 阴影阈值
                v *= shadowsFactor;
                v = qBound(0.0, v, 1.0);
            }

            QColor newColor;
            newColor.setHsvF(h, s, v);
            scanLine[x] = newColor.rgb();
        }
    }
}

// 色温调整实现
void ImageProcessor::adjustTemperature(QImage &image, qreal temperature)
{
    if (temperature < -100.0 || temperature > 100.0) {
        emit processingFailed("色温值超出范围 (-100.0 到 +100.0)。");
        return;
    }

    qreal redGain = 1.0;
    qreal blueGain = 1.0;

    if (temperature > 0.0) {
        redGain += temperature / 100.0;
        blueGain -= temperature / 100.0;
    }
    else {
        redGain += temperature / 100.0; // temperature 是负数
        blueGain -= temperature / 100.0;
    }

    redGain = qBound(0.5, redGain, 2.0);
    blueGain = qBound(0.5, blueGain, 2.0);

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            int r = qBound(0, static_cast<int>(color.red() * redGain), 255);
            int g = color.green(); // 绿色通道不变
            int b = qBound(0, static_cast<int>(color.blue() * blueGain), 255);

            scanLine[x] = qRgb(r, g, b);
        }
    }
}

// 色调调整实现
void ImageProcessor::adjustHue(QImage &image, qreal hueAmount)
{
    if (hueAmount < -180.0 || hueAmount > 180.0) {
        emit processingFailed("色调旋转量超出范围 (-180.0 到 +180.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            qreal h, s, v;
            color.getHsvF(&h, &s, &v);

            h += hueAmount / 360.0; // 将度转换为 [0,1] 范围
            while (h > 1.0) h -= 1.0;
            while (h < 0.0) h += 1.0;

            QColor newColor;
            newColor.setHsvF(h, s, v);
            scanLine[x] = newColor.rgb();
        }
    }
}

// 羽化实现（简单均值模糊）
void ImageProcessor::featherEdges(QImage &image, int featherRadius)
{
    if (featherRadius <= 0) return;

    // 复制图像
    QImage blurred = image.copy();

    // 简单均值模糊
    for(int y = featherRadius; y < image.height() - featherRadius; ++y) {
        for(int x = featherRadius; x < image.width() - featherRadius; ++x) {
            QColor sum(0, 0, 0);
            int count = 0;
            for(int ky = -featherRadius; ky <= featherRadius; ++ky) {
                for(int kx = -featherRadius; kx <= featherRadius; ++kx) {
                    QColor pixel(image.pixel(x + kx, y + ky));
                    sum.setRed(sum.red() + pixel.red());
                    sum.setGreen(sum.green() + pixel.green());
                    sum.setBlue(sum.blue() + pixel.blue());
                    count++;
                }
            }
            sum.setRed(sum.red() / count);
            sum.setGreen(sum.green() / count);
            sum.setBlue(sum.blue() / count);
            blurred.setPixel(x, y, sum.rgb());
        }
    }

    // 替换原图
    image = blurred;
}

// 添加颗粒实现（灰度颗粒）
void ImageProcessor::addGrain(QImage &image, qreal grainIntensity)
{
    if (grainIntensity <= 0.0) return;

    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            qreal randVal = static_cast<qreal>(qrand()) / RAND_MAX;
            if(randVal < grainIntensity) {
                int noise = qrand() % 256;
                scanLine[x] = qRgb(noise, noise, noise);
            }
        }
    }
}

// 白平衡调整实现
void ImageProcessor::adjustWhiteBalance(QImage &image, qreal redGain, qreal greenGain, qreal blueGain)
{
    if (redGain < 0.5 || redGain > 2.0 ||
        greenGain < 0.5 || greenGain > 2.0 ||
        blueGain < 0.5 || blueGain > 2.0) {
        emit processingFailed("白平衡增益超出范围 (0.5 到 2.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);

            int r = qBound(0, static_cast<int>(color.red() * redGain), 255);
            int g = qBound(0, static_cast<int>(color.green() * greenGain), 255);
            int b = qBound(0, static_cast<int>(color.blue() * blueGain), 255);

            scanLine[x] = qRgb(r, g, b);
        }
    }
}
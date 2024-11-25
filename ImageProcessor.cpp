#include "ImageProcessor.h"
#include <QColor>
#include <QtConcurrent>
#include <cmath>
#include <QTime>

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
}

ImageProcessor::~ImageProcessor()
{
}

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
    QMutexLocker locker(&mutex);

    QImage processedImage = image;
    
    // 先处理白平衡
    if (whiteBalanceRed != 1.0 || whiteBalanceGreen != 1.0 || whiteBalanceBlue != 1.0) {
        adjustWhiteBalance(processedImage, whiteBalanceRed, whiteBalanceGreen, whiteBalanceBlue);
    }

    // 基础调整
    if (brightness != 0) {
        adjustBrightness(processedImage, brightness);
    }
    
    if (contrastFactor != 1.0) {
        adjustContrast(processedImage, contrastFactor);
    }

    // 颜色调整
    if (saturationFactor != 1.0) {
        adjustSaturation(processedImage, saturationFactor);
    }
    
    if (vibranceFactor != 1.0) {
        adjustVibrance(processedImage, vibranceFactor);
    }

    if (clarityFactor != 0.0) {
        adjustClarity(processedImage, clarityFactor);
    }

    if (highlightsFactor != 1.0 || shadowsFactor != 1.0) {
        adjustHighlightsShadows(processedImage, highlightsFactor, shadowsFactor);
    }

    if (temperature != 0.0) {
        adjustTemperature(processedImage, temperature);
    }

    if (hueAmount != 0.0) {
        adjustHue(processedImage, hueAmount);
    }

    // 特效处理
    if (featherRadius > 0) {
        featherEdges(processedImage, featherRadius);
    }

    if (grainIntensity > 0.0) {
        addGrain(processedImage, grainIntensity);
    }

    image = processedImage;
    emit processingFinished(image);
}

void ImageProcessor::adjustBrightness(QImage &image, int brightness)
{
    if (brightness == 0) return;
    
    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            
            int r = clamp(color.red() + brightness);
            int g = clamp(color.green() + brightness);
            int b = clamp(color.blue() + brightness);
            
            scanLine[x] = qRgb(r, g, b);
        }
    }
}

// 饱和度调整实现
void ImageProcessor::adjustSaturation(QImage &image, qreal saturationFactor)
{
    if (saturationFactor == 1.0) return;
    if (saturationFactor < 0.0 || saturationFactor > 2.0) {
        emit processingFailed("饱和度因子超出范围 (0.0 到 2.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            qreal h, s, l;
            color.getHslF(&h, &s, &l);
            
            s = qBound(0.0, s * saturationFactor, 1.0);
            
            QColor newColor;
            newColor.setHslF(h, s, l);
            scanLine[x] = newColor.rgb();
        }
    }
}

// 鲜艳度调整实现
void ImageProcessor::adjustVibrance(QImage &image, qreal vibranceFactor)
{
    if (vibranceFactor == 1.0) return;
    if (vibranceFactor < 0.0 || vibranceFactor > 2.0) {
        emit processingFailed("鲜艳度因子超出范围 (0.0 到 2.0)。");
        return;
    }

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            int r = color.red();
            int g = color.green();
            int b = color.blue();
            
            // 计算饱和度
            int maxChannel = qMax(qMax(r, g), b);
            int minChannel = qMin(qMin(r, g), b);
            qreal sat = maxChannel == 0 ? 0 : (maxChannel - minChannel) / qreal(maxChannel);
            
            // 仅增强低饱和度的颜色
            qreal factor = 1.0 + (1.0 - sat) * (vibranceFactor - 1.0);
            
            r = clamp(qRound(r * factor));
            g = clamp(qRound(g * factor));
            b = clamp(qRound(b * factor));
            
            scanLine[x] = qRgb(r, g, b);
        }
    }
}

// 对比度调整实现
void ImageProcessor::adjustContrast(QImage &image, qreal contrastFactor)
{
    if (contrastFactor == 1.0) return;
    if (contrastFactor < 0.5 || contrastFactor > 3.0) {
        emit processingFailed("对比度因子超出范围 (0.5 到 3.0)。");
        return;
    }

    // 计算平均亮度作为对比度调整的中心点
    qreal avgLuma = 0;
    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            avgLuma += 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
        }
    }
    avgLuma /= (image.width() * image.height());

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            
            qreal r = color.red() - avgLuma;
            qreal g = color.green() - avgLuma;
            qreal b = color.blue() - avgLuma;
            
            r = (r * contrastFactor) + avgLuma;
            g = (g * contrastFactor) + avgLuma;
            b = (b * contrastFactor) + avgLuma;
            
            scanLine[x] = qRgb(clamp(qRound(r)), 
                              clamp(qRound(g)), 
                              clamp(qRound(b)));
        }
    }
}

// 清晰度调整实现 
void ImageProcessor::adjustClarity(QImage &image, qreal clarityFactor)
{
    if (clarityFactor == 0.0) return;
    if (clarityFactor < -100.0 || clarityFactor > 100.0) {
        emit processingFailed("清晰度因子超出范围 (-100.0 到 +100.0)。");
        return;
    }

    // 创建高斯模糊图像
    QImage blurred = image;
    int radius = 3;
    qreal sigma = 1.0;

    // 高斯模糊
    for(int y = radius; y < image.height()-radius; ++y) {
        for(int x = radius; x < image.width()-radius; ++x) {
            qreal sumR = 0, sumG = 0, sumB = 0, sumWeight = 0;
            
            for(int ky = -radius; ky <= radius; ++ky) {
                for(int kx = -radius; kx <= radius; ++kx) {
                    QColor pixel(image.pixel(x + kx, y + ky));
                    qreal weight = exp(-(kx*kx + ky*ky)/(2*sigma*sigma));
                    
                    sumR += pixel.red() * weight;
                    sumG += pixel.green() * weight;
                    sumB += pixel.blue() * weight;
                    sumWeight += weight;
                }
            }
            
            blurred.setPixel(x, y, qRgb(
                clamp(qRound(sumR/sumWeight)),
                clamp(qRound(sumG/sumWeight)),
                clamp(qRound(sumB/sumWeight))
            ));
        }
    }

    // 混合原图和模糊图
    qreal amount = clarityFactor / 100.0;
    for(int y = 0; y < image.height(); ++y) {
        QRgb *origLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        QRgb *blurLine = reinterpret_cast<QRgb*>(blurred.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor orig(origLine[x]);
            QColor blur(blurLine[x]);
            
            int r = clamp(orig.red() + (orig.red() - blur.red()) * amount);
            int g = clamp(orig.green() + (orig.green() - blur.green()) * amount);
            int b = clamp(orig.blue() + (orig.blue() - blur.blue()) * amount);
            
            origLine[x] = qRgb(r, g, b);
        }
    }
}

// 其他函数的修改原则类似:
// 1. 添加提前返回检查
// 2. 确保参数在有效范围内
// 3. 使用clamp函数限制像素值
// 4. 优化处理逻辑和性能

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
    if (temperature == 0.0) return;
    if (temperature < -100.0 || temperature > 100.0) {
        emit processingFailed("色温值超出范围 (-100.0 到 +100.0)。");
        return;
    }

    qreal redGain = 1.0;
    qreal blueGain = 1.0;

    if (temperature > 0.0) {
        redGain += temperature / 100.0;
        blueGain -= temperature / 100.0;
    } else {
        redGain += temperature / 100.0;
        blueGain -= temperature / 100.0;
    }

    // 限制增益范围
    redGain = qBound(0.5, redGain, 2.0);
    blueGain = qBound(0.5, blueGain, 2.0);

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            int r = clamp(qRound(color.red() * redGain));
            int g = color.green();
            int b = clamp(qRound(color.blue() * blueGain));
            scanLine[x] = qRgb(r, g, b);
        }
    }
}

// 色调调整实现
void ImageProcessor::adjustHue(QImage &image, qreal hueAmount)
{
    if (hueAmount == 0.0) return;
    if (hueAmount < -180.0 || hueAmount > 180.0) {
        emit processingFailed("色调旋转量超出范围 (-180.0 到 +180.0)。");
        return;
    }

    qreal hueShift = hueAmount / 360.0; // 转换为0-1范围

    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            qreal h, s, l;
            color.getHslF(&h, &s, &l);
            
            h += hueShift;
            while (h > 1.0) h -= 1.0;
            while (h < 0.0) h += 1.0;
            
            QColor newColor;
            newColor.setHslF(h, s, l);
            scanLine[x] = newColor.rgb();
        }
    }
}

// 羽化实现
void ImageProcessor::featherEdges(QImage &image, int radius)
{
    if (radius <= 0 || radius > 50) {
        emit processingFailed("羽化半径超出范围 (1 到 50)。");
        return;
    }

    QImage original = image;
    
    for(int y = 0; y < image.height(); ++y) {
        for(int x = 0; x < image.width(); ++x) {
            int r = 0, g = 0, b = 0;
            int count = 0;
            
            for(int dy = -radius; dy <= radius; ++dy) {
                int ny = y + dy;
                if(ny < 0 || ny >= image.height()) continue;
                
                for(int dx = -radius; dx <= radius; ++dx) {
                    int nx = x + dx;
                    if(nx < 0 || nx >= image.width()) continue;
                    
                    QColor color(original.pixel(nx, ny));
                    r += color.red();
                    g += color.green();
                    b += color.blue();
                    count++;
                }
            }
            
            image.setPixel(x, y, qRgb(
                clamp(r / count),
                clamp(g / count),
                clamp(b / count)
            ));
        }
    }
}

// 添加颗粒效果实现
void ImageProcessor::addGrain(QImage &image, qreal intensity)
{
    if (intensity <= 0.0 || intensity > 1.0) {
        emit processingFailed("颗粒强度超出范围 (0.0 到 1.0)。");
        return;
    }

    QRandomGenerator random(QTime::currentTime().msecsSinceStartOfDay());
    
    for(int y = 0; y < image.height(); ++y) {
        QRgb *scanLine = reinterpret_cast<QRgb*>(image.scanLine(y));
        for(int x = 0; x < image.width(); ++x) {
            QColor color(scanLine[x]);
            
            // 生成随机噪声
            qreal noise = (random.generateDouble() - 0.5) * 2.0 * intensity * 255;
            
            int r = clamp(color.red() + qRound(noise));
            int g = clamp(color.green() + qRound(noise));
            int b = clamp(color.blue() + qRound(noise));
            
            scanLine[x] = qRgb(r, g, b);
        }
    }
}

// 白平衡调整实现
void ImageProcessor::adjustWhiteBalance(QImage &image, qreal redGain, qreal greenGain, qreal blueGain)
{
    if (redGain == 1.0 && greenGain == 1.0 && blueGain == 1.0) return;
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
            
            int r = clamp(qRound(color.red() * redGain));
            int g = clamp(qRound(color.green() * greenGain));
            int b = clamp(qRound(color.blue() * blueGain));
            
            scanLine[x] = qRgb(r, g, b);
        }
    }
}

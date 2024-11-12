#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QImage>

class ImageProcessor : public QObject {
    Q_OBJECT
public:
    explicit ImageProcessor(QObject *parent = nullptr);

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

signals:
    void processingFinished(const QImage &processedImage);

private:
    // declare functions
    void adjustBrightness(QImage &image, int brightness);
    void adjustSaturation(QImage &image, qreal saturationFactor);
    void adjustVibrance(QImage &image, qreal vibranceFactor);
    void adjustContrast(QImage &image, qreal contrastFactor);
    void adjustClarity(QImage &image, qreal clarityFactor);
    void adjustHighlightsShadows(QImage &image, qreal highlightsFactor, qreal shadowsFactor);
    void adjustTemperature(QImage &image, qreal temperature);
    void adjustHue(QImage &image, qreal hueAmount);
    void featherEdges(QImage &image, int featherRadius);
    void addGrain(QImage &image, qreal grainIntensity);
    void adjustWhiteBalance(QImage &image, qreal redGain, qreal greenGain, qreal blueGain);
};

#endif // IMAGEPROCESSOR_H

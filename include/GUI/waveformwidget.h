#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>
#include <QVector>

class WaveformWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WaveformWidget(QWidget *parent = nullptr);

    void setFilterParams(float gain, float gainLF, float gainHF);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<float> waveformPoints;
};

#endif // WAVEFORMWIDGET_H

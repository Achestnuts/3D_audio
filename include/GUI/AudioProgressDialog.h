#ifndef AUDIOPROGRESSDIALOG_H
#define AUDIOPROGRESSDIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class AudioProgressDialog : public QDialog {
    Q_OBJECT
public:
    explicit AudioProgressDialog(QWidget *parent = nullptr);

    void setProgress(int percent);
    bool isCancelled() const;

signals:
    void cancelRequested();

private:
    QProgressBar *progressBar;
    QPushButton *cancelButton;
    QLabel *statusLabel;
    bool cancelled;
};

#endif // AUDIOPROGRESSDIALOG_H

#ifndef AUDIOIMPORTDIALOG_H
#define AUDIOIMPORTDIALOG_H

#pragma once
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AudioImportDialog;
}
QT_END_NAMESPACE

class AudioImportDialog : public QDialog {
    Q_OBJECT
public:
    enum ImportChoice {
        ImportAsSource,
        ConvertFormat,
        Cancel
    };

    explicit AudioImportDialog(const QString &filePath, QWidget *parent = nullptr);
    ImportChoice choice() const;

    Ui::AudioImportDialog* ui;

private:
    ImportChoice userChoice;
};


#endif // AUDIOIMPORTDIALOG_H

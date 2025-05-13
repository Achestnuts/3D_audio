#ifndef AUDIOIMPORTDIALOG_H
#define AUDIOIMPORTDIALOG_H

#pragma once
#include <QDialog>

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

private:
    ImportChoice userChoice;
};


#endif // AUDIOIMPORTDIALOG_H

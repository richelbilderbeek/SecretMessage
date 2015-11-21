#ifndef QTSECRETMESSAGEEXTRACTDIALOG_H
#define QTSECRETMESSAGEEXTRACTDIALOG_H

#include "qthideandshowdialog.h"


namespace Ui {
  class QtSecretMessageExtractDialog;
}

namespace ribi {
namespace sema {

class QtExtractDialog : public QtHideAndShowDialog
{
    Q_OBJECT
    
public:
    explicit QtExtractDialog(QWidget *parent = 0);
    QtExtractDialog(const QtExtractDialog&) = delete;
    QtExtractDialog& operator=(const QtExtractDialog&) = delete;
    ~QtExtractDialog() noexcept;
    
private slots:
    void on_button_load_clicked();

private:
    Ui::QtSecretMessageExtractDialog *ui;
};

} //~namespace sema
} //~namespace ribi

#endif // QTSECRETMESSAGEEXTRACTDIALOG_H

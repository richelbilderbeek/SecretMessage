#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qtsecretmessageextractdialog.h"

#include <cassert>
#include <boost/shared_ptr.hpp>

#include <QFileDialog>

#include "secretmessagemaindialog.h"

#include "ui_qtsecretmessageextractdialog.h"
#pragma GCC diagnostic pop

ribi::sema::QtExtractDialog::QtExtractDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtSecretMessageExtractDialog)
{
  ui->setupUi(this);
}

ribi::sema::QtExtractDialog::~QtExtractDialog() noexcept
{
  delete ui;
}

void ribi::sema::QtExtractDialog::on_button_load_clicked()
{
  const std::string filename
    = QFileDialog::getOpenFileName(
      0,"Please select an image to extract the message of",
      QString(),"*.png *.bmp").toStdString();
  if (filename.empty()) return;

  //Convert
  {
    const boost::shared_ptr<const QImage> source {
      new QImage(filename.c_str())
    };
    const boost::shared_ptr<const QImage> result {
      MainDialog().ExtractMessageRed(source)
    };
    QPixmap pixmap { QPixmap::fromImage(*result) };
    ui->label_result->setPixmap(pixmap);
  }
  ui->label_todo->hide();
}

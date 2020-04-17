#ifndef PROJECT_ANDLESTICK_HART_MAINDIALOG_H
#define PROJECT_ANDLESTICK_HART_MAINDIALOG_H

#include <QDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QComboBox>
#include <QtGui>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDateTimeEdit>
#include "model.h"
#include "chartwindow.h"

class MainDialog : public QDialog {
Q_OBJECT
public:
    MainDialog(QWidget *parent = 0);

private slots:

    void showClicked();

    void findClicked();

    void managerFinished(QNetworkReply *reply); // cлот, выполняемый при завершении запроса
    void anotherRequest(QNetworkReply *reply);

    void enableShowButton(const QString &text);

private:
    Model mm;
    chartwindow *chwi;//добавил
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QLabel *labelInstrumentName_;
    QPushButton *graphButton_;
    QPushButton *showButton_;
    QLabel *labelDateFrom_;
    QLabel *labelDateTo_;
    QDateTimeEdit *dateFrom_;
    QDateTimeEdit *dateTo_;
    QComboBox *comboBox;
};

#endif //PROJECT_ANDLESTICK_HART_MAINDIALOG_H

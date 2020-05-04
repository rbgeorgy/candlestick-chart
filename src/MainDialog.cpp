#include "MainDialog.h"

MainDialog::MainDialog(QWidget *parent)
        : QDialog(parent) {
    graphButton_ = new QPushButton(tr("&Draw"));
    graphButton_->setEnabled(true);
    showButton_ = new QPushButton(tr("&SHOW"));
    showButton_->setDefault(true);
    showButton_->setEnabled(true); //
    labelDateFrom_ = new QLabel(tr("Date From: "));
    labelDateTo_ = new QLabel(tr("Date To: "));
    dateFrom_ = new QDateTimeEdit(QDate(2020, 02, 01));
    dateTo_ = new QDateTimeEdit(QDate::currentDate());
    dateTo_->setMaximumDate(QDate::currentDate());
    dateTo_->setMinimumDate(dateFrom_->date());
    dateFrom_->setDisplayFormat("yyyy.MM.dd");
    dateTo_->setDisplayFormat("yyyy.MM.dd");

    comboBox = new QComboBox;
    labelInstrumentName_ = new QLabel(tr("Instrument Name: "));
    labelInstrumentName_->setBuddy(comboBox);

    chwi = new chartwindow; //добавил

    connect(comboBox, SIGNAL(currentIndexChanged(
                                     const QString &)),
            this, SLOT(enableShowButton(
                               const QString &)));
    connect(graphButton_, SIGNAL(clicked()), this, SLOT(findClicked()));
//    connect(showButton_, SIGNAL(clicked()), this, SLOT(showClicked()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(labelInstrumentName_);
    topLeftLayout->addWidget(comboBox);

    QHBoxLayout *midLeftLayout = new QHBoxLayout;
    midLeftLayout->addWidget(labelDateFrom_);
    midLeftLayout->addWidget(dateFrom_);
    QHBoxLayout *bottomLeftLayout = new QHBoxLayout;
    bottomLeftLayout->addWidget(labelDateTo_);
    bottomLeftLayout->addWidget(dateTo_);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addLayout(midLeftLayout);
    leftLayout->addLayout(bottomLeftLayout);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(graphButton_);
    rightLayout->addWidget(showButton_);
    rightLayout->addStretch();
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Сandlestick Сhart"));
    setFixedHeight(sizeHint().height());
    loader.do_all_instrument_request();
}

void MainDialog::findClicked() {
    QTimer* tmr = new QTimer();
    loader.do_one_instrument_request(tmr);
    loader.timer = tmr;
    connect(tmr, &QTimer::timeout, this, [this]() {
        show_graph();
        this->loader.timer->deleteLater();
    });

void MainDialog::enableShowButton(const QString &text) {
    showButton_->setEnabled(text != "-");
}

void MainDialog::show_graph() {
    chwi->fill(loader.mm.get_bt(), loader.mm.get_et(), loader.mm.get_op(),
            loader.mm.get_cl(), loader.mm.get_hi(), loader.mm.get_lo());
    chwi->show();
}

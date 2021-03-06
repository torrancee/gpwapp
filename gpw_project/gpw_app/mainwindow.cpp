#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDate>
#include <buyitem.h>
#include "func.h"
#include "stockitem.h"
#include "newprice.h"
#include "sellitem.h"

using std::shared_ptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //addItemsToUsersComboBox();
    setAllConnections();

    //set text color for red, green and black palletes
    red.setColor(QPalette::Text, Qt::red);
    green.setColor(QPalette::Text, Qt::darkGreen);
    black.setColor(QPalette::Text, Qt::black);

    //make default plot
    makePlot();

    //set date
    ui->todayLine->setText(QDate::currentDate().toString("ddd dd.MM.yyyy"));

    //set header names in stock list
    ui->StockList->setHeaderLabels({"NAME", "PRICE"});

    //set header names in details view
    ui->detailsTree->setHeaderLabels({"DATE", "VOL", "PRICE", "TOTAL", "C.TOTAL", "%"});
    ui->detailsTree->header()->resizeSection(0, 95);
    ui->detailsTree->header()->resizeSection(1, 67);
    ui->detailsTree->header()->resizeSection(2, 67);
    ui->detailsTree->header()->resizeSection(3, 67);
    ui->detailsTree->header()->resizeSection(4, 67);
    ui->detailsTree->header()->resizeSection(5, 20);

    //set header names in details view
    ui->archiveTree->setHeaderLabels({"DATE", "VOLUME", "PRICE", "TOTAL", "%"});

    QPixmap picture(":/img/gpwapp.png");
    ui->PicLabel->setPixmap(picture.scaled(ui->PicLabel->width(),
                                           ui->PicLabel->height(),
                                           Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    for(auto &user : users){
        user.saveDataToTheFile();
    }

    delete ui;
}

/*
 *  TODO: connect it with backend stock data import from website.
 */

void MainWindow::on_ImportData_clicked()
{
    QMessageBox::warning(this, "Upsss", "Feature not available");
}

void MainWindow::addItemsToUsersComboBox(std::map<QString, QString>& logsAndPass)
{
    for(auto &temp : logsAndPass){
        ui->UsersComboBox->addItem(temp.first);
    }
}

void MainWindow::setAllConnections()
{
    connect(ui->UsersComboBox,SIGNAL(currentTextChanged(QString)), ui->AccountValue, SLOT(setText(QString)));
    connect(ui->UsersComboBox,SIGNAL(currentTextChanged(QString)), ui->AccountPercent, SLOT(setText(QString)));
}

void MainWindow::on_AccountValue_textChanged(const QString &value)
{
    //TODO: connect it with backend calculated data
    if(value=="AKRZ"){
        ui->AccountValue->setText("10000");
    }
    else if(value=="WPOG"){
        ui->AccountValue->setText("5000");
    }
    else if(value=="none"){
        ui->AccountValue->setText("0");
    }
}

void MainWindow::on_AccountPercent_textChanged(const QString &value)
{
    //TODO: connect it with backend calculated data
    if(value=="AKRZ"){
        ui->AccountPercent->setText("5%");
        ui->AccountPercent->setPalette(green);
    }
    else if(value=="WPOG"){
        ui->AccountPercent->setText("-6%");
        ui->AccountPercent->setPalette(red);
    }
    else if(value=="none"){
        ui->AccountPercent->setText("0%");
        ui->AccountPercent->setPalette(black);
    }
}

/*
 *  Function create and show new window for add new stock item.
 */

void MainWindow::on_AddItem_clicked()
{
    //create window for add item
    AddItemWindow *itemWindow = new AddItemWindow(this);
    itemWindow->show();
}

/*
 * Function (slot) is called after AddItem button clicked.
 * Current user should be checked and item should be added to the proper list.
 *
*/

void MainWindow::receiveItemList(InputData data)
{
    QString currentUser = ui->UsersComboBox->currentText();

    if(ui->StockList->findItems(data.name, Qt::MatchFixedString).length() != 0){

        QMessageBox::warning(this, "Ups", "Item already exist");
    }
    else{

        //push the data to ui stock list
        QTreeWidgetItem *itemStockList =  new QTreeWidgetItem(ui->StockList);
        itemStockList->setText(0, data.name);
        itemStockList->setText(1, data.price);

        //push the data to current user object
        for(auto &tempUser : users){

            if(tempUser.getName() == currentUser){

               StockItem newItem(data.name, data.price);
               tempUser.stockItems.push_back(newItem);
            }
        }
    }
}

/*
 *  Function (slot) receive login from login panel and set in login label
 */

void MainWindow::receiveUserData(QString login, std::map<QString, QString> logsAndPass)
{
    ui->userName->setText(login);
    addItemsToUsersComboBox(logsAndPass);

    //create and add users to vector
    for(auto temp : logsAndPass){

        User newUser(temp.first);
        users.push_back(newUser);
    }

    //fill-in stockList for users
    for(auto &user : users){
        user.loadDataFromTheFile();
    }

    //set current user in combobox same as login
    int index = ui->UsersComboBox->findText(login);
    ui->UsersComboBox->setCurrentIndex(index);
}

void MainWindow::receiveBuyItemData(QString price, QString volume, QDate date)
{
    QString currentUserName =  ui->UsersComboBox->currentText();

    QTreeWidgetItem *currentStockItem = ui->StockList->currentItem();
    QString currentStockItemName = currentStockItem->text(0);

    QTreeWidgetItem *itemDetailsList =  new QTreeWidgetItem(ui->detailsTree);
    QString date_ = date.toString("dd.MM.yyyy");
    itemDetailsList->setText(0, date_);
    itemDetailsList->setText(1, volume);
    itemDetailsList->setText(2, price);

    for(auto &tempUser : users){
        if(tempUser.getName() == currentUserName){

            for(auto &tempItem : tempUser.stockItems)
            {
                if(tempItem.getName() == currentStockItemName){

                    QString details = volume + " " + price + " " + date_;
                    tempItem.setDetails(details);
            }
        }
      }
    }
}

void MainWindow::receiveItemNewPrice(QString name, QString price)
{
    for(auto &tempUser : users){

        for(auto &tempItem : tempUser.stockItems){

            if(tempItem.getName() == name)
                tempItem.setPrice(price);
        }
    }

    //to refresh price in current user view
    int currentUser = ui->UsersComboBox->currentIndex();
    ui->UsersComboBox->setCurrentIndex(-1);
    ui->UsersComboBox->setCurrentIndex(currentUser);
}

void MainWindow::makePlot()
{
    ui->stockChart->legend->setVisible(true);

    //fancy color background added
    QLinearGradient plotGradient(0,0, ui->stockChart->width(), ui->stockChart->height());
    plotGradient.setColorAt(0, Qt::white);
    plotGradient.setColorAt(1, Qt::gray);
    ui->stockChart->setBackground(plotGradient);

    // generate two sets of random walk data (one for candlestick and one for ohlc chart):
    int n = 500;
    QVector<double> time(n), value1(n), value2(n);
    QDateTime start = QDateTime(QDate(2014, 6, 11));
    start.setTimeSpec(Qt::UTC);
    double startTime = start.toTime_t();
    double binSize = 3600*24; // bin data in 1 day intervals
    time[0] = startTime;
    value1[0] = 60;
    value2[0] = 20;
    qsrand(9);
    for (int i=1; i<n; ++i)
    {
      time[i] = startTime + 3600*i;
      value1[i] = value1[i-1] + (qrand()/(double)RAND_MAX-0.5)*10;
      value2[i] = value2[i-1] + (qrand()/(double)RAND_MAX-0.5)*3;
    }

    // create candlestick chart:
    QCPFinancial *candlesticks = new QCPFinancial(ui->stockChart->xAxis, ui->stockChart->yAxis);
    candlesticks->setName("Candlestick");
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
    candlesticks->setWidth(binSize*0.9);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(245, 245, 245));
    candlesticks->setBrushNegative(QColor(40, 40, 40));
    candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
    candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));

    // create ohlc chart:
    QCPFinancial *ohlc = new QCPFinancial(ui->stockChart->xAxis, ui->stockChart->yAxis);
    ohlc->setName("OHLC");
    ohlc->setChartStyle(QCPFinancial::csOhlc);
    ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(time, value2, binSize/3.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
    ohlc->setWidth(binSize*0.2);
    ohlc->setTwoColored(true);

    // create bottom axis rect for volume bar chart:
    QCPAxisRect *volumeAxisRect = new QCPAxisRect(ui->stockChart);
    ui->stockChart->plotLayout()->addElement(1, 0, volumeAxisRect);
    volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
    volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
    // bring bottom and main axis rect closer together:
    ui->stockChart->plotLayout()->setRowSpacing(0);
    volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
    // create two bar plottables, for positive (green) and negative (red) volume bars:
    ui->stockChart->setAutoAddPlottableToLegend(false);
    QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
    for (int i=0; i<n/5; ++i)
    {
      int v = qrand()%20000+qrand()%20000+qrand()%20000-10000*3;
      (v < 0 ? volumeNeg : volumePos)->addData(startTime+3600*5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
    }
    volumePos->setWidth(3600*4);
    volumePos->setPen(Qt::NoPen);
    volumePos->setBrush(QColor(100, 180, 110));
    volumeNeg->setWidth(3600*4);
    volumeNeg->setPen(Qt::NoPen);
    volumeNeg->setBrush(QColor(180, 90, 90));

    // interconnect x axis ranges of main and bottom axis rects:
    connect(ui->stockChart->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
    connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), ui->stockChart->xAxis, SLOT(setRange(QCPRange)));
    // configure axes of both main and bottom axis rect:
    QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
    dateTimeTicker->setDateTimeSpec(Qt::UTC);
    dateTimeTicker->setDateTimeFormat("dd. MMMM");
    volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
    volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
    ui->stockChart->xAxis->setBasePen(Qt::NoPen);
    ui->stockChart->xAxis->setTickLabels(false);
    ui->stockChart->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
    ui->stockChart->xAxis->setTicker(dateTimeTicker);
    ui->stockChart->rescaleAxes();
    ui->stockChart->xAxis->scaleRange(1.025, ui->stockChart->xAxis->range().center());
    ui->stockChart->yAxis->scaleRange(1.1, ui->stockChart->yAxis->range().center());

    // make axis rects' left side line up:
    QCPMarginGroup *group = new QCPMarginGroup(ui->stockChart);
    ui->stockChart->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "Created by: \n"
                                            "   Wiktor Pogoda \n"
                                            "   Adam Krzywaniak \n\n"
                                            "2017");

}

void MainWindow::on_buyItem_clicked()
{
    QTreeWidgetItem * currentItem = ui->StockList->currentItem();
    if(currentItem != nullptr){
        BuyItem *buyItem = new BuyItem(this);
        buyItem->setModal(true);

        //set connection between MainWindow and BuyItem
        connect(this, SIGNAL(sendItemName(QString)), buyItem, SLOT(receiveItemName(QString)));

        QString currentItemName = currentItem->text(0);
        emit sendItemName(currentItemName);
        buyItem->exec();
    }
    else{

        QMessageBox::warning(this, "Upss", "Stock Item is not selected!");
    }
}

void MainWindow::on_UsersComboBox_currentIndexChanged(const QString &currentUser)
{
    ui->StockList->clear();

    for(auto &tempUser : users){

        if(tempUser.getName() == currentUser){

           for(auto &tempItem : tempUser.stockItems){

               QTreeWidgetItem *itemStockList =  new QTreeWidgetItem(ui->StockList);
               itemStockList->setText(0, tempItem.getName());
               itemStockList->setText(1, tempItem.getPrice());

           }
        }
    }
}

void MainWindow::on_StockList_itemClicked(QTreeWidgetItem *item, int column)
{
    qDebug() << "item clicked" << item->text(column);

    ui->detailsTree->clear();

    QString currentUser = ui->UsersComboBox->currentText();

    for(auto &tempUser : users){

        if(tempUser.getName() == currentUser){

           for(auto &tempItem : tempUser.stockItems){

               if(tempItem.getName() == item->text(0)){

                   for(auto & tempDetails : tempItem.details){
                       QStringList detailsList = tempDetails.split(" ");

                       QTreeWidgetItem *itemDetailsList = new QTreeWidgetItem(ui->detailsTree);
                       itemDetailsList->setText(0, detailsList.at(2));
                       itemDetailsList->setText(1, detailsList.at(0));
                       itemDetailsList->setText(2, detailsList.at(1));
                   }
               }
           }
        }
    }
}

void MainWindow::on_EditPrice_clicked()
{
    QTreeWidgetItem *currentItem = ui->StockList->currentItem();

    if(currentItem == nullptr){

        QMessageBox::warning(this, "Ups", "Item not selected.");
    }
    else{

        NewPrice *newPriceDialog = new NewPrice(this);
        QString itemName =  currentItem->text(0);
        newPriceDialog->setModal(true);

        connect(this, SIGNAL(sendItemName(QString)), newPriceDialog, SLOT(receiveItemName(QString)));
        emit sendItemName(itemName);

        newPriceDialog->exec();
    }

}

void MainWindow::on_SellItem_clicked()
{
    QTreeWidgetItem *currentItem = ui->detailsTree->currentItem();
    if(currentItem == nullptr){
        QMessageBox::warning(this, "Ups", "Item not selected");
    }
    else{

        SellItem *sellItemWindow = new SellItem(this);
        sellItemWindow->setModal(true);
        sellItemWindow->exec();
    }



}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qstandarditemmodel.h"
#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

struct Ticket {
    int id;
    int price;
    int count;
};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void drawTicket(QPainter &painter, const QRect &rect, QString series, int ticketNumber, int price);


private slots:
    void on_addTicketsBtb_clicked();

    void on_generateFileBtn_clicked();

    void on_ticketsListView_customContextMenuRequested(const QPoint &pos);
    void deleteAction();
    void deleteAllAction();


    void on_ticketsListView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    // QStringList dataList;
    QList<Ticket> tickets;
    QModelIndex selectedIndexForDeletion;
    int lastId = 0;

    bool validFields();
};
#endif // MAINWINDOW_H

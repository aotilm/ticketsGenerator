#include "mainwindow.h"
#include "qstandarditemmodel.h"
#include "ui_mainwindow.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QMenu>
#include <QIntValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    ui->countEdit->setValidator(new QIntValidator(0, INT_MAX, ui->countEdit));
    ui->priceEdit->setValidator(new QIntValidator(0, INT_MAX, ui->countEdit));

    // або фіксований розмір
    setFixedSize(700, 370);

    model = new QStandardItemModel(this);

    for (const Ticket &t : tickets) {
        QString displayText = QString("Ціна: %1  /  Кількість: %2")
                                  .arg(t.price)
                                  .arg(t.count);

        QStandardItem *item = new QStandardItem(displayText);
        item->setData(t.id, Qt::UserRole); // Зберігаємо ID
        model->appendRow(item);
    }

    ui->ticketsListView->setModel(model);



    ui->ticketsListView->setModel(model);

    ui->ticketsListView->setContextMenuPolicy(Qt::CustomContextMenu);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateFileBtn_clicked()
{
    if(ui->seriesEdit->text().isEmpty()){
        QMessageBox::information(this, " ", "Введіть серію квитків!");
        return;
    }

    if(tickets.isEmpty()){
        QMessageBox::information(this, " ", "Додайте мінімум один квиток!");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Зберегти PDF",
        QDir::homePath() + "/tickets.pdf",
        "PDF файли (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    QPdfWriter pdf(fileName);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    QPainter painter(&pdf);
    painter.setFont(QFont("Arial", 10));

    const double mmPerInch = 25.4;
    const int dpi = 300;
    const double ticketWidthMM = 40.0;
    const double ticketHeightMM = 65.0;

    const int ticketWidth = static_cast<int>(ticketWidthMM * dpi / mmPerInch);
    const int ticketHeight = static_cast<int>(ticketHeightMM * dpi / mmPerInch);

    const int cols = 5;
    const int rows = 4;
    const int ticketsPerPage = cols * rows;

    const int pageWidth = pdf.width();
    const int pageHeight = pdf.height();

    const int gridWidth = cols * ticketWidth;
    const int gridHeight = rows * ticketHeight;

    const int marginX = (pageWidth - gridWidth) / 2;
    const int marginY = (pageHeight - gridHeight) / 2;

    int ticketNumber = 1;
    int ticketsOnCurrentPage = 0;
    int currentRow = 0;
    int currentCol = 0;

    for (const Ticket &t : tickets) {
        for (int i = 0; i < t.count; ++i) {
            if (ticketsOnCurrentPage == ticketsPerPage) {
                pdf.newPage();
                ticketsOnCurrentPage = 0;
                currentRow = 0;
                currentCol = 0;
            }

            int x = marginX + currentCol * ticketWidth;
            int y = marginY + currentRow * ticketHeight;
            QRect rect(x, y, ticketWidth, ticketHeight);

            drawTicket(painter, rect, ui->seriesEdit->text(), ticketNumber, t.price);

            ticketNumber++;
            ticketsOnCurrentPage++;

            currentCol++;
            if (currentCol == cols) {
                currentCol = 0;
                currentRow++;
            }
        }
    }

    painter.end();
    QMessageBox::information(this, "Готово", "PDF збережено:\n" + fileName);
}



void MainWindow::drawTicket(QPainter &painter, const QRect &rect, QString series, int ticketNumber, int price)
{
    painter.save(); // Зберігаємо поточний стан

    // 🔲 Зовнішня чорна рамка
    QPen borderPen(Qt::black, 2);
    painter.setPen(borderPen);
    painter.setBrush(Qt::white);
    painter.drawRect(rect);

    int padding = 30;

    int left = rect.left();
    int top = rect.top();
    int width = rect.width();
    int height = rect.height();

    //  Внутрішній контентний прямокутник
    QRect innerRect(left + padding, top + padding, width - 2 * padding, height - 2 * padding);
    painter.drawRect(innerRect);

    int innerTop = innerRect.top();
    int innerLeft = innerRect.left();
    int innerWidth = innerRect.width();
    int innerHeight = innerRect.height();

    // Розбиваємо внутрішній прямокутник на секції
    int sectionHeight = innerHeight / 8;

    // 1. Верхній заголовок у рамці
    QRect topBox(innerLeft, innerTop, innerWidth, sectionHeight * 1.4);
    painter.drawRect(topBox);
    QFont topFont("Arial", 8);
    painter.setFont(topFont);
    painter.drawText(topBox, Qt::AlignCenter | Qt::TextWordWrap,
                     "КП \"Нововолинський\nміський парк\nкультури і відпочинку\"");

    // 2. серія А
    QRect seriesRect(innerLeft, topBox.bottom(), innerWidth, sectionHeight);
    QFont normalFont("Arial", 10);
    painter.setFont(normalFont);
    painter.drawText(seriesRect, Qt::AlignCenter, QString("серія %1").arg(series));

    // 3. № + номер
    QRect numberRect(innerLeft + padding, seriesRect.bottom(), innerWidth - 2 * padding, sectionHeight);
    painter.drawText(numberRect, Qt::AlignLeft | Qt::AlignVCenter,
                     QString("№ %1").arg(ticketNumber));

    // 4. КВИТОК (великим жирним)
    QRect mainTextRect(innerLeft, numberRect.bottom(), innerWidth, sectionHeight * 1.5);
    QFont bigBold("Arial", 16, QFont::Bold);
    painter.setFont(bigBold);
    painter.drawText(mainTextRect, Qt::AlignCenter, "КВИТОК");

    // 5. Ціна 30 грн (де "30" — жирним) — повністю по центру
    QRect priceRect(innerLeft + padding, mainTextRect.bottom(), innerWidth - 2 * padding, sectionHeight * 1.5);

    QString pricePrefix = "Ціна ";
    QString priceValue = QString("%1").arg(price);
    QString priceSuffix = " грн";

    // Крок 1: обчислюємо ширини кожної частини
    painter.setFont(normalFont);
    int prefixWidth = painter.fontMetrics().horizontalAdvance(pricePrefix);

    QFont boldPriceFont("Arial", 16, QFont::Bold);
    painter.setFont(boldPriceFont);
    int valueWidth = painter.fontMetrics().horizontalAdvance(priceValue);

    painter.setFont(normalFont);
    int suffixWidth = painter.fontMetrics().horizontalAdvance(priceSuffix);

    // Загальна ширина всього рядка
    int totalWidth = prefixWidth + valueWidth + suffixWidth;

    // Центрована X-координата початку
    int x = priceRect.left() + (priceRect.width() - totalWidth) / 2;

    // Вертикальна позиція baseline
    int y = priceRect.top() + (priceRect.height() + painter.fontMetrics().ascent()) / 2 - 2;

    // Крок 2: малюємо частини тексту
    painter.setFont(normalFont);
    painter.drawText(x, y, pricePrefix);
    x += prefixWidth;

    painter.setFont(boldPriceFont);
    painter.drawText(x, y, priceValue);
    x += valueWidth;

    painter.setFont(normalFont);
    painter.drawText(x, y, priceSuffix);


    // 6. Нижня рамка з написом КОНТРОЛЬ
    QRect bottomBox(innerLeft, innerRect.bottom() - sectionHeight * 1.1, innerWidth, sectionHeight * 1.1);
    painter.drawRect(bottomBox);
    QFont controlFont("Arial", 10);
    painter.setFont(controlFont);
    painter.drawText(bottomBox, Qt::AlignCenter, "КОНТРОЛЬ");

    painter.restore(); // Відновлюємо стан
}



void MainWindow::on_addTicketsBtb_clicked()
{
    if (validFields()) {
        Ticket t = {
            lastId,
            ui->priceEdit->text().toInt(),
            ui->countEdit->text().toInt()
        };

        tickets.append(t);

        QString displayText = QString("Ціна: %1  /  Кількість: %2")
                                  .arg(t.price)
                                  .arg(t.count);

        QStandardItem *item = new QStandardItem(displayText);
        item->setData(t.id, Qt::UserRole);
        model->appendRow(item);

        lastId++;

        // Очистити поля
        ui->countEdit->clear();
        ui->priceEdit->clear();
        for (const Ticket &t : tickets) {
            qDebug() << "ID:" << t.id << "Ціна:" << t.price << "Кількість:" << t.count;
        }

    }
}



void MainWindow::on_ticketsListView_customContextMenuRequested(const QPoint &pos)
{
    QModelIndex index = ui->ticketsListView->indexAt(pos);
    if (!index.isValid())
        return;

    selectedIndexForDeletion = index;

    QMenu contextMenu(this);
    contextMenu.addAction("Видалити", this, SLOT(deleteAction()));
    contextMenu.addAction("Видалити все", this, SLOT(deleteAllAction()));


    contextMenu.exec(ui->ticketsListView->viewport()->mapToGlobal(pos));
}

void MainWindow::deleteAction()
{
    if (selectedIndexForDeletion.isValid()) {
        int id = selectedIndexForDeletion.data(Qt::UserRole).toInt();

        for (int i = 0; i < tickets.size(); ++i) {
            if (tickets[i].id == id) {
                tickets.removeAt(i);
                break;
            }
        }

        model->removeRow(selectedIndexForDeletion.row());
        for (const Ticket &t : tickets) {
            qDebug() << "ID:" << t.id << "Ціна:" << t.price << "Кількість:" << t.count;
        }

    }
}

void MainWindow::deleteAllAction()
{
    if (selectedIndexForDeletion.isValid()) {
        int id = selectedIndexForDeletion.data(Qt::UserRole).toInt();

        tickets.clear();

        model->clear();

        for (const Ticket &t : tickets) {
            qDebug() << "ID:" << t.id << "Ціна:" << t.price << "Кількість:" << t.count;
        }

    }
}




void MainWindow::on_ticketsListView_clicked(const QModelIndex &index)
{
    int id = index.data(Qt::UserRole).toString().toInt();
}

bool MainWindow::validFields(){
    if(ui->countEdit->text().isEmpty() && ui->priceEdit->text().isEmpty()){
        QMessageBox::information(this, " ","Введіть вхідні дані!");
        return false;
    }

    return true;
}

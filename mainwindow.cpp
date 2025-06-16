#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStringListModel(this);
    dataList << "Початковий запис";
    model->setStringList(dataList);

    ui->ticketsListView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
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
    pdf.setResolution(300); // 300 dpi

    QPainter painter(&pdf);
    painter.setFont(QFont("Arial", 10));

    // Розміри квитка в мм
    const double mmPerInch = 25.4;
    const int dpi = 300;

    const double ticketWidthMM = 40.0;
    const double ticketHeightMM = 65.0;

    const int ticketWidth = static_cast<int>(ticketWidthMM * dpi / mmPerInch);   // ≈ 472 px
    const int ticketHeight = static_cast<int>(ticketHeightMM * dpi / mmPerInch); // ≈ 768 px

    const int cols = 5;
    const int rows = 4;

    // Відступи з урахуванням A4 сторінки
    const int pageWidth = pdf.width();   // ≈ 2480 px
    const int pageHeight = pdf.height(); // ≈ 3508 px

    const int gridWidth = cols * ticketWidth;
    const int gridHeight = rows * ticketHeight;

    const int marginX = (pageWidth - gridWidth) / 2;   // ≈ 5 мм
    const int marginY = (pageHeight - gridHeight) / 2; // ≈ 18.5 мм

    int ticketIndex = 0;
    int totalTickets = 30;

    while (ticketIndex < totalTickets) {
        for (int row = 0; row < rows && ticketIndex < totalTickets; ++row) {
            for (int col = 0; col < cols && ticketIndex < totalTickets; ++col) {
                int x = marginX + col * ticketWidth;
                int y = marginY + row * ticketHeight;

                QRect rect(x, y, ticketWidth, ticketHeight);
                drawTicket(painter, rect, ticketIndex + 1);

                ticketIndex++;
            }
        }

        if (ticketIndex < totalTickets)
            pdf.newPage();
    }

    painter.end();
    QMessageBox::information(this, "Готово", "PDF збережено:\n" + fileName);
}




void MainWindow::drawTicket(QPainter &painter, const QRect &rect, int ticketNumber)
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
    painter.drawText(seriesRect, Qt::AlignCenter, "серія А");

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
    QString priceValue = "30";
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



void MainWindow::on_pushButton_2_clicked()
{
    QString newEntry = QString("Новий запис %1").arg(dataList.size() + 1);
    dataList.append(newEntry);
    model->setStringList(dataList);
}


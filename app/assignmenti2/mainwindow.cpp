#include <QtGui>

#include "lcdrange.h"
#include "radio.h"
#include "mainwindow.h"

MainWindow::MainWindow()
{
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    createActions();
    createMenus();

    createStatusBar();
    createDockWindows();
    //
    setWindowTitle(tr("Dock Widgets"));
//    //
//    // newLetter();
    setUnifiedTitleAndToolBarOnMac(true);
}


void MainWindow::createActions()
{
    newLetterAct = new QAction(QIcon(":/images/new.png"), tr("&New Letter"),
                               this);
    newLetterAct->setShortcuts(QKeySequence::New);
    newLetterAct->setStatusTip(tr("Create a new form letter"));
    connect(newLetterAct, SIGNAL(triggered()), this, SLOT(newLetter()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current form letter"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    printAct = new QAction(QIcon(":/images/print.png"), tr("&Print..."), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print the current form letter"));
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    undoAct = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last editing action"));
    connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newLetterAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
////
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
////
    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Choose a file name"), ".",
                                                    tr("HTML (*.html *.htm)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot write file %1:\n%2.")
                                     .arg(fileName)
                                     .arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->toHtml();
    QApplication::restoreOverrideCursor();

    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Customers"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    customerList = new QListWidget(dock);
    customerList->addItems(QStringList()
                                   << "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
                                   << "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
                                   << "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
                                   << "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
                                   << "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
                                   << "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
    dock->setWidget(customerList);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
//
    dock = new QDockWidget(tr("radio"), this);
    QWidget *radio = new Radio;
//    something = new QListWidget(dock);
//    dock = new QDockWidget(tr("Paragraphs"), this);
//    paragraphsList = new QListWidget(dock);
//    paragraphsList->addItems(QStringList()
//                                     << "Thank you for your payment which we have received today."
//                                     << "Your order has been dispatched and should be with you "
//                                        "within 28 days."
//                                     << "We have dispatched those items that were in stock. The "
//                                        "rest of your order will be dispatched once all the "
//                                        "remaining items have arrived at our warehouse. No "
//                                        "additional shipping charges will be made."
//                                     << "You made a small overpayment (less than $5) which we "
//                                        "will keep on account for you, or return at your request."
//                                     << "You made a small underpayment (less than $1), but we have "
//                                        "sent your order anyway. We'll add this underpayment to "
//                                        "your next bill."
//                                     << "Unfortunately you did not send enough money. Please remit "
//                                        "an additional $. Your order will be dispatched as soon as "
//                                        "the complete amount has been received."
//                                     << "You made an overpayment (more than $5). Do you wish to "
//                                        "buy more items, or should we return the excess to you?");
//    dock->setWidget(paragraphsList);
    dock->setWidget(radio);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
//
//    connect(customerList, SIGNAL(currentTextChanged(QString)),
//            this, SLOT(insertCustomer(QString)));
//    connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
//            this, SLOT(addParagraph(QString)));
}
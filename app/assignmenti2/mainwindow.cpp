#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow()
 {
     textEdit = new QTextEdit;
     // setCentralWidget(textEdit);

     // createActions();
     // createMenus();
     // createToolBars();
     // createStatusBar();
     // createDockWindows();
     //
     // setWindowTitle(tr("Dock Widgets"));
     //
     // newLetter();
     // setUnifiedTitleAndToolBarOnMac(true);
 }


void MainWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(newLetterAct);
     fileMenu->addAction(saveAct);
     fileMenu->addAction(printAct);
     fileMenu->addSeparator();
     fileMenu->addAction(quitAct);

     editMenu = menuBar()->addMenu(tr("&Edit"));
     editMenu->addAction(undoAct);

     viewMenu = menuBar()->addMenu(tr("&View"));

     menuBar()->addSeparator();

     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);
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

      dock = new QDockWidget(tr("Paragraphs"), this);
      paragraphsList = new QListWidget(dock);
      paragraphsList->addItems(QStringList()
              << "Thank you for your payment which we have received today."
              << "Your order has been dispatched and should be with you "
                 "within 28 days."
              << "We have dispatched those items that were in stock. The "
                 "rest of your order will be dispatched once all the "
                 "remaining items have arrived at our warehouse. No "
                 "additional shipping charges will be made."
              << "You made a small overpayment (less than $5) which we "
                 "will keep on account for you, or return at your request."
              << "You made a small underpayment (less than $1), but we have "
                 "sent your order anyway. We'll add this underpayment to "
                 "your next bill."
              << "Unfortunately you did not send enough money. Please remit "
                 "an additional $. Your order will be dispatched as soon as "
                 "the complete amount has been received."
              << "You made an overpayment (more than $5). Do you wish to "
                 "buy more items, or should we return the excess to you?");
      dock->setWidget(paragraphsList);
      addDockWidget(Qt::RightDockWidgetArea, dock);
      viewMenu->addAction(dock->toggleViewAction());

      connect(customerList, SIGNAL(currentTextChanged(QString)),
              this, SLOT(insertCustomer(QString)));
      connect(paragraphsList, SIGNAL(currentTextChanged(QString)),
              this, SLOT(addParagraph(QString)));
  }
